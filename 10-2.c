#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
    int num;
} Stack;

void Initialize(Stack* s);  // 스택 초기화 함수
int IsFull(Stack* s);   // 포화 상태 검출 함수
void Push(Stack* s, char item);  // 삽입함수
char Pop(Stack* s); // 삭제함수
int Cal(char arr[]);    // 후위 표기 수식 계산 함수

int main() {
    char arr[MAX_STACK_SIZE];
    int num;
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < num; i++) { //입력받은 정수만큼 반복
        scanf("%s", arr);    //문자열을 입력받고
        int result2 = Cal(arr);  //수식 변환 함수를 실행 후 반환 값을 저장
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

