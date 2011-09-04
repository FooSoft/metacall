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
#include "mc_socket.hpp"

namespace metacall {


//
// Constants
//

namespace {


const int SOCKET_INVALID = -1;


}


//
// Socket
//

Socket::Socket() :
    socket_(SOCKET_INVALID)
{
}

Socket::~Socket() {
    close();
}

bool Socket::open() {
    close();
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    return opened();
}

void Socket::close() {
    if (!opened()) {
        return;
    }

#ifdef _WIN32
    closesocket(socket_);
#else
    ::close(socket_);
#endif

    socket_ = SOCKET_INVALID;
}

int Socket::release() {
    const int temp = socket_;
    socket_ = SOCKET_INVALID;
    return temp;
}

void Socket::set(int socket) {
    close();
    socket_ = socket;
}

void Socket::setNagle(bool enable) {
    ASSERT(opened());

    const int           value       = enable ? 0 : 1;
    const char* const   valuePtr    = reinterpret_cast<const char*>(&value);

    setsockopt(
        socket_,
        IPPROTO_TCP,
        TCP_NODELAY,
        valuePtr,
        sizeof(value)
    );
}

void Socket::setBlocking(bool enable) {
    ASSERT(opened());

#ifdef _WIN32
    unsigned long nonBlock = enable ? 0 : 1;
    ioctlsocket(socket_, FIONBIO, &nonBlock);
#else
    const int flagsOld = fcntl(socket_, F_GETFL);
    const int flagsNew = enable ? flagsOld & ~O_NONBLOCK : flagsOld | O_NONBLOCK;
    fcntl(socket_, F_SETFL, flagsNew);
#endif
}

bool Socket::connect(const char name[], int port) {
    ASSERT(opened());

    long address = 0;
    if (!resolve(name, &address)) {
        return false;
    }

    sockaddr_in host        = { 0 };
    host.sin_port           = htons(static_cast<unsigned short>(port));
    host.sin_family         = AF_INET;
    host.sin_addr.s_addr    = address;

    const sockaddr* const hostPtr = reinterpret_cast<const sockaddr*>(&host);
    if (::connect(socket_, hostPtr, sizeof(host)) == SOCKET_INVALID) {
        return false;
    }

    return true;
}

bool Socket::bind(int port) {
    ASSERT(opened());

    sockaddr_in host        = { 0 };
    host.sin_family         = AF_INET;
    host.sin_addr.s_addr    = INADDR_ANY;
    host.sin_port           = htons(static_cast<unsigned short>(port));

    const sockaddr* const hostPtr = reinterpret_cast<const sockaddr*>(&host);
    if (::bind(socket_, hostPtr, sizeof(host)) == SOCKET_INVALID) {
        return false;
    }

    return true;
}

bool Socket::listen(int backlog) {
    ASSERT(opened());
    return ::listen(socket_, backlog) != SOCKET_INVALID;
}

bool Socket::accept(Socket* socket) {
    ASSERT(opened());

    socket->close();
    socket->socket_ = ::accept(socket_, 0, 0);

    return socket->socket_ != SOCKET_INVALID;
}

int Socket::receive(void* buffer, int size) {
    ASSERT(opened());

    if (size <= 0) {
        return 0;
    }

    return recv(
        socket_,
        static_cast<char *>(buffer),
        size,
        0
    );
}

int Socket::peek(void* buffer, int size) const {
    ASSERT(opened());

    if (size <= 0) {
        return 0;
    }

    return recv(
        socket_,
        static_cast<char *>(buffer),
        size,
        MSG_PEEK
    );
}

int Socket::send(const void* buffer, int size) {
    ASSERT(opened());

    if (size <= 0) {
        return 0;
    }

    return ::send(
        socket_,
        static_cast<const char*>(buffer),
        size,
        0
    );
}

bool Socket::wait(unsigned mask, int seconds) const {
    ASSERT(opened());

    fd_set readSet;
    fd_set writeSet;
    fd_set exceptSet;

    fd_set* readSetUse      = NULL;
    fd_set* writeSetUse     = NULL;
    fd_set* exceptSetUse    = NULL;

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4127)
#endif
    if (mask & MASK_READ) {
        readSetUse = &readSet;
        FD_ZERO(readSetUse);
        FD_SET(socket_, readSetUse);
    }
    if (mask & MASK_WRITE) {
        writeSetUse = &writeSet;
        FD_ZERO(writeSetUse);
        FD_SET(socket_, writeSetUse);
    }
    if (mask & MASK_EXCEPT) {
        exceptSetUse = &exceptSet;
        FD_ZERO(exceptSetUse);
        FD_SET(socket_, exceptSetUse);
    }
#ifdef _WIN32
#pragma warning(pop)
#endif

    timeval timeoutVal  = { 0 };
    timeoutVal.tv_sec   = seconds;

    timeval* const timeoutPtr = seconds < 0 ? NULL : &timeoutVal;
    const int result = select(
        socket_ + 1,
        readSetUse,
        writeSetUse,
        exceptSetUse,
        timeoutPtr
    );

    return result > 0;
}

bool Socket::opened() const {
    return socket_ != SOCKET_INVALID;
}

bool Socket::connected() const {
    if (!opened()) {
        return false;
    }

    if (!wait(MASK_READ, 0)) {
        return true;
    }

    byte buffer = 0;
    if (peek(&buffer, sizeof(buffer)) == 0) {
        return false;
    }

    return true;
}

const char* Socket::hostname() const {
    if (!opened()) {
        return NULL;
    }

    sockaddr_in     host        = { 0 };
    socklen_t       hostSize    = sizeof(host);
    sockaddr* const hostPtr     = reinterpret_cast<sockaddr*>(&host);

    if (getsockname(socket_, hostPtr, &hostSize) == SOCKET_INVALID) {
        return NULL;
    }

    return inet_ntoa(host.sin_addr);
}

bool Socket::resolve(const char name[], long* address) {
    if ((*address = inet_addr(name)) != INADDR_NONE) {
        return true;
    }

    hostent* const host = gethostbyname(name);
    if (host == NULL) {
        return false;
    }

    *address = *reinterpret_cast<long*>(host->h_addr_list[0]);
    return true;
}


}
