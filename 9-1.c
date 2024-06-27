#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int stackSize, top;

void push(char* stack, char value);
char pop(char* stack);
void peek(char* stack);
void duplicate(char* stack);
void upRotate(char* stack, int number);
void downRotate(char* stack, int number);
void print(char* stack);

void main() {
    int calculateSize, number;
    char* stack, calculate[10], value;
    scanf("%d", &stackSize);
    stack = (char*)malloc(sizeof(char) * stackSize);
    top = -1;

    scanf("%d", &calculateSize);
    getchar();
    for (int i = 0; i < calculateSize; i++) {
        scanf("%s", calculate);
        getchar();
        if (strcmp(calculate, "PUSH") == 0) {
            scanf("%c", &value);
            getchar();
            push(stack, value);
        }
        else if (strcmp(calculate, "POP") == 0) {
            pop(stack);
        }
        else if (strcmp(calculate, "PEEK") == 0) {
            peek(stack);
        }
        else if (strcmp(calculate, "DUP") == 0) {
            duplicate(stack);
        }
        else if (strcmp(calculate, "UpR") == 0) {
            scanf("%d", &number);
            getchar();
            upRotate(stack, number);
        }
        else if (strcmp(calculate, "DownR") == 0) {
            scanf("%d", &number);
            getchar();
            downRotate(stack, number);
        }
        else if (strcmp(calculate, "PRINT") == 0) {
            print(stack);
        }
    }
    free(stack);
}

void push(char* stack, char value) {
    if (top >= stackSize - 1) {
        printf("Stack FULL\n");
        return;
    }
    stack[++(top)] = value;
}

char pop(char* stack) {
    if (top <= -1) {
        printf("Stack Empty\n");
        return;
    }
    return stack[(top)--];
}

void peek(char* stack) {
    if (top <= -1) {
        printf("Stack Empty\n");
        return;
    }
    printf("%c\n", stack[top]);
}

void duplicate(char* stack) {
    if (top >= stackSize) {
        printf("Stack FULL\n");
        return;
    }
    push(stack, pop(stack));
    push(stack, stack[top]);
}

void upRotate(char* stack, int number) {
    char* tempArray = (char*)malloc(sizeof(char) * number);
    if (number > (top + 1)) {
        free(tempArray);
        return;
    }
    for (int i = 0; i < number; i++) {
        tempArray[i] = pop(stack);
    }
    push(stack, tempArray[0]);
    for (int i = number - 1; i > 0; i--) {
        push(stack, tempArray[i]);
    }
    free(tempArray);
}

void downRotate(char* stack, int number) {
    char* tempArray = (char*)malloc(sizeof(char) * number);
    if (number > (top + 1)) {
        free(tempArray);
        return;
    }
    for (int i = 0; i < number; i++) {
        tempArray[i] = pop(stack);
    }
    for (int i = number - 2; i > -1; i--) {
        push(stack, tempArray[i]);
    }
    push(stack, tempArray[number - 1]);
    free(tempArray);
}

void print(char* stack) {
    for (int i = (top); i > -1; i--) {
        printf("%c", stack[i]);
    }
    printf("\n");
}
