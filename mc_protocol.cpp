//
// Copyright (c) 2011 Alex Yatskov
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

#include "metacall.hpp"
#include "mc_protocol.hpp"

namespace metacall {


//
// Protocol
//

Protocol::Protocol(Stream* stream, Binding* binding) :
    stream_(stream),
    binding_(binding),
    rate_(64)
{
}

void Protocol::advance() {
    if (!stream_->socket()->connected()) {
        return;
    }

    for (int i = 0; i < rate_; ++i) {
        if (advanceStream() != Stream::STATE_READY) {
            break;
        }
    }

    std::vector<TaskMap::iterator> processed;
    for (TaskMap::iterator iter = taskMap_.begin(); iter != taskMap_.end(); ++iter) {
        TaskEntry& entry = iter->second;
        switch (entry.state) {
            case TASK_STATE_READY:
            case TASK_STATE_ERROR:
                processed.push_back(iter);
                for (size_t i = 0; i < entry.handlers.size(); ++i) {
                    HandlerEntry& handler = entry.handlers[i];
                    handler.handler(this, iter->first, entry.state, handler.userPtr);
                }
                break;
            default:
                break;
        }
    }

    for (size_t i = 0; i < processed.size(); ++i) {
        taskMap_.erase(processed[i]);
    }
}

void Protocol::setRate(int rate) {
    rate_ = rate;
}

bool Protocol::setHandler(TaskId id, HandlerProc handler, void* userPtr) {
    const TaskMap::iterator iter = taskMap_.find(id);
    if (iter == taskMap_.end() || iter->second.state != TASK_STATE_PENDING) {
        return false;
    }

    iter->second.handlers.push_back(HandlerEntry(handler, userPtr));
    return true;
}

void Protocol::clearHandler(TaskId id) {
    const TaskMap::iterator iter = taskMap_.find(id);
    if (iter != taskMap_.end()) {
        taskMap_.erase(iter);
    }
}

void Protocol::clearHandlers() {
    for (TaskMap::iterator iter = taskMap_.begin(); iter != taskMap_.end(); ++iter) {
        iter->second.handlers.clear();
    }
}

Protocol::TaskState Protocol::queryState(TaskId id) const {
    const TaskMap::const_iterator iter = taskMap_.find(id);
    return iter == taskMap_.end() ? TASK_STATE_UNDEFINED : iter->second.state;
}

Stream::State Protocol::advanceStream() {
    stream_->advance();

    PacketHeader header;
    int headerSize = 0;

    Stream::State state = stream_->peek(&header, &headerSize);
    if (state == Stream::STATE_READY) {
        switch (header.id) {
            case PACKET_ID_FUNCTION_CALL_REQUEST:
                state = advanceInvokeRequest();
                break;
            case PACKET_ID_FUNCTION_CALL_REPLY:
                state = advanceInvokeReply();
                break;
            default:
                state = Stream::STATE_ERROR_PROTOCOL;
                break;
        }
    }

    return state;
}

Stream::State Protocol::advanceInvokeReply() {
    PacketInvokeReply packetReply;
    Deserializer deserializer(&packetReply.data);

    Stream::State state = stream_->receive(&packetReply);
    if (state == Stream::STATE_READY) {
        const TaskMap::iterator iter = taskMap_.find(static_cast<TaskId>(packetReply.taskId));
        if (iter == taskMap_.end()) {
            state = Stream::STATE_ERROR_PROTOCOL;
        }
        else {
            const bool error =
                (packetReply.flags & PacketInvokeReply::FLAG_UNBOUND_FUNC) ||
                (packetReply.flags & PacketInvokeReply::FLAG_INVALID_ARGS);

            iter->second.state  = error ? TASK_STATE_ERROR : TASK_STATE_READY;
            iter->second.data   = packetReply.data;
        }
    }

    return state;
}

Stream::State Protocol::advanceInvokeRequest() {
    PacketInvokeRequest packetRequest;
    Deserializer deserializer(&packetRequest.data);

    const Stream::State state = stream_->receive(&packetRequest);
    if (state == Stream::STATE_READY) {
        PacketInvokeReply packetReply;
        packetReply.taskId = packetRequest.taskId;

        Serializer serializer(&packetReply.data);
        switch (binding_->call(packetRequest.function, &deserializer, &serializer)) {
            case Binding::CALL_RESULT_INVALID_ARGS:
                packetReply.flags |= PacketInvokeReply::FLAG_INVALID_ARGS;
                break;
            case Binding::CALL_RESULT_UNBOUND_FUNC:
                packetReply.flags |= PacketInvokeReply::FLAG_UNBOUND_FUNC;
                break;
            default:
                break;
        }

        stream_->send(packetReply);
    }

    return state;
}

Protocol::TaskId Protocol::invoke(const Token& token) {
    PacketInvokeRequest packetRequest;
    return invokeExec(token, &packetRequest);
}

Protocol::TaskId Protocol::invokeExec(const Token& token, PacketInvokeRequest* packetRequest) {
    const TaskId taskId = registerTaskId();

    packetRequest->function = token;
    packetRequest->taskId   = taskId;

    if (stream_->send(*packetRequest) != Stream::STATE_READY) {
        return TASK_ID_INVALID;
    }

    taskMap_[taskId] = TaskEntry();
    return taskId;
}

Protocol::TaskId Protocol::registerTaskId() {
    static int id = TASK_ID_INVALID;
    while (++id == TASK_ID_INVALID);
    return static_cast<TaskId>(id);
}


}
