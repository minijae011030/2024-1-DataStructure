#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hanoi(int n, char a, char b, char c);

int main() {
    int n;
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');
    
	return 0;
}

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        printf("%c %c\n", a, c);

        return;
    }

    hanoi(n - 1, a, c, b);
    printf("%c %c\n", a, c);
    hanoi(n - 1, b, a, c);

    return;
}