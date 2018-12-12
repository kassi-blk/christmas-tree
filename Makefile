CC=gcc
CFLAGS=-Wall
LDFLAGS=-lncurses
OBJS=main.o ncurapi.o
DEPS=ncruapi.h
PROG_NAME=prog

.PHONY: clean

all: $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG_NAME) $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROG_NAME) *.o
