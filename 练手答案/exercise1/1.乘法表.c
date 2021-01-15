#include <stdio.h>
#include <stdlib.h>

void printTable(const int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("%2d x %2d = %2d ", i, j, i*j);
        }
        printf("\n");
    }
}


int main()
{
    printTable(9);
    system("pause");
    return 0;
}