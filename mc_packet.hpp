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
// Constants
//

enum PacketConst {
    PACKET_CONST_MAGIC      = 0x55534544,
    PACKET_CONST_VERSION    = 1
};

enum PacketId {
    PACKET_ID_INVALID,
    PACKET_ID_FUNCTION_CALL_REQUEST,
    PACKET_ID_FUNCTION_CALL_REPLY
};


//
// PacketHeader
//

struct PacketHeader {
    PacketHeader() :
        magic(0),
        id(PACKET_ID_INVALID),
        size(0)
    {
    }

    bool serialize(Serializer* serializer) const {
        return
            serializer->write(magic) &&
            serializer->write(id) &&
            serializer->write(size);
    }

    bool deserialize(Deserializer* deserializer) {
        return
            deserializer->read(&magic) &&
            deserializer->read(&id) &&
            deserializer->read(&size);
    }

    dword   magic;
    byte    id;
    dword   size;
};


//
// PacketInvokeRequest
//

struct PacketInvokeRequest {
    PacketInvokeRequest() :
        function(0),
        taskId(0)
    {
    }

    enum {
        Id = PACKET_ID_FUNCTION_CALL_REQUEST
    };

    bool serialize(Serializer* serializer) const {
        return
            serializer->write(function) &&
            serializer->write(taskId) &&
            serializer->write(data);
    }

    bool deserialize(Deserializer* deserializer) {
        return
            deserializer->read(&function) &&
            deserializer->read(&taskId) &&
            deserializer->read(&data);
    }

    dword   function;
    dword   taskId;
    Buffer  data;
};


//
// PacketInvokeReply
//

struct PacketInvokeReply {
    PacketInvokeReply() :
        flags(0),
        taskId(0)
    {
    }

    enum {
        Id = PACKET_ID_FUNCTION_CALL_REPLY
    };

    enum {
        FLAG_UNBOUND_FUNC = 1 << 0,
        FLAG_INVALID_ARGS = 1 << 1,
    };

    bool serialize(Serializer* serializer) const {
        return
            serializer->write(flags) &&
            serializer->write(taskId) &&
            serializer->write(data);
    }

    bool deserialize(Deserializer* deserializer) {
        return
            deserializer->read(&flags) &&
            deserializer->read(&taskId) &&
            deserializer->read(&data);
    }

    word    flags;
    dword   taskId;
    Buffer  data;
};


}
