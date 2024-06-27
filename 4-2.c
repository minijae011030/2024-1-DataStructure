#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	int reverse;
	scanf("%d", &reverse);

	int* reverse_arr = (int*)malloc(sizeof(int) * reverse);
	for (int i = 0; i < reverse; i++)
		scanf("%d", &reverse_arr[i]);


	int tmp = arr[reverse_arr[0]];

	for (int i = reverse - 2; i >= 0; i--) {
		arr[reverse_arr[i + 1]] = arr[reverse_arr[i]];
	}

	arr[reverse_arr[1]] = tmp;
	

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
	free(reverse_arr);

	return 0;
}