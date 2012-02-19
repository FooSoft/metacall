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

#include <string>
#include <vector>
#include <map>
#include <memory.h>
#include <assert.h>

#ifdef _WIN32

#define NOMINMAX
#include <ws2tcpip.h>

#else

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#endif

#include "mc_common.hpp"
#include "mc_token.hpp"
#include "mc_buffer.hpp"
#include "mc_socket.hpp"
#include "mc_meta.hpp"
#include "mc_serial.hpp"
#include "mc_serial-inl.hpp"
#include "mc_packet.hpp"
#include "mc_functor.hpp"
#include "mc_binding.hpp"
#include "mc_binding-inl.hpp"
#include "mc_stream.hpp"
#include "mc_stream-inl.hpp"
#include "mc_protocol.hpp"
#include "mc_protocol-inl.hpp"
#include "mc_client.hpp"
#include "mc_server.hpp"
#include "mc_prefab.hpp"
#include "mc_prefab-inl.hpp"
