
#include <connectionHandler.h>

#include <stdlib.h>
#include <boost/thread.hpp>
#include "../include/connectionHandler.h"
#include "../include/socketClient.h"

#include <iostream>
#include "../include/inputClient.h"
/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
using namespace std;

int main(int argc, char *argv[]) { //main thread send messages,socket client receive messages
    if (argc < 3) {
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        return 1;
    }

    bool shouldTerminate = false;
    int flag= 1;
    SocketClient socketClient(connectionHandler, shouldTerminate,flag);
    inputClient  inputClient(connectionHandler,shouldTerminate,flag);

    boost::thread th1(&SocketClient::run, &socketClient);
    boost::thread th2(&inputClient::run,&inputClient);

    th1.join();
    th2.join();
    return 0;
}
