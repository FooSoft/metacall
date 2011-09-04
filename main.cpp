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

#include <stdio.h>
#include "metacall.hpp"

using namespace metacall;


//
// Constants
//

static const int SERVER_PORT        = 1337;
static const int SERVER_MAX_CLIENTS = 1;


//
// Local functions
//

static void serverTest() {
    printf("Server test!\n");
}


//
// Program entry
//

int main(int argc, char **argv) {
    Server server;
    printf("[S] Starting server on port %d\n", SERVER_PORT);
    if (!server.start(SERVER_PORT, SERVER_MAX_CLIENTS)) {
        printf("[S] Unable to start server\n");
        return 1;
    }

    server.binding()->bind(FPARAM(serverTest));

    Client client;
    printf("[S] Connecting to server on port %d\n", SERVER_PORT);
    if (!client.connect("localhost", SERVER_PORT)) {
        printf("[C] Unable to connect to server\n");
        return 1;
    }

    while (true) {
        server.advance();
        client.protocol()->invoke("serverTest");
        client.advance();
    }

    return 0;
}
