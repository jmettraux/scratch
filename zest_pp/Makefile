
CFLAGS=-fPIC -O3 -g -Wall -Werror
CC=c99
NAME=zest

lib: lib$(NAME).so

lib$(NAME).so: $(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so $^ -o $@

clean:
	rm -f *.o *.so*

