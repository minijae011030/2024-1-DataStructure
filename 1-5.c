#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Time {
	int hour, min, sec;
} Time;

void TimeCalc(Time t1, Time t2);

int main() {
	Time t1, t2;

	scanf("%d %d %d", &t1.hour, &t1.min, &t1.sec);
	scanf("%d %d %d", &t2.hour, &t2.min, &t2.sec);

	TimeCalc(t1, t2);

	return 0;
}

void TimeCalc(Time t1, Time t2) {
	int t1_total = t1.sec + t1.min * 60 + t1.hour * 3600;
	int t2_total = t2.sec + t2.min * 60 + t2.hour * 3600;

	int calc = t2_total - t1_total;

	printf("%d ", calc / 3600);
	calc = calc % 3600;

	printf("%d ", calc / 60);

	printf("%d", calc % 60);

	return;
}