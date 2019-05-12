#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

int print_err_and_return_err_code(char *err) {
    fprintf(stderr, "Error: %s!\n", err);
    return -1;
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

int main(int argc, char **argv) {
    if (argc < 2) return print_err_and_return_err_code("Not enough arguments");

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) return print_err_and_return_err_code(strerror(errno));

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    long int new_line_count = 0;
    long int word_count = 0;
    long int byte_count = 0;

    while((read = getline(&buffer, &len, fp)) != -1) {
        new_line_count++;
        word_count += count_words_in_string(buffer);
        byte_count += read;
    }

    printf("%ld %ld %ld %s\n", new_line_count, word_count, byte_count, argv[1]);

    free(buffer);

    if (fclose(fp) == EOF) return print_err_and_return_err_code(strerror(errno));

    return 0;
}
