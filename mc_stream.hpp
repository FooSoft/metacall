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

#pragma once

namespace metacall {


//
// Stream
//

class Stream {
 public:
    enum State {
        STATE_READY,
        STATE_PENDING_PACKET_HEADER,
        STATE_PENDING_PACKET_BODY,
        STATE_ERROR_PROTOCOL,
        STATE_ERROR_CONNECTION
    };

    Stream(Socket* socket);

    State           advance();
    void            reset();

    template        <typename T>
    State           send(const T& packet);
    template        <typename T>
    State           receive(T* packet);
    State           peek(PacketHeader* header, int* headerSize);

    const Socket*   socket() const;
    Socket*         socket();

 private:
    Socket*         m_socket;
    Buffer          m_buffRecv;
    Buffer          m_buffSend;
};


}
