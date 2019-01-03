//
// Created by michaeh@wincs.cs.bgu.ac.il on 1/2/19.
//

#include <inputClient.h>

#include "inputClient.h"


inputClient::inputClient(ConnectionHandler &connection, bool &shouldTerminate):connection(connection), shouldTerminate(shouldTerminate) {}

void inputClient::taskJob() {

    while (!shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        if (!connection.sendLine(line)) {
            std::cout << "Disconnected. Exiting..." << std::endl;
            break;
        }
    }

}
