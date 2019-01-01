//
// Created by michael on 12/31/18.
//

#include "socketClient.h"

using namespace std;

SocketClient::SocketClient(ConnectionHandler& connection, bool & shouldTerminate) : connection(connection), shouldTerminate(shouldTerminate) {
}

void SocketClient::taskJob() {
    while (true) {
        std::string answer;

        if (!this->connection.getLine(answer)) {
            break;
        }
        int len = answer.length();
        answer.resize(len - 1);
        std::cout << answer << std::endl;
    }

}
