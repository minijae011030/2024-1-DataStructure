#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int countOnesButSlow(int** arr, int n);	
int countOnes(int** arr, int n);	

int main() {
	int n;
	scanf("%d", &n);
	
	// �������迭 �����Ҵ�
	int** arr = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n);
	}

	// �������迭 �Է�
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	int result1 = countOnesButSlow(arr, n);	// ���� ����

	int result2 = countOnes(arr, n);	// ���� ����

	printf("%d\n", result1);
	printf("%d\n", result2);
	
	// �����Ҵ� ����
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}

	free(arr);
}

int countOnesButSlow(int** arr, int n) {	// ���� ����
	int count = 0;
	for (int i = 0; i < n; i++) {	// ���� �ݺ�
		int j = 0;
		while (j < n && arr[i][j] == 1) {	// ���� ���Ҹ� ���鼭 �������̳� 1�� �ٴٸ� �� ���� 1 ����
			count++;
			j++;	// �� + 1
		}
	}

	return count;
}

int countOnes(int** arr, int n) {	// ���� ����
	int count = 0;

	int i = n - 1, j = 0;	// ���� ������, ���� ù��°���� ����

	while (i >= 0 && j <= n) {	// ù��° ��, ������ ���� �����ϱ� ������ �ݺ�
		if (arr[i][j] != 1) {	// ���Ұ� 1�� �ƴϸ�
			count += j;	// ���� ������ŭ count ����
			i--;	// �� - 1
		}
		else {	// ���Ұ� 1�̸�
			j++;	// �� + 1
		}

	}

	return count;
}