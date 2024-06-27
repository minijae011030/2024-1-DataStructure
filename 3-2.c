#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void descending_order(int n);

int main() {
	int n;
	scanf("%d", &n);

	descending_order(n);

	return 0;
}

void descending_order(int n) {
	if (n < 10) {
		printf("%d\n", n);

		return;
	}

	descending_order(n / 10);
	printf("%d\n", n % 10);

	return;
}