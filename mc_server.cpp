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
#include "mc_server.hpp"

namespace metacall {


//
// Server
//

Server::Server() :
    clientMax_(1),
    clientActive_(CLIENT_ID_INVALID)
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
    return &binding_;
}

Binding* Server::binding() {
    return &binding_;
}

bool Server::start(int serverPort, int clientsMax) {
    stop();

    if (server_.open() && server_.bind(serverPort) && server_.listen()) {
        server_.setBlocking(false);
        server_.setNagle(false);
        clientMax_ = clientsMax;
        return true;
    }

    stop();
    return false;
}

void Server::stop() {
    disconnectAll();
    clientMax_ = 0;
}

void Server::getClients(std::vector<ClientId>* clients) const {
    for (ClientMap::const_iterator iter = clients_.begin(); iter != clients_.end(); ++iter) {
        clients->push_back(iter->first);
    }
}

bool Server::getClient(ClientId id, ClientData* data) const {
    const ClientMap::const_iterator iter = clients_.find(id);
    if (iter != clients_.end())  {
        data->id        = iter->first;
        data->name      = iter->second->socket.hostname();
        data->protocol  = &iter->second->protocol;
        return true;
    }

    return false;
}

void Server::disconnect(ClientId id) {
    const ClientMap::iterator iter = clients_.find(id);
    if (iter != clients_.end()) {
        delete iter->second;
        clients_.erase(iter);
    }
}

void Server::disconnectAll() {
    for (ClientMap::iterator iter = clients_.begin(); iter != clients_.end(); ++iter) {
        delete iter->second;
    }

    clients_.clear();
}

int Server::clientCount() const {
    return clients_.size();
}

ClientId Server::clientActive() const {
    return clientActive_;
}

void Server::advanceConnecting() {
    if (clientMax_ == 0 || !server_.opened()) {
        return;
    }

    Socket client;
    if (!server_.accept(&client)) {
        return;
    }

    const std::pair<ClientId, ClientEntry*> entry(registerClientId(), new ClientEntry(&binding_));
    const ClientMap::iterator iter = clients_.insert(entry).first;
    iter->second->socket.set(client.release());
    iter->second->socket.setNagle(false);
    iter->second->socket.setBlocking(false);
}

void Server::advanceDisconnecting() {
    std::vector<ClientMap::iterator> clients;
    for (ClientMap::iterator iter = clients_.begin(); iter != clients_.end(); ++iter) {
        if (!iter->second->socket.connected()) {
            clients.push_back(iter);
        }
    }

    for (std::vector<ClientMap::iterator>::iterator iter = clients.begin(); iter != clients.end(); ++iter) {
        disconnect((*iter)->first);
    }
}

void Server::advanceConnected() {
    ASSERT(clientActive_ == CLIENT_ID_INVALID);

    for (ClientMap::iterator iter = clients_.begin(); iter != clients_.end(); ++iter) {
        clientActive_ = iter->first;
        iter->second->protocol.advance();
    }

    clientActive_ = CLIENT_ID_INVALID;
}

ClientId Server::registerClientId() {
    static int s_id = CLIENT_ID_INVALID;
    while (++s_id == CLIENT_ID_INVALID);
    return static_cast<ClientId>(s_id);
}


}
