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
public:
    inputClient(ConnectionHandler &connection, bool &shouldTerminate);
    void taskJob();
};



#endif //BOOST_ECHO_CLIENT_INPUTCLIENT_H
