#include <stdio.h>
#include <stdlib.h>


void printDiamond(const int n) {
    for (int i = 1; i < n*2; ++i){
        int space = (i < n) ? (n - i%n) : i%n;
        for (int j = 0; j < space; ++j) printf(" ");

        int star = (i <= n) ? i : (n - i % n);
        for (int j = 0; j < star; ++j) {
            if (j == 0 || j == star - 1) printf("* ");
            else printf("  ");
        }

        printf("\n");
    }
}

int main() {
    printDiamond(5);
    system("pause");
    return 0;
}
