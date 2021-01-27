#include <stdio.h>
#include <stdlib.h>

int findRepeatNumber(int *arr, const int len) {
	int visited[1001] = {0};
    for (int i = 0; i < len; ++i) {
        if (visited[arr[i]] == 1) return arr[i];
        visited[arr[i]] = 1;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
	int arr[1001] = {0};
	arr[0] = 100;
	for (int i = 1; i < 1001; ++i) {
		arr[i] = i;
	}
	findRepeatNumber(arr, 1000);
	return 0;
}