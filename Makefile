CC = g++ -g -c -Wall -ansi -pedantic -std=c++20

LN = g++

OBJS = main.o Keys.o

exe: $(OBJS)
	$(LN) -o exe $(OBJS) -lssl -lcrypto

Keys.o: Keys.hpp Keys.cpp
	$(CC) Keys.cpp

clean:
	/bin/rm -f exe *.o *~ \#*
