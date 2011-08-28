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
// IFunctor
//

class IFunctor {
public:
    virtual bool call(Deserializer* args, Serializer* ret) const = 0;
};


//
// Functor0p
//

template <typename R>
class Functor0p : public IFunctor {
public:
    typedef R(*F)();

    Functor0p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer*, Serializer* ret) const {
        ret->write(function_());
        return true;
    }

private:
    F function_;
};

template <>
class Functor0p<void> : public IFunctor {
public:
    typedef void(*F)();

    Functor0p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer*, Serializer*) const {
        function_();
        return true;
    }

private:
    F function_;
};


//
// Functor1p
//

template <typename R, typename P1>
class Functor1p : public IFunctor {
public:
    typedef R (*F)(P1);

    Functor1p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;

        const bool success = args->read(&p1);
        if (success) {
            ret->write(function_(p1));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1>
class Functor1p<void, P1> : public IFunctor {
public:
    typedef void (*F)(P1);

    Functor1p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;

        const bool success = args->read(&p1);
        if (success) {
            function_(p1);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor2p
//

template <typename R, typename P1, typename P2>
class Functor2p : public IFunctor {
public:
    typedef R (*F)(P1, P2);

    Functor2p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;

        const bool success =
            args->read(&p1) &&
            args->read(&p2);

        if (success) {
            ret->write(function_(p1, p2));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2>
class Functor2p<void, P1, P2> : public IFunctor {
public:
    typedef void (*F)(P1, P2);

    Functor2p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;

        const bool success =
            args->read(&p1) &&
            args->read(&p2);

        if (success) {
            function_(p1, p2);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor3p
//

template <typename R, typename P1, typename P2, typename P3>
class Functor3p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3);

    Functor3p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3);

        if (success) {
            ret->write(function_(p1, p2, p3));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3>
class Functor3p<void, P1, P2, P3> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3);

    Functor3p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3);

        if (success) {
            function_(p1, p2, p3);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor4p
//

template <typename R, typename P1, typename P2, typename P3, typename P4>
class Functor4p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4);

    Functor4p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4);

        if (success) {
            ret->write(function_(p1, p2, p3, p4));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4>
class Functor4p<void, P1, P2, P3, P4> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4);

    Functor4p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4);

        if (success) {
            function_(p1, p2, p3, p4);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor5p
//

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class Functor5p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4, P5);

    Functor5p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5);

        if (success) {
            ret->write(function_(p1, p2, p3, p4, p5));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5>
class Functor5p<void, P1, P2, P3, P4, P5> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4, P5);

    Functor5p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5);

        if (success) {
            function_(p1, p2, p3, p4, p5);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor6p
//

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Functor6p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4, P5, P6);

    Functor6p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6);

        if (success) {
            ret->write(function_(p1, p2, p3, p4, p5, p6));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Functor6p<void, P1, P2, P3, P4, P5, P6> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4, P5, P6);

    Functor6p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6);

        if (success) {
            function_(p1, p2, p3, p4, p5, p6);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor7p
//

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class Functor7p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4, P5, P6, P7);

    Functor7p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7);

        if (success) {
            ret->write(function_(p1, p2, p3, p4, p5, p6, p7));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class Functor7p<void, P1, P2, P3, P4, P5, P6, P7> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4, P5, P6, P7);

    Functor7p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7);

        if (success) {
            function_(p1, p2, p3, p4, p5, p6, p7);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor8p
//

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class Functor8p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4, P5, P6, P7, P8);

    Functor8p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;
        typename StripConstRef<P8>::Type p8;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7) &&
            args->read(&p8);

        if (success) {
            ret->write(function_(p1, p2, p3, p4, p5, p6, p7, p8));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class Functor8p<void, P1, P2, P3, P4, P5, P6, P7, P8> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4, P5, P6, P7, P8);

    Functor8p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;
        typename StripConstRef<P8>::Type p8;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7) &&
            args->read(&p8);

        if (success) {
            function_(p1, p2, p3, p4, p5, p6, p7, p8);
        }

        return success;
    }

private:
    F function_;
};


//
// Functor9p
//

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class Functor9p : public IFunctor {
public:
    typedef R (*F)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

    Functor9p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer* ret) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;
        typename StripConstRef<P8>::Type p8;
        typename StripConstRef<P9>::Type p9;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7) &&
            args->read(&p8) &&
            args->read(&p9);

        if (success) {
            ret->write(function_(p1, p2, p3, p4, p5, p6, p7, p8, p9));
        }

        return success;
    }

private:
    F function_;
};

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
class Functor9p<void, P1, P2, P3, P4, P5, P6, P7, P8, P9> : public IFunctor {
public:
    typedef void (*F)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

    Functor9p(F function) :
        function_(function)
    {
    }

    bool call(Deserializer* args, Serializer*) const {
        typename StripConstRef<P1>::Type p1;
        typename StripConstRef<P2>::Type p2;
        typename StripConstRef<P3>::Type p3;
        typename StripConstRef<P4>::Type p4;
        typename StripConstRef<P5>::Type p5;
        typename StripConstRef<P6>::Type p6;
        typename StripConstRef<P7>::Type p7;
        typename StripConstRef<P8>::Type p8;
        typename StripConstRef<P9>::Type p9;

        const bool success =
            args->read(&p1) &&
            args->read(&p2) &&
            args->read(&p3) &&
            args->read(&p4) &&
            args->read(&p5) &&
            args->read(&p6) &&
            args->read(&p7) &&
            args->read(&p8) &&
            args->read(&p9);

        if (success) {
            function_(p1, p2, p3, p4, p5, p6, p7, p8, p9);
        }

        return success;
    }

private:
    F function_;
};


}
