#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mostOnes(int** arr, int n);

int main() {
	int n;
	scanf("%d", &n);

	int** arr = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	int result = mostOnes(arr, n);
	printf("%d\n", result);

	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}

	free(arr);

	return 0;
}

int mostOnes(int** arr, int n) {
	int i = 0, j = 0, max_row = 0;

	while ((i < n) && (j < n)) {	// 마지막 행과 열에 도달하기 전까지 반복
		if (arr[i][j] == 0) {	// 0에 도달하면 다음 행으로 이동
			i++;
		}
		else {	// 1이면 max_row를 변경하고 다음 열로 이동
			max_row = i;
			j++;
		}
	}

	return max_row;
}