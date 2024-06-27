#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct Node {
    struct Node* next;
    int element;
} Node;

typedef struct Stack {
    int n;  // 스택에 있는 노드의 개수
    struct Node* top;   // 스택의 상단 노드
    struct Stack* minStack; // 최소값 스택
} Stack;

int generateRandonInt();

Stack initStack();
Node* makeNode(int element);

void push(Stack* stack, int element);
int pop(Stack* stack);
void pushMillion(Stack* stack);
void popMillion(Stack* stack);
int getMin(Stack* stack);

int main() {
    Stack stack = initStack();

    char buffer[10]; 
    char* cmd;
    char* element;     // 두 번째 단어를 가리키는 포인터
    int element_as_int; // 두 번째 부분을 정수로 저장할 변수

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    while (1) {
        // 명령 코드 입력받기
        int has_element_int = 0;
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        cmd = strtok(buffer, " "); 
        element = strtok(NULL, " "); 

        if (element != NULL) {
            char* endptr;
            element_as_int = strtol(element, &endptr, 10);

            if (*endptr == '\0')  has_element_int = 1; 
            
        }

        /////////////////////////////////////

        if (strcmp(cmd, "q") == 0) {
            // 수행 종료
            return 0;
        } 
        else if (strcmp(cmd, "p") == 0) {
            if (has_element_int) {
                QueryPerformanceFrequency(&ticksPerSec);
                QueryPerformanceCounter(&start);

                push(&stack, element_as_int);    // 스택에 원소 e를 삽입

                QueryPerformanceCounter(&end);
                diff.QuadPart = end.QuadPart - start.QuadPart;
                double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

                stack.n++; // 스택 노드 개수 증가
                printf("push %d (%d), cputime = %.7f\n", element_as_int, stack.n, cputime);
            }
            else {
                QueryPerformanceFrequency(&ticksPerSec);
                QueryPerformanceCounter(&start);

                pushMillion(&stack);    // 스택에 100만개 원소를 삽입

                QueryPerformanceCounter(&end);
                diff.QuadPart = end.QuadPart - start.QuadPart;
                double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

                stack.n += 1000000; // 스택 노드 개수 증가
                printf("push (%d), cputime = %.7f\n", stack.n, cputime);
            }
        }
        else if (strcmp(cmd, "o") == 0) {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            int e = pop(&stack);    // 스택으로부터 원소를 삭제

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            stack.n--;  // 스택 노드 개수 감소
            if (e) printf("pop %d (%d), cputime = %.7f\n", e, stack.n, cputime);
        }
        else if (strcmp(cmd, "O") == 0) {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            popMillion(&stack); // 스택으로부터 100만개 원소를 삭제

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            stack.n -= 1000000; // 스택 노드 개수 감소
            printf("popMillion (%d), cputime = %.7f\n", stack.n, cputime);
        }
        else if (strcmp(cmd, "f") == 0) {
            // 스택 원소 중 최소값 출력
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            int min = getMin(&stack);

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            printf("min %d (%d), cputime = %.7f\n", min, stack.n, cputime);
        }

    }
   

    return 0;
}

int generateRandonInt() {
    int start = 1000;
    int end = 9999;
    int random_int = rand() % (end - start + 1) + start;

    return random_int;
}

Stack initStack() { // 스택을 초기화 하는 함수
    Stack stack;

    stack.n = 0;    // 노드 개수 초기화
    stack.top = NULL;   // 상단 개수 초기화

    stack.minStack = (Stack*)malloc(sizeof(Stack)); // 최소값 스택 초기화
    *stack.minStack = (Stack){ 0, NULL, NULL }; // 최소값 스택 초기화

    return stack;
}

Node* makeNode(int element) {   // 노드 생성하는 함수
    Node* node = (Node*)malloc(sizeof(Node));
    node->element = element;
    node->next = NULL;

    return node;
}

void push(Stack* stack, int element) {  // 스택에 노드를 삽입하는 함수
    Node* newNode = makeNode(element);  // 새로운 노드 생성

    newNode->next = stack->top; // 스택의 상단에 새로운 노드 추가
    stack->top = newNode;   // 상단 업데이트

    // 최소값 스택에 업데이트
    if (stack->minStack->top == NULL || element <= stack->minStack->top->element) {
        Node* minNode = makeNode(element); // 최소값 노드 생성
        minNode->next = stack->minStack->top; // 최소값 스택의 상단에 추가
        stack->minStack->top = minNode; // 최소값 스택 상단 업데이트
        stack->minStack->n++; // 최소값 스택 크기 증가
    }

    return;
}

int pop(Stack* stack) { // 스택에서 노드를 제거하는 함수
    if (stack->n == 0) {    // 스택이 비어있는 경우
        printf("stack is empty\n");
        return NULL;
    }

    Node* topNode = stack->top; // 상단 노드
    int element = topNode->element;

    stack->top = topNode->next; // 다음 노드를 상단으로 업데이트
    free(topNode);  // 상단 노드 해제

    // 최소값 스택에서도 최소값 팝
    if (element == stack->minStack->top->element) {
        Node* minTopNode = stack->minStack->top;
        stack->minStack->top = minTopNode->next; // 최소값 스택의 상단 업데이트
        free(minTopNode); // 최소값 노드 해제
        stack->minStack->n--; // 최소값 스택 크기 감소
    }

    return element;
}

void pushMillion(Stack* stack) {    // 스택에 100만개의 노드를 삽입하는 함수
    for (int i = 0; i < 1000000; i++) {
        int random_int = generateRandonInt();    // 1000~9999 사이 난수 생성
        push(stack, random_int);   // 스택에 노드 삽입
    }

    return;
}

void popMillion(Stack* stack) { // 스택에 100만개의 노드를 삭제하는 함수
    for (int i = 0; i < 1000000; i++) {
        pop(stack);
    }

    return;
}


int getMin(Stack* stack) {  // 스택에서 최소값을 얻는 함수
    return stack->minStack->top->element; // 최소값 반환
}