CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

build: clean
	$(CC) $(CFLAGS) -o trashcan trashcan.c
run: build
	touch source.txt
	echo "Test source file text!" > source.txt
	./trashcan -t source.txt
clean:
	rm -f trashcan
	rm -f source.txt
	rm -f target.txt
	rm -f .ti3_trashcan/*
