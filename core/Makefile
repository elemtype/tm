OBJECTS=util.o crypter.o base_packet.o base_packet_out.o touch_packet_out.o Socket.o ClientSocket.o login.o
CC=g++
CC_FLAG= -Wall #-Werror -Wfloat-equal -Wshadow -Wconversion -Winline

login:$(OBJECTS)
	$(CC) $(CC_FLAG) ${OBJECTS} -o login

util.o: ../common/util.cc ../common/util.h
	$(CC) $(CC_FLAG) -c ../common/util.cc

crypter.o: ../crypter/crypter.cc ../crypter/crypter.h
	$(CC) $(CC_FLAG) -c ../crypter/crypter.cc

base_packet.o: packet/base_packet.cc packet/base_packet.h
	$(CC) $(CC_FLAG) -c packet/base_packet.cc

base_packet_out.o: packet/out/base_packet_out.cc packet/out/base_packet_out.h
	$(CC) $(CC_FLAG) -c packet/out/base_packet_out.cc

touch_packet_out.o: packet/out/touch_packet_out.cc packet/out/touch_packet_out.h
	$(CC) $(CC_FLAG) -c packet/out/touch_packet_out.cc

Socket.o: ../network/Socket.cc ../network/Socket.h
	$(CC) $(CC_FLAG) -c ../network/Socket.cc

ClientSocket.o: ../network/ClientSocket.cc ../network/ClientSocket.h
	$(CC) $(CC_FLAG) -c ../network/ClientSocket.cc

login.o: login.cc login.h
	$(CC) $(CC_FLAG) -c login.cc 

clean:
	rm login *.o