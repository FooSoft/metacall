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

#define TEST_UNICODE
#define TEST_ANSI
#define TEST_C_STRING
#define TEST_BASIC_STRING


//
// C string
//

static void testCStrAnsi(const char str[]) {
    printf("[testCStrAnsi]: '%s'\n", str);
}

static void testCStrUnicode(const wchar_t str[]) {
    printf("[testCStrUnicode]: '%S'\n", str);
}


//
// std::basic_string
//

static void testBasicStringAnsi(const std::string& str) {
    printf("[testBasicStringAnsi]: '%s'\n", str.c_str());
}

static void testBasicStringUnicode(const std::wstring& str) {
    wprintf(L"[testBasicStringUnicode]: '%S'\n", str.c_str());
}



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
        //
        // C string
        //
#ifdef TEST_C_STRING
        {
            binding.bind(FPARAM(testCStrAnsi));
            binding.bind(FPARAM(testCStrUnicode));

            //
            // ANSI
            //
#ifdef TEST_ANSI
            {
                const char* strings[] = { "Hello world", "", NULL };
                for (int i = 0; i < 3; ++i) {
                    protocol.invoke("testCStrAnsi", strings[i]);
                }
            }
#endif
            //
            // Unicode
            //
#ifdef TEST_UNICODE
            {
                const wchar_t* strings[] = { L"Hello world", L"", NULL };
                for (int i = 0; i < 3; ++i) {
                    protocol.invoke("testCStrUnicode", strings[i]);
                }
            }
#endif
        }
#endif

        //
        // std::basic_string
        //
#ifdef TEST_BASIC_STRING
        {
            binding.bind(FPARAM(testBasicStringAnsi));
            binding.bind(FPARAM(testBasicStringUnicode));

            //
            // ANSI
            //
#ifdef TEST_ANSI
            {
                std::string strings[] = { std::string("Hello world"), std::string() };
                for (int i = 0; i < 2; ++i) {
                    protocol.invoke("testBasicStringAnsi", strings[i]);
                }
            }
#endif
            //
            // Unicode
            //
#ifdef TEST_UNICODE
            {
                std::wstring strings[] = { std::wstring(L"Hello world"), std::wstring() };
                for (int i = 0; i < 2; ++i) {
                    protocol.invoke("testBasicStringUnicode", strings[i]);
                }
            }
#endif
        }
#endif

        server.advance();
        client.advance();
    }
    while (server.clientCount() > 0);

    return 0;
}
