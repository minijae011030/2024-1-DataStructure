#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// 느린 버전 함수 선언
int countOnesButSlow(int** arr, int n);
// 빠른 버전 함수 선언
int countOnes(int** arr, int n);

// 난수 생성 함수 선언
int generateRandomMatrix(int** arr, int n);

int main() {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int n_value[] = { 30000, 10000, 20000 };

    for (int i = 0; i < 3; i++) {
        // 배열 동적할당
        int** arr = (int**)malloc(sizeof(int*) * n_value[i]);

        for (int j = 0; j < n_value[i]; j++) {
            arr[j] = (int*)malloc(sizeof(int) * n_value[i]);
        }

        int kTotal = generateRandomMatrix(arr, n_value[i]);

        // 느린 버전 실행
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int slow_ones = countOnesButSlow(arr, n_value[i]);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        double slow_time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

        printf("kTotal: %d, ones (slow): %d, cputime (n = %d for slow): %.12f seconds\n", kTotal, slow_ones, n_value[i], slow_time); // 느린 버전 출력

        // 배열 동적할당 해제
        for (int j = 0; j < n_value[i]; j++) {
            free(arr[j]);
        }

        free(arr);
    }

    for (int i = 0; i < 3; i++) {
        // 배열 동적할당
        int** arr = (int**)malloc(sizeof(int*) * n_value[i]);

        for (int j = 0; j < n_value[i]; j++) {
            arr[j] = (int*)malloc(sizeof(int) * n_value[i]);
        }

        int kTotal = generateRandomMatrix(arr, n_value[i]);

        // 빠른 버전 실행
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int fast_ones = countOnes(arr, n_value[i]);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        double fast_time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

        printf("kTotal: %d, ones (fast): %d, cputime (n = %d for fast): %.12f seconds\n", kTotal, fast_ones, n_value[i], fast_time); // 빠른 버전 먼저 출력

        // 배열 동적할당 해제
        for (int j = 0; j < n_value[i]; j++) {
            free(arr[j]);
        }

        free(arr);
    }
}

// 난수 생성 함수 정의
int generateRandomMatrix(int** arr, int n) {
    int kTotal = 0;
    int start = n * 0.9;
    int end = n;

    for (int i = 0; i < n; i++) {
        int range = rand() % (end - start + 1) + start;   // 난수 발생
        kTotal += range;

        // 1로 초기화
        for (int j = 0; j < range; j++) {
            arr[i][j] = 1;
        }
        // 0으로 초기화
        for (int j = range; j < n; j++) {
            arr[i][j] = 0;
        }

        // 범위 재설정
        start = range * 0.9;
        end = range;
    }

    return kTotal;
}

// 느린 버전 함수 정의
int countOnesButSlow(int** arr, int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {   // 행을 반복
        for (int j = 0; j < n; j++) {   // 열을 반복
            if (arr[i][j] == 1) {
                count++;
            }
        }
    }

    return count;
}

// 빠른 버전 함수 정의
int countOnes(int** arr, int n) {
    int count = 0;
    int i = n - 1, j = 0;   // 행은 마지막, 열은 첫번째에서 시작

    while (i >= 0 && j < n) {   // 첫번째 행, 마지막 열에 도달하기 전까지 반복
        if (arr[i][j] != 1) {   // 원소가 1이 아니면
            count += j; // 열의 개수만큼 count 더함
            i--;    // 행 - 1
        }
        else {    // 원소가 1이면
            j++;    // 열 + 1
        }
    }

    if (arr[0][n - 1] == 1) {
        count += n;
    }

    return count;
}
