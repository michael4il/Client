
//
//#include <boost/thread.hpp>
//#include "../include/connectionHandler.h"
//#include "../include/socketClient.h"
//#include "clientMain.h"
//using namespace std;
//int main(int argc, char *argv[]) { //main thread send messages,socket client receive messages
//    if (argc < 3) {
//        return -1;
//    }
//    std::string host = argv[1];
//    short port = atoi(argv[2]);
//
//    ConnectionHandler connectionHandler(host, port);
//    if (!connectionHandler.connect()) {
//        return 1;
//    }
//
//    bool shouldTerminate = false;
//
//    SocketClient socketClient(connectionHandler, shouldTerminate);
//    boost::thread th2(&SocketClient::taskJob, &socketClient);//==thread.start
//
//    while (!shouldTerminate) {
//        const short bufsize = 1024;
//        char buf[bufsize];
//        std::cin.getline(buf, bufsize);
//        std::string line(buf);
//
//        if (line != "" && !connectionHandler.sendLine(line)) {
//            std::cout << "Disconnected. Exiting..." << std::endl;
//            break;
//        }
//    }
//
//
//    th2.join();
//    return 0;
//}