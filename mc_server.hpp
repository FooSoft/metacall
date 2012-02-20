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
// Server
//

class Server {
public:
    enum ClientId {
        CLIENT_ID_INVALID
    };

    struct ClientData {
        ClientData() :
            id(CLIENT_ID_INVALID),
            protocol(NULL)
        {
        }

        ClientId    id;
        std::string name;
        Protocol*   protocol;
    };

    Server();
    ~Server();

    void            advance();
    bool            start(int serverPort, int clientsMax = 1);
    void            stop();
    void            disconnect(ClientId id);
    void            disconnectAll();

    void            clients(std::vector<ClientId>* clients) const;
    bool            clients(ClientId id, ClientData* data) const;
    ClientId        clientActive() const;
    int             clientCount() const;
    const Binding&  binding() const;
    Binding&        binding();

private:
    struct ClientEntry : public ClientData {
        ClientEntry(Binding* binding) :
            stream(&socket),
            protocol(&stream, binding)
        {
        }

        Socket      socket;
        Stream      stream;
        Protocol    protocol;
    };

    void            advanceConnecting();
    void            advanceConnected();
    void            advanceDisconnecting();
    static ClientId registerClientId();

    typedef         std::map<ClientId, ClientEntry*> ClientMap;
    ClientMap       m_clients;
    int             m_clientMax;
    ClientId        m_clientActive;
    Socket          m_server;
    Binding         m_binding;
};


}
