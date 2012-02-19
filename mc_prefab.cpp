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
// Local functions
//

static int strLen(const char str[]) {
    return strlen(str);
}

static int strLen(const wchar_t str[]) {
    return wcslen(str);
}

template <typename T>
static bool serializeStr(Serializer* serializer, const T value[]) {
    const int length = value == NULL ? 0 : strLen(value) + 1;
    serializer->write(length);
    serializer->writeRaw(value, length * sizeof(T));
    return true;
}

template <typename T>
static bool deserializeStr(Deserializer* deserializer, const T ** value) {
    *value = NULL;

    int length = 0;
    if (!deserializer->read(&length)) {
        return false;
    }

    if (length == 0) {
        return true;
    }

    *value = reinterpret_cast<const T*>(deserializer->readRaw(length * sizeof(T)));
    return *value != NULL;
}


//
// C strings
//

bool serialize(Serializer* serializer, const char value[]) {
    return serializeStr(serializer, value);
}

bool deserialize(Deserializer* deserializer, const char ** value) {
    return deserializeStr(deserializer, value);
}

bool serialize(Serializer* serializer, const wchar_t value[]) {
    return serializeStr(serializer, value);
}

bool deserialize(Deserializer* deserializer, const wchar_t ** value) {
    return deserializeStr(deserializer, value);
}


}
