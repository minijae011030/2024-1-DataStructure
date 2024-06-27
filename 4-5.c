#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int** arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) 
        arr[i] = (int*)malloc(sizeof(int) * m);
    
    int row = n, col = m;
    int i = 0, j = 0;
    int a = 1;

    for (i = 0; i < n; i++) 
        for (j = 0; j < m; j++) 
            arr[i][j] = 0;


    int current_i = 0;
    int current_j = 0;

    arr[current_i][current_j] = 1;
    a = 1;

    while (current_j + 1 < m && arr[current_i][current_j + 1] == 0) {
        current_j++;
        a++;
        i = current_i;
        j = current_j;
        arr[i][j] = a;

        while (i + 1 < n && j - 1 >= 0 && arr[i + 1][j + 1] == 0) {
            a++;
            arr[i + 1][j - 1] = a;
            i++;
            j--;
        }
    }

    while (current_i + 1 < n && arr[current_i + 1][current_j] == 0) {
        current_i++;
        a++;
        i = current_i;
        j = current_j;
        arr[i][j] = a;

        while (i + 1 < n && j - 1 >= 0 && arr[i + 1][j - 1] == 0) {
            a++;
            arr[i + 1][j - 1] = a;
            i++;
            j--;
        }
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < m; b++) 
            printf(" %d", arr[a][b]);
        
        printf("\n");
    }

    for (int i = 0; i < m; i++)
        free(arr[i]);

    free(arr);

    return 0;
}