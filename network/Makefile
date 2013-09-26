# Makefile for the socket programming example
#

simple_client_objects = ClientSocket.o Socket.o simple_client_main.o


all : simple_client

simple_client: $(simple_client_objects)
	g++ -o simple_client $(simple_client_objects)


Socket: Socket.cc
ClientSocket: ClientSocket.cc
simple_client_main: simple_client_main.cc


clean:
	rm -f *.o simple_client