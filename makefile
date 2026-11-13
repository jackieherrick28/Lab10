CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lm

all: send_signal recv_signal

send_signal: send_signal.o
	$(CC) send_signal.o $(LIBS) -o send_signal

recv_signal: recv_signal.o
	$(CC) recv_signal.o $(LIBS) -o recv_signal

send_signal.o: send_signal.c
	$(CC) $(CFLAGS) -c send_signal.c

recv_signal.o: recv_signal.c
	$(CC) $(CFLAGS) -c recv_signal.c

clean:
	rm -f *.o send_signal recv_signal