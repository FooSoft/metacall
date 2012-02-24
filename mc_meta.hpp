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
// Meta
//

template <typename T>
struct HasSerializer {
    template <typename U, void (U::*)(Serializer*) const>
    struct Signature { };

    template <typename U>
    static dword Test(Signature<U, &U::serialize>*);

    template <typename U>
    static qword Test(...);

    enum {
        Value = sizeof(Test<T>(NULL)) == sizeof(dword)
    };
};

template <typename T>
struct HasDeserializer {
    template <typename U, bool (U::*)(Deserializer*)>
    struct Signature { };

    template <typename U>
    static dword Test(Signature<U, &U::deserialize>*);

    template <typename U>
    static qword Test(...);

    enum {
        Value = sizeof(Test<T>(NULL)) == sizeof(dword)
    };
};

template <typename T>
struct StripRef {
    typedef T Type;
};

template <typename T>
struct StripRef<T&> {
    typedef T Type;
};

template <typename T>
struct StripConst {
    typedef T Type;
};

template <typename T>
struct StripConst<const T> {
    typedef T Type;
};

template <typename T>
struct StripConstRef {
    typedef typename StripConst<typename StripRef<T>::Type >::Type Type;
};


}
