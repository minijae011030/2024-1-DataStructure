#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* stack;
int top;

char pop();
void push(char value);
int isEmpty();
int isBalanced(char* sentence);

void main() {
    int count = 0;

    char* sentence = (char*)malloc(sizeof(char) * 1000);
    stack = (char*)malloc(sizeof(char) * 1000);
    top = -1;

    gets(sentence);
    for (int i = 0; i < strlen(sentence); i++) {
        if ((sentence[i] == '(') || (sentence[i] == '{') || (sentence[i] == '[') || (sentence[i] == ')') || (sentence[i] == '}') || (sentence[i] == ']')) {
            count++;
        }
    }

    if (isBalanced(sentence) == 1) printf("OK_%d", count);
    else printf("Wrong_%d", count);

    free(sentence);
    free(stack);
}

char pop() {
    return stack[(top)--];
}

void push(char value) {
    stack[++(top)] = value;
}

int isEmpty() {
    if ((top) == -1)  return 1;

    return 0;
}

int isBalanced(char* sentence) {
    char popItem;

    for (int i = 0; i < strlen(sentence); i++) {    // ������ �ݺ�
        if ((sentence[i] == '(') || (sentence[i] == '{') || (sentence[i] == '[')) { // ���� ��ȣ�̸� stack �迭�� push
            push(sentence[i]);

        }
        else if ((sentence[i] == ')') || (sentence[i] == '}') || (sentence[i] == ']')) {  // ������ ��ȣ�̸�
            if (isEmpty()) return 0;    // ������ ������� return 0

            popItem = pop();    // stack �迭�� ���� pop
            // pop�� ���ҿ� ���� ������ ���Ұ� ���� ������ 0�� ����
            if (sentence[i] == ')' && popItem != '(')
                return 0;
            if (sentence[i] == '(' && popItem != ')')
                return 0;

            if (sentence[i] == '}' && popItem != '{')
                return 0;
            if (sentence[i] == '{' && popItem != '}')
                return 0;

            if (sentence[i] == ']' && popItem != '[')
                return 0;
            if (sentence[i] == '[' && popItem != ']')
                return 0;
        }
    }

    return isEmpty();
}