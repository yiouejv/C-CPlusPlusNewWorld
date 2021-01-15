#include <stdio.h>
#include <stdlib.h>

void testReadString() {
    char c;
    while (scanf("%c", &c) != EOF) {
        printf("%c", c);
    }
}

int main(int argc, char const *argv[])
{
    testReadString();
    return 0;
}