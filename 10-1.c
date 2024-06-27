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
int IsEmpty(Stack* s);  // 공백 상태 검출 함수
void Push(Stack* s, char item);  // 삽입함수
char Pop(Stack* s); // 삭제함수
char Peek(Stack* s);    // 피크함수

int prec(char item);  // 연산자의 우선순위를 반환한다.
char* infix_to_postfix(char arr[]); // 수식 변환함수

int main() {
    char arrression[MAX_STACK_SIZE];

    int num;
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < num; i++) {
        scanf("%s", arrression);

        char* result = infix_to_postfix(arrression);
        printf("%s\n", result);
    }

    return 0;
}

void Initialize(Stack* s) {
    s->num = -1;
    return;
}

int IsFull(Stack* s) {
    return (s->num >= (MAX_STACK_SIZE - 1));
}

int IsEmpty(Stack* s) {
    return (s->num == -1);
}

void Push(Stack* s, char item) {
    if (IsFull(s)) return;

    s->data[++(s->num)] = item;
    return;
}

char Pop(Stack* s) {
    return s->data[(s->num)--];
}

char Peek(Stack* s) {
    return s->data[s->num];
}

int prec(char item) {
    if (item == '(' || item == ')') return 0;
    if (item == '|') return 1;
    if (item == '&') return 2;
    if (item == '>' || item == '<') return 3;
    if (item == '+' || item == '-') return 4;
    if (item == '*' || item == '/') return 5;
    if (item == '!' || item == 'p' || item == 'm') return 6;

    return -1;
}

char* infix_to_postfix(char arr[]) {
    int idx = 0;
    int len = strlen(arr);
    char ch, op;

    Stack s;
    Initialize(&s);

    char* stack_arr = (char*)malloc(MAX_STACK_SIZE);

    for (int i = 0; i < len; i++) {
        ch = arr[i];
        if (ch == '+' || ch == '-') {
            if (i == 0) {
                arr[i] = (ch == '+') ? 'p' : 'm';
            }
            else if (arr[i - 1] != ')' && !('A' <= arr[i - 1] && arr[i - 1] <= 'Z')) {
                arr[i] = (ch == '+') ? 'p' : 'm';
            }
        }
    }

    for (int i = 0; i < len; i++) {
        ch = arr[i];

        if ('A' <= ch && ch <= 'Z') {   // 일반 숫자
            stack_arr[idx++] = ch;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '!' || ch == '|' || ch == '&' || ch == 'p' || ch == 'm') {
            while (!IsEmpty(&s) && (prec(ch) <= prec(Peek(&s)))) {
                stack_arr[idx++] = Peek(&s);
                Pop(&s);
            }

            if (ch == '|' || ch == '&') {
                i++;
                Push(&s, ch);
                Push(&s, ch);
            }
            else {
                Push(&s, ch);
            }

        }
        else if (ch == '(') {
            Push(&s, ch);

        }
        else if (ch == ')') {
            op = Pop(&s);

            while (op != '(') {
                stack_arr[idx++] = op;
                op = Pop(&s);
            }
        }
    }

    while (!IsEmpty(&s)) {
        op = Peek(&s);
        Pop(&s);
        stack_arr[idx++] = op;
    }

    stack_arr[idx] = '\0';

    for (int i = 0; i < idx; i++) {
        if (stack_arr[i] == 'p') stack_arr[i] = '+';
        if (stack_arr[i] == 'm') stack_arr[i] = '-';
    }
    return stack_arr;
}