//
// Created by michael on 12/31/18.
//

#include "socketClient.h"

using namespace std;

SocketClient::SocketClient(ConnectionHandler& connection, bool & shouldTerminate,int& flag) : connection(connection), shouldTerminate(shouldTerminate) , flag(flag){
}

void SocketClient::run() {
    std::string answer;
    while ( !shouldTerminate ) {
        answer.resize(0);
        if (!this->connection.getLine(answer)) {
            break;
        }
        int len = answer.length();
        answer.resize(len);
        std::cout << answer << std::endl;
        if(answer=="ACK 3") {
            flag = -1;
            shouldTerminate = true;
        } else flag=1;
    }

}
