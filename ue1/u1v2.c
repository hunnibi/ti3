#include <stdio.h>
#include <stdlib.h>

// no check if file is empty, or doesn't have enough data for calculation
int main(void)
{
    FILE *fp = fopen("test.dat", "r");

    if (fp == NULL)
        return 1;

    int fileSum = 0;
    int calculatedSum = 0;
    int val1 = 0, val2 = 0;

    fscanf(fp, "%d", &fileSum);

    while((fscanf(fp, "%d*%d", &val1, &val2)) != EOF) {
        calculatedSum += val1 * val2;
    }

    fclose(fp);

    int result = (fileSum == calculatedSum) ? 0 : 1;
    printf("Result: %d\n", result);

    return result;
}
