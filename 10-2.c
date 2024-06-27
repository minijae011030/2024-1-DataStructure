#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
    int num;
} Stack;

void Initialize(Stack* s);  // ���� �ʱ�ȭ �Լ�
int IsFull(Stack* s);   // ��ȭ ���� ���� �Լ�
void Push(Stack* s, char item);  // �����Լ�
char Pop(Stack* s); // �����Լ�
int Cal(char arr[]);    // ���� ǥ�� ���� ��� �Լ�

int main() {
    char arr[MAX_STACK_SIZE];
    int num;
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < num; i++) { //�Է¹��� ������ŭ �ݺ�
        scanf("%s", arr);    //���ڿ��� �Է¹ް�
        int result2 = Cal(arr);  //���� ��ȯ �Լ��� ���� �� ��ȯ ���� ����
        printf("%d\n", result2);
    }

    return 0;
}

void Initialize(Stack* s) {
    s->num = -1;
}

int IsFull(Stack* s) {
    return (s->num >= (MAX_STACK_SIZE - 1));
}

void Push(Stack* s, char item) {
    if (IsFull(s)) return;

    s->data[++(s->num)] = item;
    return;
}

char Pop(Stack* s) {
    return s->data[(s->num)--];
}

int Cal(char arr[]) {
    int op1, op2, value;
    char ch;
    Stack s;

    Initialize(&s);

    for (int i = 0; i < (int)strlen(arr); i++) {
        ch = arr[i];

        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = ch - '0';
            Push(&s, value);
        }
        else {
            op2 = Pop(&s);
            op1 = Pop(&s);

            switch (ch) {
            case '+': Push(&s, op1 + op2); break;
            case '-': Push(&s, op1 - op2); break;
            case '*': Push(&s, op1 * op2); break;
            case '/': Push(&s, op1 / op2); break;
            }
        }
    }

    return Pop(&s);
}

