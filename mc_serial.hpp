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
// Deserializer
//

class Deserializer {
public:
    Deserializer(const Buffer* data);

    template        <typename T>
    bool            read        (T* data);
    const byte*     readRaw     (int size);
    bool            setOffset   (int offset, bool relative);
    int             offset      () const;

private:
    const Buffer*   data_;
    int             offset_;
};


//
// Serializer
//

class Serializer {
public:
    Serializer(Buffer* data);

    template    <typename T>
    bool        write       (const T& data);
    bool        writeRaw    (const void* data, int size);
    bool        setOffset   (int offset, bool relative);
    int         offset      () const;

private:
    Buffer* data_;
    int     offset_;
};


//
// ArrayWriter
//

template <typename T>
class ArrayWriter {
public:
    ArrayWriter(const T* data, int count) :
        data(data),
        count(count)
    {
    }

    const T*    data;
    int         count;
};


//
// ArrayReader
//

template <typename T>
class ArrayReader {
public:
    ArrayReader() :
        data(NULL),
        count(0)
    {
    }

    ~ArrayReader() {
        delete[] data;

        data    = NULL;
        count   = 0;
    }

    const T*    data;
    int         count;
};


//
// Standard serializers/deserializers
//

template    <typename T>
bool        serialize   (Serializer* serializer, const ArrayWriter<T>& writer);
template    <typename T>
bool        deserialize (Deserializer* deserializer, ArrayReader<T>* reader);

bool        serialize   (Serializer* serializer, const Buffer& buffer);
bool        deserialize (Deserializer* deserializer, Buffer* buffer);

bool        serialize   (Serializer* serializer, const PacketHeader& packet);
bool        deserialize (Deserializer* deserializer, PacketHeader* packet);

bool        serialize   (Serializer* serializer, const PacketInvokeRequest& packet);
bool        deserialize (Deserializer* deserializer, PacketInvokeRequest* packet);

bool        serialize   (Serializer* serializer, const PacketInvokeReply& packet);
bool        deserialize (Deserializer* deserializer, PacketInvokeReply* packet);


}
