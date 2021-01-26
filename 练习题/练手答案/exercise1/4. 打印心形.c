#include <stdio.h>
#include <stdlib.h>


void printStar(const int n) {
	if (n < 10) return;
	int starHead = (n / 2) - 2;
	int line = n + starHead;
	for (int i = 0; i < line; ++i) {
		if (i < starHead) {
			int space = starHead - i;
			for (int j = 0; j < space; ++j) printf(" ");
			for (int j = 0; j < 2 + i; ++j) printf("* ");
			for (int j = 0; j < 2*space; ++j) printf(" ");
			for (int j = 0; j < 2 + i; ++j) printf("* ");
		}else {
			int space = i - starHead;
			for (int i = 0; i < space; ++i) printf(" ");
			for (int j = 0; j < n - i + starHead; ++j) printf("* ");
		}
		printf("\n");
	}
}


int main() {
	printStar(10);
	system("pause");
	return 0;
}