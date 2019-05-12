#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int print_err_and_return_err_code(char *err) {
    fprintf(stderr, "Error: %s!\n", err);
    return -1;
}

int main(int argc, char **argv) {
    if (argc < 2) return print_err_and_return_err_code("Not enough arguments");

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) return print_err_and_return_err_code(strerror(errno));

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&buffer, &len, fp)) != -1) {
        printf("%s", buffer);
    }

    free(buffer);

    if (fclose(fp) == EOF) return print_err_and_return_err_code(strerror(errno));

    return 0;
}
