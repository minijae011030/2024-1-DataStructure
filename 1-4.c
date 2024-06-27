#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char* word, int len);

int main() {
	char word[100];

	scanf("%s", word);
	
	int len = strlen(word);

	for (int i = 0; i < len; i++) {
		printf("%s\n", word);
		rotate(word, len);
	}

	return 0;
}

void rotate(char* word, int len) {
	char tmp = word[0];

	for (int i = 0; i < len - 1; i++) {
		word[i] = word[i + 1];
	}

	word[len - 1] = tmp;

	return;
}