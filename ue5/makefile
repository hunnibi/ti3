CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

run: build
	./a.out

build: clean
	$(CC) $(CFLAGS) scheduler.c sched_test.c
	
clean:
	rm -f a.out
