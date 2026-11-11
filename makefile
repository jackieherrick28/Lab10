CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lm

all: tennis1 tennis2

tennis1: tennis1.o
	$(CC) tennis1.o $(LIBS) -o tennis1

tennis2: tennis2.o
	$(CC) tennis2.o $(LIBS) -o tennis2

tennis1.o: tennis1.c tennis.h tennis1.h
	$(CC) $(CFLAGS) -c tennis1.c

tennis2.o: tennis2.c tennis.h
	$(CC) $(CFLAGS) -c tennis2.c

clean:
	rm -f *.o tennis1 tennis2