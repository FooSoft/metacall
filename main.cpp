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
// Defines
//

#define TEST_C_STRING
#define TEST_BASIC_STRING


//
// C string
//

#ifdef TEST_C_STRING

static void testCStringAnsi(const char str[]) {
    printf("[testCStringAnsi]: '%s'\n", str);
}

static void testCStringUnicode(const wchar_t str[]) {
    printf("[testCStringUnicode]: '%S'\n", str);
}

static void testCString(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testCStringAnsi));
    binding->bind(FPARAM(testCStringUnicode));

    const char* stringsAnsi[] = { "Hello world", "", NULL };
    for (int i = 0; i < 3; ++i) {
        protocol->invoke("testCStringAnsi", stringsAnsi[i]);
    }

    const wchar_t* stringsUnicode[] = { L"Hello world", L"", NULL };
    for (int i = 0; i < 3; ++i) {
        protocol->invoke("testCStringUnicode", stringsUnicode[i]);
    }
}

#endif


//
// std::basic_string
//

#ifdef TEST_BASIC_STRING

static void testBasicStringAnsi(const std::string& str) {
    printf("[testBasicStringAnsi]: '%s'\n", str.c_str());
}

static void testBasicStringUnicode(const std::wstring& str) {
    wprintf(L"[testBasicStringUnicode]: '%S'\n", str.c_str());
}

static void testBasicString(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testBasicStringAnsi));
    binding->bind(FPARAM(testBasicStringUnicode));

    std::string stringsAnsi[] = { std::string("Hello world"), std::string() };
    for (int i = 0; i < 2; ++i) {
        protocol->invoke("testBasicStringAnsi", stringsAnsi[i]);
    }

    std::wstring stringsUnicode[] = { std::wstring(L"Hello world"), std::wstring() };
    for (int i = 0; i < 2; ++i) {
        protocol->invoke("testBasicStringUnicode", stringsUnicode[i]);
    }
}

#endif



//
// Program entry
//

int main(int, char *[]) {
    const int port = 1234;

    Server server;
    if (!server.start(port)) {
        perror("Cannot start server\n");
        return 1;
    }

    Client client;
    if (!client.connect("localhost", port)) {
        perror("Cannot connect to server\n");
        return 1;
    }

    Binding&    binding     = server.binding();
    Protocol&   protocol    = client.protocol();

    do {
#ifdef TEST_C_STRING
        testCString(&binding, &protocol);
#endif

#ifdef TEST_BASIC_STRING
        testBasicString(&binding, &protocol);
#endif

        server.advance();
        client.advance();
    }
    while (server.clientCount() > 0);

    return 0;
}
