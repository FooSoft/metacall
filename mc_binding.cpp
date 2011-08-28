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
// Binding
//

Binding::~Binding() {
    unbindAll();
}

Binding::CallResult Binding::call(const Token& token, Deserializer* args, Serializer* ret) const {
    const FunctorMap::const_iterator iter = functors_.find(token);

    if (iter == functors_.end()) {
        return CALL_RESULT_UNBOUND_FUNC;
    }
    if (!iter->second->call(args, ret)) {
        return CALL_RESULT_INVALID_ARGS;
    }

    return CALL_RESULT_SUCCESS;
}

void Binding::unbind(const Token& token) {
    FunctorMap::iterator iter = functors_.find(token);
    if (iter != functors_.end()) {
        delete iter->second;
        functors_.erase(iter);
    }
}

void Binding::unbindAll() {
    for (FunctorMap::iterator iter = functors_.begin(); iter != functors_.end(); ++iter) {
        delete iter->second;
    }

    functors_.clear();
}


}
