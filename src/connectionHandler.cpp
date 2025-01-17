#include <connectionHandler.h>

using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using namespace std;
ConnectionHandler::ConnectionHandler(string host, short port): host_(host), port_(port), io_service_(), socket_(io_service_){opCounter=0;}

ConnectionHandler::~ConnectionHandler() {
    close();
}

bool ConnectionHandler::connect() {
    std::cout << "Starting connect to "
              << host_ << ":" << port_ << std::endl;
    try {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
        boost::system::error_code error;
        socket_.connect(endpoint, error);
        if (error)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {

            tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);
        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "Get Bytes recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
    boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
            tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);

        }
        if(error)
            throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "Send Bytes failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
//-------------------------------------------------------------DECODER--------------------------------
bool ConnectionHandler::getLine(std::string& line) {
    string first,second;
    char firstShort[2];
    getBytes(firstShort,2);
    short opcode= bytesToShort(firstShort);
    opcodeToString(first,opcode);
    line.append(first+" ");// first is string
    switch(opcode){
        //------------------------------------------------ERROR--------------------------------
        case 11:{
            handleShort(line);
            break;
        }
        //--------------------------------------------NOTIFICATION------------------------------------
        case 9:{
            char c;
            getBytes(&c,1);
            if(c=='\0')
                line.append("PM ");
            else
                line.append("Public ");
            getFrameAscii(line,'\0');
            line.append(" ");
            getFrameAscii(line,'\0');
            break;
        }
        case 10:{

            //------------------------------------------------ACK-----------------------------------------------------


            short opcodeSecond= handleShort(line);//string updated
            if(opcodeSecond== 4 || opcodeSecond==7) {
                line.append(" ");
                short count = handleShort(line);
                line.append(" ");
                for (int i = 0; i < count; i++) {
                    getFrameAscii(line, '\0');
                    line.append(" ");
                }
                line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                line.resize(line.size() - 1);
            }
            //-------------------------------------------------------------STAT-----------------
            if(opcodeSecond==8)
            {
                line.append(" ");
                handleShort(line);
                line.append(" ");
                handleShort(line);
                line.append(" ");
                handleShort(line);
            }
            break;
        }

    }


    return true;//need to return bool

}



//---------------------------------------------ENCODER-----------------------------------------------------------
bool ConnectionHandler::sendLine(std::string& line) {
    stringstream strt(line);
    string var;
    getline(strt,var,' ');

    if(var=="LOGIN"){
        sendShort(2);
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        return true;

    }else if(var=="REGISTER"){

        sendShort((short)1);
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        return true;
    }else if(var=="LOGOUT") {
        sendShort(3);
        return true;
    }else if(var=="FOLLOW"){
        //---------------------------------------------FOLLOW---------------------------------
        sendShort(4);
        getline(strt,var,' ');
        if(var=="0")
            sendFrameAscii("",'\0');//maybe \n \n
        else sendFrameAscii("",'1');
        getline(strt,var,' ');
        sendShort((short)stoi(var));//num of users
        while(getline(strt,var,' '))
            sendFrameAscii(var,'\0');
        return true;
//-------------------------------------------------------------------------------------------

    }else if(var=="POST"){
        sendShort(5);
        getline(strt,var,'\n');
        sendFrameAscii(var,'\0');
        return true;
//-------------------------------------------------------------------------------------------
    }else if(var=="PM"){
        sendShort(6);
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        getline(strt,var,'\n');
        sendFrameAscii(var,'\0');
        return true;
        //-------------------------------------------------------------------------------------------

    }else if(var=="USERLIST"){
        sendShort(7);
        return true;
    }else if(var=="STAT"){
        sendShort(8);
        getline(strt,var,' ');
        sendFrameAscii(var,'\0');
        return true;
    }else if(var=="aa"){
        getline(strt,var,' ');
        sendFrameAscii("aa",'\0');
        return true;
    }
    return true;
}


bool ConnectionHandler::sendShort(short num){
    char arr[2];
    shortToBytes(num,arr);
    return sendBytes(arr,2);


}


bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {

    char ch;//1 byte

    // Stop when we encounter the null character. 
    // Notice that the null character is not appended to the frame string.
    try {
        do{
            getBytes(&ch, 1);
            frame.append(1, ch);
        }while (delimiter != ch);
        frame.resize(frame.size()-1);
    } catch (std::exception& e) {
        std::cerr << "Get Frame recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}


bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
    bool result=sendBytes(frame.c_str(),frame.length());
    if(!result) return false;
    return sendBytes(&delimiter,1);
}

// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

void ConnectionHandler::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);

}

short ConnectionHandler::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

bool ConnectionHandler::opcodeToString(std::string &line, short opcode) {
    switch (opcode)  {
        case 1:line.append("REGISTER");break;
        case 2:line.append("LOGIN");break;
        case 3:line.append("LOGOUT");break;
        case 4:line.append("FOLLOW");break;
        case 5:line.append("POST");break;
        case 6:line.append("PM");break;
        case 7:line.append("USERLIST");break;
        case 8:line.append("STAT");break;
        case 9:line.append("NOTIFICATION");break;
        case 10:line.append("ACK");break;
        case 11:line.append("ERROR");break; }
        return true;
}

short ConnectionHandler::handleShort(std::string &line) {
    char bytesArr[2];
    getBytes(bytesArr,2);
    short value= bytesToShort(bytesArr);
    string Result;
    ostringstream convert;
    convert << value;
    Result = convert.str();
    line.append(Result);
    return value;
}





