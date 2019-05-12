#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int print_err_and_return_err_code(char *err) {
    fprintf(stderr, "Error: %s!\n", err);
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 2) return print_err_and_return_err_code("Not enough arguments");

    FILE *fd = fopen(argv[1], "r");
    if (fd == NULL) return print_err_and_return_err_code(strerror(errno));

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&buffer, &len, fd)) != -1) {
        printf("%s", buffer);
    }

    free(buffer);

    if (fclose(fd) == EOF) return print_err_and_return_err_code(strerror(errno));

    return 0;
}
