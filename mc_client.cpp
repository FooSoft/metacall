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
// Client
//

Client::Client() :
    m_stream(&m_socket),
    m_protocol(&m_stream, &m_binding)
{
}

void Client::advance() {
    if (!m_socket.opened()) {
        return;
    }

    if (m_socket.connected()) {
        m_protocol.advance();
    }
    else {
        disconnect();
    }
}

bool Client::connect(const char name[], int port) {
    disconnect();

    m_socket.open();
    m_socket.setNagle(false);

    if (!m_socket.connect(name, port)) {
        disconnect();
        return false;
    }

    m_socket.setBlocking(false);
    return true;
}

void Client::disconnect() {
    m_protocol.clearHandlers();
    m_stream.reset();
    m_socket.close();
}

bool Client::connected() const {
    return m_socket.connected();
}

const Protocol* Client::protocol() const {
    return &m_protocol;
}

Protocol* Client::protocol() {
    return &m_protocol;
}

const Binding* Client::binding() const {
    return &m_binding;
}

Binding* Client::binding() {
    return &m_binding;
}


}
