#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int count_words_in_string(char *str);
int print_err_and_return_err_code(char *err);

// Attention: uses stdin as input. Line buffer size: 4096!
int main(int argc, char **argv) {

    FILE *fd;
    if (argc > 1) {
        fd = fopen(argv[1], "r");
        if (fd == NULL) return print_err_and_return_err_code(strerror(errno));
    } else {
        fd = stdin;
    }

    char buffer[BUFFER_SIZE];

    long int new_line_count = 0;
    long int word_count = 0;
    long int byte_count = 0;

    while(fgets(buffer, BUFFER_SIZE, fd) != NULL) {
        new_line_count++;
        word_count += count_words_in_string(buffer);
        byte_count += strlen(buffer);
    }

    printf("%ld %ld %ld", new_line_count, word_count, byte_count);

    if (argc > 1) printf(" %s\n", argv[1]);

    printf("\n");

    if (argc > 1 && fclose(fd) == EOF) return print_err_and_return_err_code(strerror(errno));

    return 0;
}

int count_words_in_string(char *str) {
    int number_of_words = 0;

    if (*str != '\n' && *str != '\0') number_of_words++;

    while(*str != '\0') {
        if (*str == ' ') number_of_words++;

        str++;
    }

    return number_of_words;
}

int print_err_and_return_err_code(char *err) {
    fprintf(stderr, "Error: %s!\n", err);
    return -1;
}
