#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	char name[9];
	int score;
} Student;

int main() {
	Student *student = (Student*)malloc(sizeof(Student) * 5);

	int total = 0;
	for (int i = 0; i < 5; i++) {
		scanf("%s %d", student[i].name, &student[i].score);
		total += student[i].score;

		getchar();
	}

	int avg = total / 5;

	for (int i = 0; i < 5; i++) {
		if (student[i].score <= avg)
			printf("%s\n", student[i].name);
	}
	
	free(student);

	return 0;
}