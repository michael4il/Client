//
// Created by michaeh@wincs.cs.bgu.ac.il on 1/2/19.
//

#include <inputClient.h>

#include "inputClient.h"

using namespace std;
inputClient::inputClient(ConnectionHandler &connection, bool &shouldTerminate,int& flag):connection(connection), shouldTerminate(shouldTerminate),flag(flag){}

void inputClient::run() {

    while (!shouldTerminate) {

        const short bufsize = 1024;

        char buf[bufsize];
        while(flag==0){}
        if(flag==-1)
            break;
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        if(line=="LOGOUT")
            flag=0;
        if (!connection.sendLine(line)) {
            std::cout << "Disconnected. Exiting..." << std::endl;
            break;
        }
    }

}

