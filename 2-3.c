#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* prefixAverages1(int* arr, int n);
int* prefixAverages2(int* arr, int n);

int roundNumber(double num);

int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	int* A1 = prefixAverages1(arr, n);
	int* A2 = prefixAverages2(arr, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", A1[i]);
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		printf("%d ", A2[i]);
	}
	printf("\n");

	free(arr);
	free(A1);
	free(A2);

	return 0;
}

int* prefixAverages1(int* arr, int n) {
	int* A = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		double sum = 0.0;
		for (int j = 0; j <= i; j++) {
			sum += arr[j];
		}

		int result = roundNumber(sum / (i + 1));
		A[i] = result;
	}

	return A;
}

int* prefixAverages2(int* arr, int n) {
	int* A = (int*)malloc(sizeof(int) * n);
	double sum = 0.0;

	for (int i = 0; i < n; i++) {
		sum += arr[i];

		int result = roundNumber(sum / (i + 1));
		A[i] = result;
	}

	return A;
}

int roundNumber(double num) {
	int integer = (int)num;
	double decimal = num - integer;

	if (decimal >= 0.5) {
		integer++;
	}

	return integer;
}