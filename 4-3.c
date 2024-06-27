#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, a = 1;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            for (int j = 1; j <= n; j++) {
                printf(" %d", a);
                a++;
            }
        }
        else {
            a += n - 1;
            for (int j = 1; j <= n; j++) {
                printf(" %d", a);
                a--;
            }
            a += n + 1;
        }

        printf("\n");
    }
    
    return 0;
}