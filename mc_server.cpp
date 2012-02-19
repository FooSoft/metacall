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

namespace metacall {


//
// Server
//

Server::Server() :
    m_clientMax(1),
    m_clientActive(CLIENT_ID_INVALID)
{
}

Server::~Server() {
    disconnectAll();
}

void Server::advance() {
    advanceConnecting();
    advanceDisconnecting();
    advanceConnected();
}

const Binding* Server::binding() const {
    return &m_binding;
}

Binding* Server::binding() {
    return &m_binding;
}

bool Server::start(int serverPort, int clientsMax) {
    stop();

    if (m_server.open() && m_server.bind(serverPort) && m_server.listen()) {
        m_server.setBlocking(false);
        m_server.setNagle(false);
        m_clientMax = clientsMax;
        return true;
    }

    stop();
    return false;
}

void Server::stop() {
    disconnectAll();
    m_clientMax = 0;
}

void Server::clients(std::vector<ClientId>* clients) const {
    for (ClientMap::const_iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
        clients->push_back(iter->first);
    }
}

bool Server::clients(ClientId id, ClientData* data) const {
    const ClientMap::const_iterator iter = m_clients.find(id);
    if (iter == m_clients.end())  {
        return false;
    }

    data->id        = iter->first;
    data->name      = iter->second->socket.hostname();
    data->protocol  = &iter->second->protocol;

    return true;
}

void Server::disconnect(ClientId id) {
    const ClientMap::iterator iter = m_clients.find(id);
    if (iter != m_clients.end()) {
        delete iter->second;
        m_clients.erase(iter);
    }
}

void Server::disconnectAll() {
    for (ClientMap::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
        delete iter->second;
    }

    m_clients.clear();
}

int Server::clientCount() const {
    return m_clients.size();
}

Server::ClientId Server::clientActive() const {
    return m_clientActive;
}

void Server::advanceConnecting() {
    if (m_clientMax == 0 || !m_server.opened()) {
        return;
    }

    Socket client;
    if (!m_server.accept(&client)) {
        return;
    }

    const std::pair<ClientId, ClientEntry*> entry(
        registerClientId(),
        new ClientEntry(&m_binding)
    );

    const ClientMap::iterator iter = m_clients.insert(entry).first;
    iter->second->socket.set(client.release());
    iter->second->socket.setNagle(false);
    iter->second->socket.setBlocking(false);
}

void Server::advanceDisconnecting() {
    std::vector<ClientMap::iterator> clients;
    for (ClientMap::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
        if (!iter->second->socket.connected()) {
            clients.push_back(iter);
        }
    }

    for (std::vector<ClientMap::iterator>::iterator iter = clients.begin(); iter != clients.end(); ++iter) {
        disconnect((*iter)->first);
    }
}

void Server::advanceConnected() {
    ASSERT(m_clientActive == CLIENT_ID_INVALID);

    for (ClientMap::iterator iter = m_clients.begin(); iter != m_clients.end(); ++iter) {
        m_clientActive = iter->first;
        iter->second->protocol.advance();
    }

    m_clientActive = CLIENT_ID_INVALID;
}

Server::ClientId Server::registerClientId() {
    static int s_id = CLIENT_ID_INVALID;
    while (++s_id == CLIENT_ID_INVALID);
    return static_cast<ClientId>(s_id);
}


}
