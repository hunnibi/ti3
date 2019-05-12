#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int wc_from_stdin();
int wc_from_file(char *);

// Attention: uses stdin as input. Line buffer size(chars per line): 4096!
int main(int argc, char **argv) {
    if (argc == 1) {
        return wc_from_stdin();
    } else {
        int status;
        pid_t pid = fork();
        if (pid == 0) {
            int result = wc_from_file(argv[1]);
            pid = fork();
            return result;
        } else if(pid > 0) {
            pid = wait(&status);
            return wc_from_file(argv[2]);
        } else {
            printf("Error: fork failed!\n");
            exit(EXIT_FAILURE);
        }
    }
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

int wc_from_stdin() {
    char buffer[BUFFER_SIZE];

    long int new_line_count = 0;
    long int word_count = 0;
    long int byte_count = 0;

    while(fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        new_line_count++;
        word_count += count_words_in_string(buffer);
        byte_count += strlen(buffer);
    }

    printf("%ld %ld %ld\n", new_line_count, word_count, byte_count);

    return 0;
}

int wc_from_file(char *filename) {
    FILE *fd = fopen(filename, "r");
    if (fd == NULL) return print_err_and_return_err_code(strerror(errno));

    char buffer[BUFFER_SIZE];

    long int new_line_count = 0;
    long int word_count = 0;
    long int byte_count = 0;

    while(fgets(buffer, BUFFER_SIZE, fd) != NULL) {
        new_line_count++;
        word_count += count_words_in_string(buffer);
        byte_count += strlen(buffer);
    }

    printf("%ld %ld %ld %s\n", new_line_count, word_count, byte_count, filename);

    if (fclose(fd) == EOF) return print_err_and_return_err_code(strerror(errno));

    return 0;
}
