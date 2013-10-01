CC=g++
CC_FLAG= -Wall #-Werror -Wfloat-equal -Wshadow -Wconversion -Winline

test:test.o util.o crypter.o
	$(CC) $(CC_FLAG) test.o util.o crypter.o -o test

test.o: test.cc 

util.o: util.cc util.h
	$(CC) $(CC_FLAG) -c util.cc

crypter.o: crypter.cc crypter.h
	$(CC) $(CC_FLAG) -c crypter.cc

clean:
	rm test util.o crypter.o 