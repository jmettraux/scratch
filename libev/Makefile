
#CFLAGS=-I../src
LDLIBS=/usr/lib/libev.so # :-(
CC=c99
#VPATH=../src

serve: serve.o

s: serve
	./serve

clean:
	rm -f *.o
	#rm -f *.c    # :-(
	#rm -f serve  # :-(

.PHONY: clean s

