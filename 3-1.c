#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_sum(int n);

int main() {
	int n;
	scanf("%d", &n);

	int result = calculate_sum(n);
	printf("%d\n", result);

	return 0;
}

int calculate_sum(int n) {
	if (n <= 0) {
		return 0;
	}

	return n + calculate_sum(n - 1);
}
