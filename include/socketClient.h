//
// Created by michael on 12/31/18.
//
#ifndef CLIENT_SOCKETCLIENT_H
#define CLIENT_SOCKETCLIENT_H

#include "connectionHandler.h"

class SocketClient {
private:
    ConnectionHandler &connection;
    bool &shouldTerminate;
public:
    SocketClient(ConnectionHandler &connection, bool &shouldTerminate);
    void taskJob();
};

#endif //CLIENT_SOCKETCLIENT_H
