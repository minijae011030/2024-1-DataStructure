#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ascending_order(int n);

int main() {
	int n;
	scanf("%d", &n);

	ascending_order(n);

	return 0;
}

void ascending_order(int n) {
	if (n < 10) {
		printf("%d\n", n);

		return;
	}

	printf("%d\n", n % 10);

	return ascending_order(n / 10);
}