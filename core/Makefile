OBJECTS=base_packet.o base_packet_in.o Socket.o ClientSocket.o login.o
CC=g++
CC_FLAG= -Wall #-Werror -Wfloat-equal -Wshadow -Wconversion -Winline

login:$(OBJECTS)
	$(CC) $(CC_FLAG) ${OBJECTS} -o login

base_packet.o: packet/base_packet.cc packet/base_packet.h
	$(CC) $(CC_FLAG) -c packet/base_packet.cc

base_packet_in.o: packet/in/base_packet_in.cc packet/in/base_packet_in.h
	$(CC) $(CC_FLAG) -c packet/in/base_packet_in.cc

Socket.o: ../network/Socket.cc ../network/Socket.h
	$(CC) $(CC_FLAG) -c ../network/Socket.cc

ClientSocket.o: ../network/ClientSocket.cc ../network/ClientSocket.h
	$(CC) $(CC_FLAG) -c ../network/ClientSocket.cc

login.o: login.cc login.h
	$(CC) $(CC_FLAG) -c login.cc 

clean:
	rm login *.o