#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modulo(int a, int b);

int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	int result = modulo(a, b);
	printf("%d\n", result);

	return 0;
}

int modulo(int a, int b) {
	while (a >= b) {
		a -= b;
	}

	return a;
}