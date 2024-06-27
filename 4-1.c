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

	int* reverse_arr = (int*)malloc(sizeof(int) * reverse * 2);
	for (int i = 0; i < reverse * 2; i++)
		scanf("%d", &reverse_arr[i]);
	

	for (int i = 0; i < reverse * 2; i += 2) {
		int start_idx = reverse_arr[i];
		int end_idx = reverse_arr[i + 1];

		for (int i = 0; i <= (end_idx - start_idx) / 2; i++) {
			int tmp = arr[start_idx + i];
			arr[start_idx + i] = arr[end_idx - i];
			arr[end_idx - i] = tmp;
		}
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
	free(reverse_arr);

	return 0;
}