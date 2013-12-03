
CFLAGS=-g -Wall -O3
LDLIBS=
CC=c99

pfize: pfize.o
pfize.o: pfize.c
	$(CC) $(CFLAGS) -o $@ -c $<

#h_and_f.c:
#	cp h_and_f_src.c h_and_f.c
#	#pfize h_and_f_src.c h_and_f.c
zest: zest.o
zest.o: zest.c
	#cat h_and_f.c >> zest.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f *.o *.so*
	rm -f z_*.c

