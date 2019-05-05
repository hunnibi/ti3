CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

build: clean
	$(CC) $(CFLAGS) ue2_2.c
run: build
	touch source.txt
	echo "Test source file text!" > source.txt
	./a.out
clean:
	rm -f a.out
	rm -f target.txt
