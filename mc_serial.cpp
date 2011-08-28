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
#include "mc_serial.hpp"

namespace metacall {


//
// Deserializer
//

Deserializer::Deserializer(const Buffer* data) :
    data_(data),
    offset_(0)
{
}

const byte* Deserializer::readRaw(int size) {
    if (data_ == NULL || size > data_->bytes() - offset_) {
        return NULL;
    }

    const byte* data = static_cast<const byte*>(data_->data()) + offset_;
    offset_ += size;

    return data;
}

int Deserializer::offset() const {
    return offset_;
}

bool Deserializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? offset_ + offset : offset;

    if (offsetNew >= 0 && offsetNew <= data_->bytes()) {
        offset_ = offsetNew;
        return true;
    }

    return false;
}


//
// Serializer
//

Serializer::Serializer(Buffer* data) :
    data_(data),
    offset_(0)
{
}

bool Serializer::writeRaw(const void* data, int size) {
    if (data_ != NULL) {
        data_->addToBack(static_cast<const byte*>(data), size);
        offset_ += size;
    }

    return true;
}

bool Serializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? offset_ + offset : offset;

    if (offsetNew >= 0 && offsetNew <= data_->bytes()) {
        offset_ = offsetNew;
        return true;
    }

    return false;
}

int Serializer::offset() const {
    return offset_;
}


//
// Serializers
//

bool serialize(Serializer* serializer, const Buffer& buffer) {
    serializer->write(buffer.bytes());
    serializer->writeRaw(buffer.data(), buffer.bytes());
    return true;
}

bool deserialize(Deserializer* deserializer, Buffer* buffer) {
    int count = 0;
    if (!deserializer->read(&count)) {
        return false;
    }

    const byte* const data = deserializer->readRaw(count);
    if (data == NULL)
    {
        return false;
    }

    buffer->setData(data, count);
    return true;
}

bool serialize(Serializer* serializer, const PacketHeader& packet) {
    return
        serializer->write(packet.magic) &&
        serializer->write(packet.id) &&
        serializer->write(packet.size);
}

bool deserialize(Deserializer* deserializer, PacketHeader* packet) {
    return
        deserializer->read(&packet->magic) &&
        deserializer->read(&packet->id) &&
        deserializer->read(&packet->size);
}

bool serialize(Serializer* serializer, const PacketInvokeRequest& packet) {
    return
        serializer->write(packet.function) &&
        serializer->write(packet.taskId) &&
        serializer->write(packet.data);
}

bool deserialize(Deserializer* deserializer, PacketInvokeRequest* packet) {
    return
        deserializer->read(&packet->function) &&
        deserializer->read(&packet->taskId) &&
        deserializer->read(&packet->data);
}

bool serialize(Serializer* serializer, const PacketInvokeReply& packet) {
    return
        serializer->write(packet.flags) &&
        serializer->write(packet.taskId) &&
        serializer->write(packet.data);
}

bool deserialize(Deserializer* deserializer, PacketInvokeReply* packet) {
    return
        deserializer->read(&packet->flags) &&
        deserializer->read(&packet->taskId) &&
        deserializer->read(&packet->data);
}


}
