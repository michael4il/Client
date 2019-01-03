//
// Created by michaeh@wincs.cs.bgu.ac.il on 1/2/19.
//

#ifndef BOOST_ECHO_CLIENT_INPUTCLIENT_H
#define BOOST_ECHO_CLIENT_INPUTCLIENT_H
#include "connectionHandler.h"


class inputClient {

private:
    ConnectionHandler &connection;
    bool &shouldTerminate;
    int& flag;
public:
    inputClient(ConnectionHandler &connection, bool &shouldTerminate,int& flag);
    void run();
};



#endif //BOOST_ECHO_CLIENT_INPUTCLIENT_H
