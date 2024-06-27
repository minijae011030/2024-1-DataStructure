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
    int n;  // ���ÿ� �ִ� ����� ����
    struct Node* top;   // ������ ��� ���
    struct Stack* minStack; // �ּҰ� ����
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
    char* element;     // �� ��° �ܾ ����Ű�� ������
    int element_as_int; // �� ��° �κ��� ������ ������ ����

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    while (1) {
        // ��� �ڵ� �Է¹ޱ�
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
            // ���� ����
            return 0;
        } 
        else if (strcmp(cmd, "p") == 0) {
            if (has_element_int) {
                QueryPerformanceFrequency(&ticksPerSec);
                QueryPerformanceCounter(&start);

                push(&stack, element_as_int);    // ���ÿ� ���� e�� ����

                QueryPerformanceCounter(&end);
                diff.QuadPart = end.QuadPart - start.QuadPart;
                double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

                stack.n++; // ���� ��� ���� ����
                printf("push %d (%d), cputime = %.7f\n", element_as_int, stack.n, cputime);
            }
            else {
                QueryPerformanceFrequency(&ticksPerSec);
                QueryPerformanceCounter(&start);

                pushMillion(&stack);    // ���ÿ� 100���� ���Ҹ� ����

                QueryPerformanceCounter(&end);
                diff.QuadPart = end.QuadPart - start.QuadPart;
                double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

                stack.n += 1000000; // ���� ��� ���� ����
                printf("push (%d), cputime = %.7f\n", stack.n, cputime);
            }
        }
        else if (strcmp(cmd, "o") == 0) {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            int e = pop(&stack);    // �������κ��� ���Ҹ� ����

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            stack.n--;  // ���� ��� ���� ����
            if (e) printf("pop %d (%d), cputime = %.7f\n", e, stack.n, cputime);
        }
        else if (strcmp(cmd, "O") == 0) {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);

            popMillion(&stack); // �������κ��� 100���� ���Ҹ� ����

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            double cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

            stack.n -= 1000000; // ���� ��� ���� ����
            printf("popMillion (%d), cputime = %.7f\n", stack.n, cputime);
        }
        else if (strcmp(cmd, "f") == 0) {
            // ���� ���� �� �ּҰ� ���
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

Stack initStack() { // ������ �ʱ�ȭ �ϴ� �Լ�
    Stack stack;

    stack.n = 0;    // ��� ���� �ʱ�ȭ
    stack.top = NULL;   // ��� ���� �ʱ�ȭ

    stack.minStack = (Stack*)malloc(sizeof(Stack)); // �ּҰ� ���� �ʱ�ȭ
    *stack.minStack = (Stack){ 0, NULL, NULL }; // �ּҰ� ���� �ʱ�ȭ

    return stack;
}

Node* makeNode(int element) {   // ��� �����ϴ� �Լ�
    Node* node = (Node*)malloc(sizeof(Node));
    node->element = element;
    node->next = NULL;

    return node;
}

void push(Stack* stack, int element) {  // ���ÿ� ��带 �����ϴ� �Լ�
    Node* newNode = makeNode(element);  // ���ο� ��� ����

    newNode->next = stack->top; // ������ ��ܿ� ���ο� ��� �߰�
    stack->top = newNode;   // ��� ������Ʈ

    // �ּҰ� ���ÿ� ������Ʈ
    if (stack->minStack->top == NULL || element <= stack->minStack->top->element) {
        Node* minNode = makeNode(element); // �ּҰ� ��� ����
        minNode->next = stack->minStack->top; // �ּҰ� ������ ��ܿ� �߰�
        stack->minStack->top = minNode; // �ּҰ� ���� ��� ������Ʈ
        stack->minStack->n++; // �ּҰ� ���� ũ�� ����
    }

    return;
}

int pop(Stack* stack) { // ���ÿ��� ��带 �����ϴ� �Լ�
    if (stack->n == 0) {    // ������ ����ִ� ���
        printf("stack is empty\n");
        return NULL;
    }

    Node* topNode = stack->top; // ��� ���
    int element = topNode->element;

    stack->top = topNode->next; // ���� ��带 ������� ������Ʈ
    free(topNode);  // ��� ��� ����

    // �ּҰ� ���ÿ����� �ּҰ� ��
    if (element == stack->minStack->top->element) {
        Node* minTopNode = stack->minStack->top;
        stack->minStack->top = minTopNode->next; // �ּҰ� ������ ��� ������Ʈ
        free(minTopNode); // �ּҰ� ��� ����
        stack->minStack->n--; // �ּҰ� ���� ũ�� ����
    }

    return element;
}

void pushMillion(Stack* stack) {    // ���ÿ� 100������ ��带 �����ϴ� �Լ�
    for (int i = 0; i < 1000000; i++) {
        int random_int = generateRandonInt();    // 1000~9999 ���� ���� ����
        push(stack, random_int);   // ���ÿ� ��� ����
    }

    return;
}

void popMillion(Stack* stack) { // ���ÿ� 100������ ��带 �����ϴ� �Լ�
    for (int i = 0; i < 1000000; i++) {
        pop(stack);
    }

    return;
}


int getMin(Stack* stack) {  // ���ÿ��� �ּҰ��� ��� �Լ�
    return stack->minStack->top->element; // �ּҰ� ��ȯ
}