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
#include "mc_prefab.hpp"

namespace metacall {


//
// Local functions
//

template <typename T>
static int genStrLen(const T str[]) {
    int length = 0;
    while (str[length] != 0) {
        ++length;
    }

    return length;
}

template <typename T>
static bool serializeStr(Serializer* serializer, const T str[]) {
    serializer->writeRaw(str, sizeof(T) * (genStrLen(str) + 1));
    return true;
}

template <typename T>
static bool deserializeStr(Deserializer* deserializer, const T ** str) {
    *str = reinterpret_cast<const T*>(deserializer->readRaw(1));
    if (*str == NULL) {
        return false;
    }

    return deserializer->readRaw(genStrLen(*str)) != NULL;
}


//
// Shared functions
//

bool serialize(Serializer* serializer, const char str[]) {
    return serializeStr(serializer, str);
}

bool deserialize(Deserializer* deserializer, const char ** str) {
    return deserializeStr(deserializer, str);
}

bool serialize(Serializer* serializer, const wchar_t str[]) {
    return serializeStr(serializer, str);
}

bool deserialize(Deserializer* deserializer, const wchar_t ** str) {
    return deserializeStr(deserializer, str);
}


}
