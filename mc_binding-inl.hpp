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
// Binding
//

template <typename R>
bool Binding::bind(const Token& token, R(*function)()) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor0p<R>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1>
bool Binding::bind(const Token& token, R(*function)(P1)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor1p<R, P1>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2>
bool Binding::bind(const Token& token, R(*function)(P1, P2)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor2p<R, P1, P2>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor3p<R, P1, P2, P3>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor4p<R, P1, P2, P3, P4>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4, P5)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor5p<R, P1, P2, P3, P4, P5>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4, P5, P6)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor6p<R, P1, P2, P3, P4, P5, P6>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor7p<R, P1, P2, P3, P4, P5, P6, P7>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7, P8)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor8p<R, P1, P2, P3, P4, P5, P6, P7, P8>(function);
        return true;
    }

    return false;
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
bool Binding::bind(const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) {
    if (functors_.find(token) == functors_.end()) {
        functors_[token] = new Functor9p<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(function);
        return true;
    }

    return false;
}


}
