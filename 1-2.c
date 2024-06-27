#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ABC(int *arr, int k);	

int main() {
	int arr[10];

	for (int i = 0; i < 10; i++) 
		scanf("%d", &arr[i]);

	for (int i = 0; i < 9; i++) 
		ABC(arr, i);

	for (int i = 0; i < 10; i++)
		printf(" %d", arr[i]);	

	return 0;
}

void ABC(int *arr, int k) {
	int max = -2147483647, idx = 0, *p = NULL;
	
	for (int i = k; i < 10; i++) {
		if (arr[i] > max) {
			max = arr[i];
			idx = i;
		}
	}

	int tmp = arr[idx];
	arr[idx] = arr[k];
	arr[k] = tmp;

	return;
}