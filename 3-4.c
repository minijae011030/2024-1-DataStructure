#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max(int* arr, int n);

int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	int max = find_max(arr, n);
	printf("%d\n", max);

	free(arr);

	return 0;
}

int find_max(int* arr, int n) {
	if (n == 1) {
		return arr[0];
	}

	int max = find_max(arr, n - 1);

	if (max > arr[n - 1]) return max;
	else return arr[n - 1];
}
