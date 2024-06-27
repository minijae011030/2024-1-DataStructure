#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char name[8];
	int kor, eng, math;
	double avg;
} Student;

int main() {
	int n;
	scanf("%d", &n);

	Student* student = (Student*)malloc(sizeof(Student) * n);
	
	for (int i = 0; i < n; i++) {
		scanf("%s %d %d %d", student[i].name, &student[i].kor, &student[i].eng, &student[i].math);
		getchar();

		student[i].avg = (student[i].kor + student[i].eng + student[i].math) / 3.0;
	}

	for (int i = 0; i < n; i++) {
		printf("%s %.1f ", student[i].name, student[i].avg);

		if (student[i].kor >= 90 || student[i].eng >= 90 || student[i].math >= 90) {
			printf("GREAT ");
		}

		if (student[i].kor < 70 || student[i].eng < 70 || student[i].math < 70) {
			printf("BAD");
		}

		printf("\n");
	}

	free(student);

	return 0;
}