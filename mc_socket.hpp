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
// Socket
//

class Socket {
public:
    enum {
        MASK_READ   = 1 << 0,
        MASK_WRITE  = 1 << 1,
        MASK_EXCEPT = 1 << 2
    };

    Socket();
    ~Socket();

    bool        open();
    void        close();
    int         release();
    void        set(int socket);
    void        setNagle(bool enable);
    void        setBlocking(bool enable);

    bool        connect(const char name[], int port);
    bool        bind(int port);
    bool        listen(int backlog = 5);
    bool        accept(Socket* socket);

    int         receive(void* buffer, int size);
    int         peek(void* buffer, int size) const;
    int         send(const void* buffer, int size);
    bool        wait(unsigned mask, int seconds) const;

    bool        opened() const;
    bool        connected() const;
    const char* hostname() const;

private:
    static bool resolve(const char name[], long* address);

    int         m_socket;
};


}
