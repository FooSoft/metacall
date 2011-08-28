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
// Binding
//

class Binding {
public:
    enum CallResult {
        CALL_RESULT_SUCCESS,
        CALL_RESULT_INVALID_ARGS,
        CALL_RESULT_UNBOUND_FUNC
    };

    ~Binding();

    template    <typename R>
    bool        bind        (const Token& token, R(*function)());
    template    <typename R, typename P1>
    bool        bind        (const Token& token, R(*function)(P1));
    template    <typename R, typename P1, typename P2>
    bool        bind        (const Token& token, R(*function)(P1, P2));
    template    <typename R, typename P1, typename P2, typename P3>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3));
    template    <typename R, typename P1, typename P2, typename P3, typename P4>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4));
    template    <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4, P5));
    template    <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4, P5, P6));
    template    <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7));
    template    <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7, P8));
    template    <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
    bool        bind        (const Token& token, R(*function)(P1, P2, P3, P4, P5, P6, P7, P8, P9));

    CallResult  call        (const Token& token, Deserializer* args, Serializer* ret) const;
    void        unbind      (const Token& token);
    void        unbindAll   ();

private:
    typedef     std::map<unsigned, IFunctor*> FunctorMap;
    FunctorMap  functors_;
};


}
