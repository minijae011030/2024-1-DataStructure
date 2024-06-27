#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Euclid(int a, int b);

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int result = Euclid(a, b);
    printf("%d\n", result);

    return 0;
}

int Euclid(int a, int b) {
    if (b == 0) {
        return a;
    }

    return Euclid(b, a % b);
}