
CFLAGS=-g -Wall -O3
LDLIBS=
CC=c99

zest: zest.o
zest.o: zest.c header.c
	$(CC) $(CFLAGS) -o $@ -c $<

header.c: pfize header_src.c
	./pfize header_src.c > header.c

pfize: pfize.o
pfize.o: pfize.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f *.o *.so*
	rm -f z_*.c

