#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

#define 

int print_err_and_return_err_code() {
    printf("Error: %s\n", strerror(errno));
    return -1;
}

int copy(char *sourcename, char *targetname) {
    int source_fd = open(sourcename, O_RDONLY);
    if (source_fd == -1) return print_err_and_return_err_code();

    int target_fd = open(targetname, O_CREAT | O_EXCL | O_WRONLY | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (target_fd == -1) return print_err_and_return_err_code();

    char buffer[BUFFER_SIZE];
    ssize_t chars_read = 0;

    while((chars_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        chars_read = write(target_fd, buffer, chars_read);
        if (chars_read == -1) return print_err_and_return_err_code();
    }

    if (close(source_fd) == -1) return print_err_and_return_err_code();
    if (close(target_fd) == -1) return print_err_and_return_err_code();

    return 0;
 }

int main(void) {
    return copy("source.txt", "target.txt");
}
