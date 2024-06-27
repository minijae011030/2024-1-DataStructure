#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int ar[100][100], n, m;
    scanf("%d %d", &n, &m);

    int i = 0, j = 0, a = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            ar[i][j] = 0;
        }
    }
    i = 0, j = 0;

    ar[i][j] = 1;
    a = 2;

    while (a <= n * m) {
        while (j + 1 < m && ar[i][j + 1] == 0) {
            j++;
            ar[i][j] = a;
            a++;
        }

        while (i + 1 < n && ar[i + 1][j] == 0) {
            i++;
            ar[i][j] = a;
            a++;
        }

        while (j - 1 >= 0 && ar[i][j - 1] == 0) {
            j--;
            ar[i][j] = a;
            a++;
        }

        while (i - 1 >= 0 && ar[i - 1][j] == 0) {
            i--;
            ar[i][j] = a;
            a++;
        }
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < m; b++) {
            printf(" %d", ar[a][b]);
        }
        printf("\n");
    }

    return 0;
}