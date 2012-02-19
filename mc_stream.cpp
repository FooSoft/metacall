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
    m_socket(socket)
{
}

Stream::State Stream::advance() {
    if (!m_socket->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    if (m_buffSend.bytes() > 0 && m_socket->wait(Socket::MASK_WRITE, 0)) {
        const int bytesSent = m_socket->send(
            m_buffSend.data(),
            m_buffSend.bytes()
        );

        if (bytesSent <= 0) {
            return STATE_ERROR_CONNECTION;
        }

        m_buffSend.removeFromFront(NULL, bytesSent);
    }

    if (m_socket->wait(Socket::MASK_READ, 0)) {
        byte buffRecv[SOCKET_BUFFER_SIZE];
        const int bytesRecv = m_socket->receive(
            buffRecv,
            sizeof(buffRecv)
        );

        if (bytesRecv <= 0) {
            return STATE_ERROR_CONNECTION;
        }

        m_buffRecv.addToBack(buffRecv, bytesRecv);
    }

    return STATE_READY;
}

void Stream::reset() {
    m_buffSend.clear();
    m_buffRecv.clear();
}

Stream::State Stream::peek(PacketHeader* header, int* headerSize) {
    if (!m_socket->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    Deserializer deserializer(&m_buffRecv);
    if (!deserializer.read(header)) {
        return STATE_PENDING_PACKET_HEADER;
    }

    if (header->magic != PACKET_CONST_MAGIC) {
        return STATE_ERROR_PROTOCOL;
    }

    *headerSize = deserializer.offset();

    const int packetSize = static_cast<int>(header->size) + *headerSize;
    if (m_buffRecv.bytes() < packetSize) {
        return STATE_PENDING_PACKET_BODY;
    }

    return STATE_READY;
}

const Socket* Stream::socket() const {
    return m_socket;
}

Socket* Stream::socket() {
    return m_socket;
}


}
