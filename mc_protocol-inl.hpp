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


template <typename P1>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1) {
    PacketInvokeRequest packetRequest;

    Serializer serializer(&packetRequest.data);
    serializer.write(p1);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2) {
    PacketInvokeRequest packetRequest;

    Serializer serializer(&packetRequest.data);
    serializer.write(p1);
    serializer.write(p2);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3) {
    PacketInvokeRequest packetRequest;

    Serializer serializer(&packetRequest.data);
    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3 & p3, const P4& p4) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4, typename P5>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);
    serializer.write(p5);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);
    serializer.write(p5);
    serializer.write(p6);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);
    serializer.write(p5);
    serializer.write(p6);
    serializer.write(p7);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);
    serializer.write(p5);
    serializer.write(p6);
    serializer.write(p7);
    serializer.write(p8);

    return invokeExec(token, &packetRequest);
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
Protocol::TaskId Protocol::invoke(const Token& token, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6, const P7& p7, const P8& p8, const P9& p9) {
    PacketInvokeRequest packetRequest;
    Serializer serializer(&packetRequest.data);

    serializer.write(p1);
    serializer.write(p2);
    serializer.write(p3);
    serializer.write(p4);
    serializer.write(p5);
    serializer.write(p6);
    serializer.write(p7);
    serializer.write(p8);
    serializer.write(p9);

    return invokeExec(token, &packetRequest);
}

template <typename R>
Protocol::TaskState Protocol::queryResult(TaskId id, R* result) {
    TaskMap::const_iterator iter = m_taskMap.find(id);
    if (iter == m_taskMap.end()) {
        return TASK_STATE_UNDEFINED;
    }

    TaskEntry& entry = iter->second;
    if (entry.state == TASK_STATE_READY) {
        Deserializer deserializer(&entry.data);
        if (!deserializer.read(result)) {
            entry.state = TASK_STATE_ERROR;
        }
    }

    return entry.state;
}


}
