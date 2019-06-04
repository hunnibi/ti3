CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

run: build
	./a.out
build: clean
	$(CC) $(CFLAGS) my_ls.c
clean:
	rm -f a.out
