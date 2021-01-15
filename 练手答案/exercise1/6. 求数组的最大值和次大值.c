#include <stdio.h>
#include <stdlib.h>

void arrayMaxAndSecondMax(int *arr, const int len, int *ans) {
	if (len <= 2) {
		return;
	}
	int max, secondMax;
	if (arr[0] > arr[1]) {
		max = arr[0];
		secondMax = arr[1];
	}else {
		max = arr[1];
		secondMax = arr[0];
	}

	for (int i = 2; i < len; ++i) {
		if (arr[i] >= max) {
			secondMax = max;
			max = arr[i];
		}
		else if (arr[i] > secondMax) {
			secondMax = arr[i];
		}else; // pass
	}
	ans[0] = max;
	ans[1] = secondMax;
}

int main(int argc, char const *argv[])
{
	int arr[] = {1, 2, 3};
	int ans[2] = {0};
	arrayMaxAndSecondMax(arr, 3, ans);
	return 0;
}