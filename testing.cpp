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
#define TEST_VECTOR
#define TEST_LIST
#define TEST_PAIR
#define TEST_MAP


//
// C string
//

#ifdef TEST_C_STRING

static void testCStringAnsiImp(const char str[]) {
    printf("[testCStringAnsiImp]: '%s'\n", str);
}

static void testCStringUnicodeImp(const wchar_t str[]) {
    printf("[testCStringUnicodeImp]: '%S'\n", str);
}

static void testCString(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testCStringAnsiImp));
    binding->bind(FPARAM(testCStringUnicodeImp));

    const char* stringsAnsi[] = { "Hello world", "", NULL };
    for (int i = 0; i < 3; ++i) {
        protocol->invoke("testCStringAnsiImp", stringsAnsi[i]);
    }

    const wchar_t* stringsUnicode[] = { L"Hello world", L"", NULL };
    for (int i = 0; i < 3; ++i) {
        protocol->invoke("testCStringUnicodeImp", stringsUnicode[i]);
    }
}

#endif


//
// std::basic_string
//

#ifdef TEST_BASIC_STRING

static void testBasicStringAnsiImp(const std::string& string) {
    printf("[testBasicStringAnsiImp]: '%s'\n", string.c_str());
}

static void testBasicStringUnicodeImp(const std::wstring& string) {
    wprintf(L"[testBasicStringUnicodeImp]: '%S'\n", string.c_str());
}

static void testBasicString(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testBasicStringAnsiImp));
    binding->bind(FPARAM(testBasicStringUnicodeImp));

    std::string stringsAnsi[] = { std::string("Hello world"), std::string() };
    for (int i = 0; i < 2; ++i) {
        protocol->invoke("testBasicStringAnsiImp", stringsAnsi[i]);
    }

    std::wstring stringsUnicode[] = { std::wstring(L"Hello world"), std::wstring() };
    for (int i = 0; i < 2; ++i) {
        protocol->invoke("testBasicStringUnicodeImp", stringsUnicode[i]);
    }
}

#endif


//
// std::vector
//

#ifdef TEST_VECTOR

static void testVectorImp(const std::vector<float>& vector) {
    printf("[testVectorImp]: ");

    for (std::vector<float>::const_iterator iter = vector.begin(); iter != vector.end(); ++iter) {
        printf("%f ", *iter);
    }

    printf("\n");
}

static void testVector(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testVectorImp));

    std::vector<float> vector;
    vector.push_back(3.14159f);
    vector.push_back(2.71828f);
    vector.push_back(1.61803f);

    protocol->invoke("testVectorImp", vector);
}

#endif


//
// std::list
//

#ifdef TEST_LIST

static void testListImp(const std::list<float>& list) {
    printf("[testListImp]: ");

    for (std::list<float>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
        printf("%f ", *iter);
    }

    printf("\n");
}

static void testList(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testListImp));

    std::list<float> list;
    list.push_back(3.14159f);
    list.push_back(2.71828f);
    list.push_back(1.61803f);

    protocol->invoke("testListImp", list);
}

#endif


//
// std::pair
//

#ifdef TEST_PAIR

static void testPairImp(const std::pair<float, int>& pair) {
    printf("[testPairImp]: (%f, %d)\n", pair.first, pair.second);
}

static void testPair(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testPairImp));
    protocol->invoke("testPairImp", std::make_pair<float, int>(3.14159f, 123));
}

#endif


//
// std::map
//

#ifdef TEST_MAP

static void testMapImp(const std::map<float, int>& map) {
    printf("[testMapImp]: ");

    for (std::map<float, int>::const_iterator iter = map.begin(); iter != map.end(); ++iter) {
        printf("(%f, %d) ", iter->first, iter->second);
    }

    printf("\n");
}

static void testMap(Binding* binding, Protocol* protocol) {
    binding->bind(FPARAM(testMapImp));

    std::map<float, int> map;
    map[3.14159f] = 123;
    map[2.71828f] = 456;
    map[1.61803f] = 789;

    protocol->invoke("testMapImp", map);
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

#ifdef TEST_VECTOR
        testVector(&binding, &protocol);
#endif

#ifdef TEST_LIST
        testList(&binding, &protocol);
#endif

#ifdef TEST_PAIR
        testPair(&binding, &protocol);
#endif

#ifdef TEST_MAP
        testMap(&binding, &protocol);
#endif

        server.advance();
        client.advance();
    }
    while (server.clientCount() > 0);

    return 0;
}
