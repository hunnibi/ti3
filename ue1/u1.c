#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("test.dat", "r");
    
    if (fp == NULL)
        return 1;
    
    char *line = NULL;
    char *endPtr;
    
    size_t len = 0;
    ssize_t read;
    
    int fileSum = 0;
    int calculatedSum = 0;

    read = getline(&line, &len, fp);    
    for (int i = 0; read != -1; i++) 
    {
        if (i == 0) {
            fileSum = strtol(line, NULL, 10);
        } else {
            int val1 = strtol(line, &endPtr, 10);
            int val2 = strtol(endPtr+1, NULL, 10);
            
            calculatedSum += val1 * val2;
        }
        read = getline(&line, &len, fp);
    }
    

    printf("file_sum: %d, calculated_sum: %d\n", fileSum, calculatedSum);

    fclose(fp);
    
    if (line)
        free(line);
   
    exit(EXIT_SUCCESS);
    
    return 0;
}

