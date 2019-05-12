CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

build: clean build_cat build_wc

build_cat: clean
	$(CC) $(CFLAGS) -o my_cat my_cat.c

build_wc: clean
	$(CC) $(CFLAGS) -o my_wc my_wc.c

run_cat: build_cat
	./my_cat lorem.txt

run_wc: build_wc
	./my_wc lorem.txt

clean:
	rm -f my_cat
	rm -f my_wc
