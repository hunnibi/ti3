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

char* concat_string(const char *s1, const char *s2);
int list_files(char *path, int show_sorted, int show_hidden);
int print_err_and_return_err_code(char *err);
void print_file_description(char *path, int show_date_modified);
int is_regular_file(const char *path);
int exists(const char *fname);

// warning: multiple paths are not supported, like in native 'ls'
// warning: sorting or/and filter parameters MUST go first, otherwise ignored
// warning: ls mode length must be like one of next examples: -l / -a / -la / -al
//          otherwise it will be ignored, or it leads to error
// warning: path longer than 50 characters - bad output
// warning: function prints full file paths (not only file name)
int main(int argc, char **argv)
{
    char *path = ".";
    int sorted = 0;
    int show_hidden = 0;

    if (argc == 1)
    {
        return list_files(path, sorted, show_hidden);
    }

    if (argv[1][0] == '-')
    {
        char *ls_mode = argv[1];
        if (strlen(ls_mode) > 3 || strlen(ls_mode) < 2) {
            return print_err_and_return_err_code("Error: Invalid ls mode!\n");
        }

        sorted = (ls_mode[1] == 'l' || ls_mode[2] == 'l');
        show_hidden = (ls_mode[1] == 'a' || ls_mode[2] == 'a');

        if (argc > 2)
        {
            path = argv[2];
        }
    }
    else
    {
        path = argv[1];
    }

    if (!exists(path))
    {
        printf("ls: cannot access '%s': No such file or directory\n", path);
        return 1;
    }

    if (is_regular_file(path))
    {
        print_file_description(path, sorted);
        return 0;
    }
    else
    {
        // if dir path already has '/' at the end, another '/' will not harm
        // it will even work with multiple '/' in a row, like: path/to////file
        /* otherwise could be checked with next code:
            if (path[strlen(path)-1] == '/') {
            }

            but path could have format: path/to/folder///////
            and it will be also legitimate and will work...
            so it doesn't make sense to check or to fix it
        */
        char *full_path = concat_string(path, "/");
        int result = list_files(full_path, sorted, show_hidden);

        free(full_path);

        if (result)
        {
            return print_err_and_return_err_code(strerror(errno));
        }
        else
        {
            return 0;
        }
    }
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int is_dir_entry_not_hidden(const struct dirent *entry)
{
   return entry->d_name[0] != '.';
}

char* concat_string(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void print_file_description(char *path, int show_date_modified)
{
    // warning: path longer than 50 characters - bad output
    fprintf(stdout, "%-50s", path);
    if (show_date_modified)
    {
        struct stat attr;
        stat(path, &attr);
        fprintf(stdout, "%s", ctime(&attr.st_mtime)); // warning: f*cking 'ctime' generates string with '\n' at the end
    }
    else
    {
        printf("\n");
    }
}

// warning: function prints full file paths (not only file name)
int list_files(char *path, int show_sorted, int show_hidden)
{
    int (*sort)(const struct dirent **, const struct dirent **) = show_sorted ? &alphasort : 0;
    int (*filter)(const struct dirent*) = show_hidden ? 0 : &is_dir_entry_not_hidden;

    struct dirent **entries;
    int number_of_entries = scandir(path, &entries, filter, sort);

    if (number_of_entries < 0)
    {
        return errno;
    }

    for (int i = 0; i < number_of_entries; i++)
    {
        char *path_with_name = concat_string(path, entries[i]->d_name);

        print_file_description(path_with_name, show_sorted);

        free(path_with_name);
        free(entries[i]);
    }
    free(entries);
    return 0;
}

int print_err_and_return_err_code(char *err)
{
    fprintf(stderr, "%s\n", err);
    return 1;
}

/*
ls
ls -l : alphabet sort + last modified
ls -a : show hidden
ls path/to/dir or path/to/file

ls -la or ls -al should be possible

return 0 : success
return 1 : minor problems
return 2 : major problems
*/
