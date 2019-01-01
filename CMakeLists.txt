cmake_minimum_required(VERSION 3.12)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)
include_directories(src)
add_executable(
        Boost_Echo_Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp src/socketClient.cpp include/socketClient.h src/clientMain.cpp include/clientMain.h)
target_link_libraries(${PROJECT_NAME}  -lpthread ) #obviously without the '[...]' and the correct target name
target_link_libraries(Boost_Echo_Client ${Boost_LIBRARIES})