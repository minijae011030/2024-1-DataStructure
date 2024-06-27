#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int n;
	scanf("%d", &n);

	int* arr1 = (int*)malloc(sizeof(int) * n);
	int* arr2 = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) 
		scanf("%d", &arr1[i]);
	
	for (int i = 0; i < n; i++) 
		scanf("%d", &arr2[i]);

	for (int i = 0; i < n; i++)
		printf(" %d", arr1[i] + arr2[n - i - 1]);

	free(arr1);
	free(arr2);

	return 0;
}