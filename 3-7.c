#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_spell(char* word, char spell);

int main() {
    char word[101], spell;

    scanf("%s", word);
    getchar();
    scanf("%c", &spell);

    int result = find_spell(word, spell);
    printf("%d\n", result);

    return 0;
}


int find_spell(char* word, char spell) {
    if (*word == '\0')
        return 0;

    return (*word == spell) + find_spell(word + 1, spell);
}