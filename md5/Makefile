
CFLAGS=-I../src -g -Wall
LDLIBS=
CC=c99 -lcrypto

NAMES=$(patsubst ./%.c, ./%.o, $(wildcard ./*.c))

md5: $(NAMES)

clean:
	rm -f *.o
	rm -f *.so

.PHONY: clean

