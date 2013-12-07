
CFLAGS=-g -Wall -O3
LDLIBS=
CC=c99


zest: zest.o
zest.o: zest.c header.c
	$(CC) $(CFLAGS) -o $@ -c $<

header.c: pfize header_src.c
	./pfize print_header header_src.c > header.c

pfize: pfize.o


.PHONY: clean

clean:
	rm -f *.o *.so*
	rm -f z.c

