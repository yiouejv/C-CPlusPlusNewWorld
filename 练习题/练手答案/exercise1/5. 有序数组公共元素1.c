#include <stdio.h>
#include <stdlib.h>

void twoArrayRepeat(int *ans, int *len, int* arr1, int* arr2, const int len1, const int len2) {
    int index1 = 0, index2 = 0;

    while (index1 < len1 && index2 < len2) {
        if (arr1[index1] < arr2[index2]) {
            ++index1;
        }
        else if (arr1[index1] > arr2[index2]) {
            ++index2;
        }
        else {
            ans[(*len)++] = arr1[index1++];
        }
    }
}



int main() {
    int arr1[] = { 1, 2, 3, 4, 5, 6, 7 };
    int arr2[] = { 1, 3, 5, 6 };
    int ans[100] = { 0 };
    int len = 0;
    twoArrayRepeat(ans, &len, arr1, arr2, 7, 4);
    return 0;
}