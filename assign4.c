#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct Node {
    int element;
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* front;
    struct Node* rear;
} Queue;

typedef struct Stack {
    struct Queue* mainQueue;
    struct Queue* subQueue;
} Stack;

Stack initStack();
Node* makeNode(int element);

int generateRandomInt();

// 큐 함수
int isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, int element);
int dequeue(Queue* queue);

// 스택 함수
int isStackEmpty(Stack* stack);
void push(Stack* stack, int element);
int pop(Stack* stack);
int top(Stack* stack);
void millionPush(Stack* stack);

int main() {
    Stack stack = initStack();

    char cmd, input[100];
    int number, n = 0;
    double cputime;

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    while (1) {
        scanf("%c", &cmd);
        getchar();

        switch (cmd) {
        case 'S':
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            if (isStackEmpty(&stack))
                printf("Empty (%d), ", n);
            else
                printf("Nonempty (%d), ", n);

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
            printf("cputime = %.10f\n", cputime);

            break;
        case 't':
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            printf("%d (%d), ", top(&stack), n);

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
            printf("cputime = %.10f\n", cputime);

            break;
        case 'p':
            gets(input);
            char* token = strtok(input, " ");
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            while (token != NULL) {
                number = atoi(token); // 문자열을 정수로 변환
                push(&stack, number);

                n++;
                token = strtok(NULL, " "); // 다음 숫자를 추출하기 위해 NULL 전달
            }

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            printf("OK (%d), cputime = %.10f\n", n, cputime);

            break;
        case 'P':
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            millionPush(&stack);

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            n += 1000000;
            printf("OK (%d), cputime = %.10f\n", n, cputime);

            break;
        case 'o':
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            if (isStackEmpty(&stack))
                printf("Empty Stack Exception!! (%d), ", n);
            else {
                n--;
                printf("%d (%d), ", pop(&stack), n);
            }

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            printf("cputime = %.10f\n", cputime);

            break;
        case 'q':
            return 0;
        }

    }
}

Stack initStack() {
    Stack stack;

    stack.mainQueue = (Queue*)malloc(sizeof(Queue));
    stack.subQueue = (Queue*)malloc(sizeof(Queue));

    stack.mainQueue->front = NULL;
    stack.mainQueue->rear = NULL;

    stack.subQueue->front = NULL;
    stack.subQueue->rear = NULL;

    return stack;
}

Node* makeNode(int element) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->element = element;
    newNode->next = NULL;

    return newNode;
}

int generateRandomInt() {
    int start = 10;
    int end = 99;

    int random_int = rand() % (end - start + 1) + start;

    return random_int;
}

int isQueueEmpty(Queue* queue) {
    if (queue->front == NULL)
        return 1;

    return 0;
}

void enqueue(Queue* queue, int element) {
    Node* newNode = makeNode(element);

    if (isQueueEmpty(queue)) { // 큐가 빈 경우
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;

    return;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }

    Node* temp = queue->front;
    int element = temp->element;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return element;
}

int isStackEmpty(Stack* stack) {
    return isQueueEmpty(stack->mainQueue);
}


void push(Stack* stack, int element) {
    enqueue(stack->mainQueue, element);

    return;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        return -1;
    }

    while (stack->mainQueue->front != stack->mainQueue->rear) {
        int n = dequeue(stack->mainQueue);
        enqueue(stack->subQueue, n);
    }

    int poppedElement = dequeue(stack->mainQueue);

    while (!isQueueEmpty(stack->subQueue)) {
        int n = dequeue(stack->subQueue);
        enqueue(stack->mainQueue, n);
    }

    return poppedElement;
}

int top(Stack* stack) {
    return stack->mainQueue->rear->element;
}

void millionPush(Stack* stack) {
    for (int i = 0; i < 1000000; i++) {
        int random_int = generateRandomInt();
        push(stack, random_int);
    }

    return;
}
