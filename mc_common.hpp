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
// Macros
//

#define ASSERT      assert
#define FPARAM(x)   #x, x


//
// Types
//

#ifdef _WIN32
    typedef unsigned __int8     byte;
    typedef unsigned __int16    word;
    typedef unsigned __int32    dword;
    typedef unsigned __int64    qword;
#else
    typedef unsigned char       byte;
    typedef unsigned short      word;
    typedef unsigned int        dword;
    typedef unsigned long int   qword;
#endif


//
// Forward declarations
//

class Serializer;
class Deserializer;


}
