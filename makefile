CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread -lboost_filesystem -lboost_thread

all: BGSclient
	g++ -o bin/BGSclient bin/main.o bin/connectionHandler.o bin/inputClient.o bin/socketClient.o $(LDFLAGS)

BGSclient: bin/main.o bin/connectionHandler.o bin/inputClient.o bin/socketClient.o
	
bin/main.o: src/main.cpp
	g++ $(CFLAGS) -o bin/main.o src/main.cpp
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp
	
bin/inputClient.o: src/inputClient.cpp
	g++ $(CFLAGS) -o bin/inputClient.o src/inputClient.cpp
	
bin/socketClient.o: src/socketClient.cpp
	g++ $(CFLAGS) -o bin/socketClient.o src/socketClient.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
