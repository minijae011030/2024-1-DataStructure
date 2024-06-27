#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int n);

int main() {
	int n;
	scanf("%d", &n);

	printf("%d", sum(n));

	return 0;
}

int sum(int n) {
	int total = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			total += j;
		}
	}

	return total;
}