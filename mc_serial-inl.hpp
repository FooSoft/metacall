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

namespace metacall {


//
// TypeReader
//

template <typename T, bool S>
struct TypeReader {
    static bool read(Deserializer* deserializer, T* data) {
        return data->deserialize(deserializer);
    }
};

template <typename T>
struct TypeReader<T, false> {
    static bool read(Deserializer* deserializer, T* data) {
        const T* const temp = reinterpret_cast<const T*>(
            deserializer->readRaw(sizeof(T))
        );

        if (temp != NULL) {
            *data = *temp;
        }

        return temp != NULL;
    }
};

template <typename T>
bool Deserializer::read(T* data) {
    return deserialize(this, data);
}


//
// TypeWriter
//

template <typename T, bool S>
struct TypeWriter {
    static void write(Serializer* serializer, const T& data) {
        data.serialize(serializer);
    }
};

template <typename T>
struct TypeWriter<T, false> {
    static void write(Serializer* serializer, const T& data) {
        serializer->writeRaw(&data, sizeof(T));
    }
};

template <typename T>
void Serializer::write(const T& data) {
    serialize(this, data);
}


//
// Handlers
//

template <typename T>
void serialize(Serializer* serializer, const T& data) {
    TypeWriter<T, HasSerializer<T>::Value>::write(serializer, data);
}

template <typename T>
bool deserialize(Deserializer* deserializer, T* data) {
    return TypeReader<T, HasDeserializer<T>::Value>::read(deserializer, data);
}


}
