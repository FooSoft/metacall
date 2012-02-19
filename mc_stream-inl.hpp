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


template <typename T>
Stream::State Stream::send(const T& packet) {
    if (!m_socket->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    Buffer buffTemp;
    Serializer serializerTemp(&buffTemp);
    serializerTemp.write(packet);

    const PacketHeader header(
        PACKET_CONST_MAGIC,
        T::Id,
        serializerTemp.offset()
    );

    Serializer serializerSend(&m_buffSend);
    serializerSend.write(header);
    serializerSend.writeRaw(buffTemp.data(), buffTemp.bytes());

    return STATE_READY;
}

template <typename T>
Stream::State Stream::receive(T* packet) {
    if (!m_socket->connected()) {
        return STATE_ERROR_CONNECTION;
    }

    PacketHeader header;
    int headerSize = 0;

    const State state = peek(&header, &headerSize);
    if (state != STATE_READY) {
        return state;
    }

    m_buffRecv.removeFromFront(NULL, headerSize);

    Deserializer deserializer(&m_buffRecv);
    const bool success =
        deserializer.read(packet) &&
        deserializer.offset() == static_cast<int>(header.size);

    m_buffRecv.removeFromFront(NULL, header.size);

    return success ? STATE_READY : STATE_ERROR_PROTOCOL;
}


}
