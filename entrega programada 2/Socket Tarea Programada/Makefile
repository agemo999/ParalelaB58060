all: Socket.o mirrorclient.o  mirrorserver.o client server
Socket.o: Socket.h Socket.cpp
	g++ -c -g Socket.cpp

mirrorclient.o: Socket.h Socket.cpp mirrorclient.cpp
	g++ -c -g Socket.cpp mirrorclient.cpp

mirrorserver.o: Socket.h Socket.cpp mirrorserver.cpp
	g++ -c -g Socket.cpp mirrorserver.cpp

client: mirrorclient.o Socket.o
	g++ mirrorclient.o Socket.o -o client

server: mirrorserver.o Socket.o
	g++ mirrorserver.o Socket.o -o server
