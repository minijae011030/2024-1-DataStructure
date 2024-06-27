#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// ���� ���� �Լ� ����
int countOnesButSlow(int** arr, int n);
// ���� ���� �Լ� ����
int countOnes(int** arr, int n);

// ���� ���� �Լ� ����
int generateRandomMatrix(int** arr, int n);

int main() {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int n_value[] = { 30000, 10000, 20000 };

    for (int i = 0; i < 3; i++) {
        // �迭 �����Ҵ�
        int** arr = (int**)malloc(sizeof(int*) * n_value[i]);

        for (int j = 0; j < n_value[i]; j++) {
            arr[j] = (int*)malloc(sizeof(int) * n_value[i]);
        }

        int kTotal = generateRandomMatrix(arr, n_value[i]);

        // ���� ���� ����
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int slow_ones = countOnesButSlow(arr, n_value[i]);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        double slow_time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

        printf("kTotal: %d, ones (slow): %d, cputime (n = %d for slow): %.12f seconds\n", kTotal, slow_ones, n_value[i], slow_time); // ���� ���� ���

        // �迭 �����Ҵ� ����
        for (int j = 0; j < n_value[i]; j++) {
            free(arr[j]);
        }

        free(arr);
    }

    for (int i = 0; i < 3; i++) {
        // �迭 �����Ҵ�
        int** arr = (int**)malloc(sizeof(int*) * n_value[i]);

        for (int j = 0; j < n_value[i]; j++) {
            arr[j] = (int*)malloc(sizeof(int) * n_value[i]);
        }

        int kTotal = generateRandomMatrix(arr, n_value[i]);

        // ���� ���� ����
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int fast_ones = countOnes(arr, n_value[i]);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        double fast_time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

        printf("kTotal: %d, ones (fast): %d, cputime (n = %d for fast): %.12f seconds\n", kTotal, fast_ones, n_value[i], fast_time); // ���� ���� ���� ���

        // �迭 �����Ҵ� ����
        for (int j = 0; j < n_value[i]; j++) {
            free(arr[j]);
        }

        free(arr);
    }
}

// ���� ���� �Լ� ����
int generateRandomMatrix(int** arr, int n) {
    int kTotal = 0;
    int start = n * 0.9;
    int end = n;

    for (int i = 0; i < n; i++) {
        int range = rand() % (end - start + 1) + start;   // ���� �߻�
        kTotal += range;

        // 1�� �ʱ�ȭ
        for (int j = 0; j < range; j++) {
            arr[i][j] = 1;
        }
        // 0���� �ʱ�ȭ
        for (int j = range; j < n; j++) {
            arr[i][j] = 0;
        }

        // ���� �缳��
        start = range * 0.9;
        end = range;
    }

    return kTotal;
}

// ���� ���� �Լ� ����
int countOnesButSlow(int** arr, int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {   // ���� �ݺ�
        for (int j = 0; j < n; j++) {   // ���� �ݺ�
            if (arr[i][j] == 1) {
                count++;
            }
        }
    }

    return count;
}

// ���� ���� �Լ� ����
int countOnes(int** arr, int n) {
    int count = 0;
    int i = n - 1, j = 0;   // ���� ������, ���� ù��°���� ����

    while (i >= 0 && j < n) {   // ù��° ��, ������ ���� �����ϱ� ������ �ݺ�
        if (arr[i][j] != 1) {   // ���Ұ� 1�� �ƴϸ�
            count += j; // ���� ������ŭ count ����
            i--;    // �� - 1
        }
        else {    // ���Ұ� 1�̸�
            j++;    // �� + 1
        }
    }

    if (arr[0][n - 1] == 1) {
        count += n;
    }

    return count;
}
