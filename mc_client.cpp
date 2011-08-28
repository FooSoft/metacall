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
#include "mc_client.hpp"

namespace metacall {


//
// Client
//

Client::Client() :
    stream_(&socket_),
    protocol_(&stream_, &binding_)
{
}

void Client::advance() {
    if (!socket_.opened()) {
        return;
    }

    if (socket_.connected()) {
        protocol_.advance();
    }
    else {
        disconnect();
    }
}

bool Client::connect(const char name[], int port) {
    disconnect();

    socket_.open();
    socket_.setNagle(false);

    if (!socket_.connect(name, port)) {
        disconnect();
        return false;
    }

    socket_.setBlocking(false);
    return true;
}

void Client::disconnect() {
    protocol_.clearHandlers();
    stream_.reset();
    socket_.close();
}

bool Client::connected() const {
    return socket_.connected();
}

const Protocol* Client::protocol() const {
    return &protocol_;
}

Protocol* Client::protocol() {
    return &protocol_;
}

const Binding* Client::binding() const {
    return &binding_;
}

Binding* Client::binding() {
    return &binding_;
}


}
