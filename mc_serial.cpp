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
// Deserializer
//

Deserializer::Deserializer(const Buffer* data) :
    m_data(data),
    m_offset(0)
{
}

const byte* Deserializer::readRaw(int size) {
    if (m_data == NULL || size > m_data->bytes() - m_offset) {
        return NULL;
    }

    const byte* data = static_cast<const byte*>(m_data->data()) + m_offset;
    m_offset += size;

    return data;
}

int Deserializer::offset() const {
    return m_offset;
}

bool Deserializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? m_offset + offset : offset;

    if (offsetNew >= 0 && offsetNew <= m_data->bytes()) {
        m_offset = offsetNew;
        return true;
    }

    return false;
}


//
// Serializer
//

Serializer::Serializer(Buffer* data) :
    m_data(data),
    m_offset(0)
{
}

bool Serializer::writeRaw(const void* data, int size) {
    if (m_data != NULL) {
        m_data->addToBack(static_cast<const byte*>(data), size);
        m_offset += size;
    }

    return true;
}

bool Serializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? m_offset + offset : offset;

    if (offsetNew >= 0 && offsetNew <= m_data->bytes()) {
        m_offset = offsetNew;
        return true;
    }

    return false;
}

int Serializer::offset() const {
    return m_offset;
}


}
