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

static const int SERVER_PORT        = 1338;
static const int SERVER_MAX_CLIENTS = 1;


//
// Local variables
//

static bool executeServer = true;


//
// Local functions (bound)
//

static void serverStop() {
    printf("[S] Server stop request received\n");
    executeServer = false;
}


//
// Local functions
//

static void server() {
    Server server;

    printf("[S] Starting server on port %d\n", SERVER_PORT);
    if (!server.start(SERVER_PORT, SERVER_MAX_CLIENTS)) {
        perror("[S] Unable to start server");
        return;
    }

    printf("[S] Binding server functions\n");
    server.binding()->bind("serverStop", serverStop);

    printf("[S] Beginning client updates\n");
    while (executeServer) {
        server.advance();
    }

    printf("[S] Server shutting down");
    server.stop();
}

static void client() {
    Client client;

    printf("[C] Connecting to server on port %d...\n", SERVER_PORT);
    if (!client.connect("localhost", SERVER_PORT)) {
        perror("[C] Unable to connect to server\n");
        return;
    }

    printf("[C] Sending server shutdown request\n");
    client.protocol()->invoke("serverStop");

    while (client.connected()) {
        client.advance();
    }
}


//
// Program entry
//

int main(int argc, char **argv) {
	printf("[S] Starting server on port %d\n", SERVER_PORT);
	Server server;
	if (!server.start(SERVER_PORT, 1)) {
		printf("[S] Unable to start server\n");
		return 1;
	}


	printf("[S] Connecting to server on port %d\n", SERVER_PORT);
	Client client;
	if (!client.connect("localhost", SERVER_PORT)) {
		printf("[C] Unable to connect to server\n");
		return 1;
	}




    return 0;
}
