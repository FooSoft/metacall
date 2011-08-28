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
// Types
//

enum TaskId {
    TASK_ID_INVALID
};

enum TaskState {
    TASK_STATE_UNDEFINED,
    TASK_STATE_PENDING,
    TASK_STATE_READY,
    TASK_STATE_ERROR
};

typedef void (*HandlerProc)(
    class Protocol* protocol,
    TaskId          id,
    TaskState       state,
    void*           userPtr
);


//
// Protocol
//

class Protocol {
public:
    Protocol(Stream* stream, Binding* binding);

    void            advance             ();

    void            setRate             (int rate);
    bool            setHandler          (TaskId id, HandlerProc handler, void* userPtr = NULL);
    void            clearHandler        (TaskId id);
    void            clearHandlers       ();

    template        <typename R>
    TaskState       queryResult         (TaskId id, R* result);
    TaskState       queryState          (TaskId id) const;

    TaskId          invoke              (const Token& token);
    template        <typename P1>
    TaskId          invoke              (const Token& token, const P1& p0);
    template        <typename P1, typename P2>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1);
    template        <typename P1, typename P2, typename P3>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2);
    template        <typename P1, typename P2, typename P3, typename P4>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3);
    template        <typename P1, typename P2, typename P3, typename P4, typename P5>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3, const P5& p4);
    template        <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3, const P5& p4, const P6& p5);
    template        <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3, const P5& p4, const P6& p5, const P7& p6);
    template        <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3, const P5& p4, const P6& p5, const P7& p6, const P8& p7);
    template        <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
    TaskId          invoke              (const Token& token, const P1& p0, const P2& p1, const P3& p2, const P4& p3, const P5& p4, const P6& p5, const P7& p6, const P8& p7, const P9& p8);

private:
    struct HandlerEntry {
        HandlerEntry(HandlerProc handler, void* userPtr) :
            handler(handler),
            userPtr(userPtr)
        {
        }

        HandlerProc handler;
        void*       userPtr;
    };

    struct TaskEntry {
        TaskEntry() :
            state(TASK_STATE_PENDING)
        {
        }

        typedef     std::vector<HandlerEntry> HandlerList;
        HandlerList handlers;
        TaskState   state;
        Buffer      data;
    };

    Stream::State   advanceStream       ();
    Stream::State   advanceInvokeRequest();
    Stream::State   advanceInvokeReply  ();

    TaskId          invokeExec          (const Token& token, PacketInvokeRequest* packetRequest);
    static TaskId   registerTaskId      ();

    typedef         std::map<TaskId, TaskEntry> TaskMap;
    TaskMap         taskMap_;
    Stream*         stream_;
    Binding*        binding_;
    int             rate_;
};


}
