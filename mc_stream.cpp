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
#include "mc_stream.hpp"

namespace metacall {


//
// Constants
//

enum {
    SOCKET_BUFFER_SIZE = 1024
};


//
// Stream
//

Stream::Stream(Socket* socket) :
    socket_(socket)
{
}

Stream::State Stream::advance() {
    if (!socket_->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    if (buffSend_.bytes() > 0 && socket_->wait(Socket::MASK_WRITE, 0)) {
        const int bytesSent = socket_->send(
            buffSend_.data(),
            buffSend_.bytes()
        );

        if (bytesSent <= 0) {
            return STATE_ERROR_CONNECTION;
        }

        buffSend_.removeFromFront(NULL, bytesSent);
    }

    if (socket_->wait(Socket::MASK_READ, 0)) {
        byte buffRecv[SOCKET_BUFFER_SIZE];
        const int bytesRecv = socket_->receive(
            buffRecv,
            sizeof(buffRecv)
        );

        if (bytesRecv <= 0) {
            return STATE_ERROR_CONNECTION;
        }

        buffRecv_.addToBack(buffRecv, bytesRecv);
    }

    return STATE_READY;
}

void Stream::reset() {
    buffSend_.clear();
    buffRecv_.clear();
}

Stream::State Stream::peek(PacketHeader* header, int* headerSize) {
    if (!socket_->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    Deserializer deserializer(&buffRecv_);
    if (!deserializer.read(header)) {
        return STATE_PENDING_PACKET_HEADER;
    }

    if (header->magic != PACKET_CONST_MAGIC) {
        return STATE_ERROR_PROTOCOL;
    }

    *headerSize = deserializer.offset();

    const int packetSize = static_cast<int>(header->size) + *headerSize;
    if (buffRecv_.bytes() < packetSize) {
        return STATE_PENDING_PACKET_BODY;
    }

    return STATE_READY;
}

const Socket* Stream::socket() const {
    return socket_;
}

Socket* Stream::socket() {
    return socket_;
}


}
