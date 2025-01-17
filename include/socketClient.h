//
// Created by michael on 12/31/18.
//
#ifndef CLIENT_SOCKETCLIENT_H
#define CLIENT_SOCKETCLIENT_H

#include "connectionHandler.h"

class socketClient {
private:
    ConnectionHandler &connection;
    bool &shouldTerminate;
    int& flag;

public:
    socketClient(ConnectionHandler &connection, bool &shouldTerminate,int& flag);
    void run();
};

#endif //CLIENT_SOCKETCLIENT_H
