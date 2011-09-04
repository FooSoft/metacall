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
#include "mc_serial.hpp"

namespace metacall {


//
// Deserializer
//

Deserializer::Deserializer(const Buffer* data) :
    data_(data),
    offset_(0)
{
}

const byte* Deserializer::readRaw(int size) {
    if (data_ == NULL || size > data_->bytes() - offset_) {
        return NULL;
    }

    const byte* data = static_cast<const byte*>(data_->data()) + offset_;
    offset_ += size;

    return data;
}

int Deserializer::offset() const {
    return offset_;
}

bool Deserializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? offset_ + offset : offset;

    if (offsetNew >= 0 && offsetNew <= data_->bytes()) {
        offset_ = offsetNew;
        return true;
    }

    return false;
}


//
// Serializer
//

Serializer::Serializer(Buffer* data) :
    data_(data),
    offset_(0)
{
}

bool Serializer::writeRaw(const void* data, int size) {
    if (data_ != NULL) {
        data_->addToBack(static_cast<const byte*>(data), size);
        offset_ += size;
    }

    return true;
}

bool Serializer::setOffset(int offset, bool relative) {
    const int offsetNew = relative ? offset_ + offset : offset;

    if (offsetNew >= 0 && offsetNew <= data_->bytes()) {
        offset_ = offsetNew;
        return true;
    }

    return false;
}

int Serializer::offset() const {
    return offset_;
}


}
