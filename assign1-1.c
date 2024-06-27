#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int countOnesButSlow(int** arr, int n);	
int countOnes(int** arr, int n);	

int main() {
	int n;
	scanf("%d", &n);
	
	// 이차원배열 동적할당
	int** arr = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}

	// 이차원배열 입력
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	int result1 = countOnesButSlow(arr, n);	// 느린 버전

	int result2 = countOnes(arr, n);	// 빠른 버전

	printf("%d\n", result1);
	printf("%d\n", result2);
	
	// 동적할당 해제
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}

	free(arr);
}

int countOnesButSlow(int** arr, int n) {	// 느린 버전
	int count = 0;
	for (int i = 0; i < n; i++) {	// 행을 반복
		int j = 0;
		while (j < n && arr[i][j] == 1) {	// 행의 원소를 돌면서 마지막이나 1에 다다를 때 까지 1 더함
			count++;
			j++;	// 열 + 1
		}
	}

	return count;
}

int countOnes(int** arr, int n) {	// 빠른 버전
	int count = 0;

	int i = n - 1, j = 0;	// 행은 마지막, 열은 첫번째에서 시작

	while (i >= 0 && j <= n) {	// 첫번째 행, 마지막 열에 도달하기 전까지 반복
		if (arr[i][j] != 1) {	// 원소가 1이 아니면
			count += j;	// 열의 개수만큼 count 더함
			i--;	// 행 - 1
		}
		else {	// 원소가 1이면
			j++;	// 열 + 1
		}

	}

	return count;
}