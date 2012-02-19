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
#include "mc_buffer.hpp"

namespace metacall {


//
// Buffer
//

Buffer::Buffer(const void* data, int count) {
    setData(data, count);
}

Buffer::Buffer() {

}

void Buffer::addToBack(const void* data, int bytes) {
    m_data.insert(
        m_data.end(),
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

void Buffer::addToFront(const void* data, int bytes) {
    m_data.insert(
        m_data.begin(),
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

int Buffer::removeFromFront(void* data, int bytes) {
    bytes = std::min(static_cast<size_t>(bytes), m_data.size());
    if (data != NULL) {
        memcpy(data, &m_data[0], bytes);
    }

    m_data.erase(m_data.begin(), m_data.begin() + bytes);
    return bytes;
}

int Buffer::removeFromBack(void* data, int bytes) {
    bytes = std::min(static_cast<size_t>(bytes), m_data.size());
    if (data != NULL) {
        memcpy(data, &m_data[m_data.size() - bytes], bytes);
    }

    m_data.erase(m_data.end() - bytes, m_data.end());
    return bytes;
}

void Buffer::clear() {
    m_data.clear();
}

void Buffer::setData(const void* data, int bytes) {
    m_data.assign(
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

const void* Buffer::data() const {
    return bytes() == 0 ? NULL : &m_data[0];
}

void* Buffer::data() {
    return bytes() == 0 ? NULL : &m_data[0];
}

int Buffer::bytes() const {
    return m_data.size();
}

bool Buffer::serialize(Serializer* serializer) const {
    serializer->write(bytes());
    serializer->writeRaw(data(), bytes());
    return true;
}

bool Buffer::deserialize(Deserializer* deserializer) {
    int count = 0;
    if (!deserializer->read(&count)) {
        return false;
    }

    const byte* const data = deserializer->readRaw(count);
    if (data == NULL) {
        return false;
    }

    setData(data, count);
    return true;
}


}
