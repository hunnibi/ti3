#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int alphasort(const struct dirent **a, const struct dirent **b);
int scandir(const char *dirp, struct dirent ***namelist, int (*filter)(const struct dirent *), int (*compar)(const struct dirent **, const struct dirent **));

int list_files(char *path, int show_sorted, int show_hidden);
int print_err_and_return_err_code(char *err);
char* get_last_modified(char *path);
void print_file_description(char *path_with_name, char* file_name, int show_date_modified);

// warning: multiple paths are not supported, like in native 'ls'
// warning: sorting or/and filter parameters MUST go first, otherwise error
int main(int argc, char **argv)
{
    // TODO: add '/' sign to each path


    print_file_description(".fufu", ".fufu", 1);
    // int result = list_files("./", 0, 1);
    // if (result) {
    //     return print_err_and_return_err_code(strerror(errno));
    // } else {
    //     return 0;
    // }
    return 0;
}

int is_dir_entry_not_hidden(const struct dirent *entry)
{
   return entry->d_name[0] != '.';
}

// char* get_last_modified(char *path)
// {   char *buffer = (char*)malloc(50 * sizeof(char));
//
//
//     strftime(buffer, 50, "%d.%m.%Y %H:%M:%S", localtime(&attr.st_mtime));
//
//     // return ;
//     return buffer;
// }

char* concat_string(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

// path_with_name and name parameters are used only for not to concatenate
// or split dir path and file name
void print_file_description(char *path_with_name, char* file_name, int show_date_modified)
{
    fprintf(stdout, "%-30s", file_name);
    if (show_date_modified) {
        struct stat attr;
        stat(path_with_name, &attr);
        fprintf(stdout, "%s", ctime(&attr.st_mtime)); // warning: f*cking 'ctime' generates string with '\n' at the end
    } else {
        printf("\n");
    }
}

int list_files(char *path, int show_sorted, int show_hidden)
{
    int (*sort)(const struct dirent **, const struct dirent **) = show_sorted ? &alphasort : 0;
    int (*filter)(const struct dirent*) = show_hidden ? 0 : &is_dir_entry_not_hidden;

    struct dirent **entries;
    int number_of_entries = scandir(path, &entries, filter, sort);

    if (number_of_entries < 0) {
        return errno;
    } else {
        for (int i = 0; i < number_of_entries; i++) {
            char *path_with_name = concat_string(path, entries[i]->d_name);

            print_file_description(path_with_name, entries[i]->d_name, show_sorted);

            free(path_with_name);
            free(entries[i]);
        }
        free(entries);
    }
    return 0;
}

int print_err_and_return_err_code(char *err)
{
    fprintf(stderr, "%s\n", err);
    return 1;
}


// void sort() {
// // todo: implement
// void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
// int strcmp(const char *s1, const char *s2);
//
// }

// int list_files_in_trash(char *path, char show_sorted, char show_hidden) {
//     DIR *dir_fd = opendir(TRASHCAN_DIRECTORY_NAME);
//     if (!dir_fd) return print_err_and_return_err_code(strerror(errno));
//
//     struct dirent *dir;
//
//     while ((dir = readdir(dir_fd)) != NULL) {
//         fprintf(stdout, "%s\n", dir->d_name);
//     }
//
//     closedir(dir_fd);
//
//     return 0;
// }

/*
ls
ls -l : alphabet sort + last modified
ls -a : show hidden
ls path/to/dir or path/to/file

ls -la or ls -al should be possible


return 0 : success
return 1 : minor problems

*/
