#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    int element;
} Node;

typedef struct Deque {
    Node* front;
    Node* rear;
    int node;
} Deque;

Deque initDeque();
Node* makeNode();

void add_front(Deque* deque, int element);
void add_rear(Deque* deque, int element);
void delete_front(Deque* deque);
void delete_rear(Deque* deque);
void print(Deque* deque);

int isEmpty(Deque* deque);

int main() {
    int n;
    scanf("%d", &n);
    getchar();

    Deque deque = initDeque();

    char buffer[10];
    char* cmd;
    char* element;     // 두 번째 단어를 가리키는 포인터
    int element_as_int; // 두 번째 부분을 정수로 저장할 변수

    for (int i = 0; i < n; i++) {
        // 명령 코드 입력받기
        int has_element_int = 0;
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = 0;

        cmd = strtok(buffer, " ");
        element = strtok(NULL, " ");

        if (element != NULL) {
            char* endptr;
            element_as_int = strtol(element, &endptr, 10);

            if (*endptr == '\0') has_element_int = 1;

        }

        ///////////////////////////////////////////////////////////

        if (strcmp(cmd, "AF") == 0) {
            // add front
            add_front(&deque, element_as_int);
        }
        else if (strcmp(cmd, "AR") == 0) {
            // add rear
            add_rear(&deque, element_as_int);
        }
        else if (strcmp(cmd, "DF") == 0) {
            // delete front
            delete_front(&deque);
        }
        else if (strcmp(cmd, "DR") == 0) {
            // delete rear
            delete_rear(&deque);
        }
        else if (strcmp(cmd, "P") == 0) {
            // print
            print(&deque);
        }
    }

    return 0;
}

Deque initDeque() {
    Deque deque;
    deque.front = NULL;
    deque.rear = NULL;
    deque.node = 0;

    return deque;
}

Node* makeNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void add_front(Deque* deque, int element) {
    Node* newNode = makeNode();
    newNode->element = element;

    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
        deque->node++;

        return;
    }

    deque->front->prev = newNode;
    newNode->next = deque->front;
    deque->front = newNode;

    deque->node++;

    return;
}

void add_rear(Deque* deque, int element) {
    Node* newNode = makeNode();
    newNode->element = element;

    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
        deque->node++;

        return;
    }

    newNode->prev = deque->rear;
    deque->rear->next = newNode;
    deque->rear = newNode;

    deque->node++;

    return;
}

void delete_front(Deque* deque) {
    if (isEmpty(deque)) {
        printf("underflow\n");
        exit(1);
    }

    if (deque->node == 1) {
        free(deque->front);
        deque->front = deque->rear = NULL;
        deque->node--;

        return;
    }

    deque->front->next->prev = deque->front;
    deque->front = deque->front->next;
    deque->front->prev = NULL;

    deque->node--;
    return;
}

void delete_rear(Deque* deque) {

    if (isEmpty(deque)) {
        printf("underflow\n");
        exit(1);
    }

    if (deque->node == 1) {
        free(deque->front);
        deque->front = deque->rear = NULL;
        deque->node--;

        return;
    }

    deque->rear = deque->rear->prev;
    deque->rear->next = NULL;

    deque->node--;
    return;
}

void print(Deque* deque) {
    Node* p = deque->front;
    while (p != NULL) {
        printf(" %d", p->element);
        p = p->next;
    }

    printf("\n");

    return;
}

int isEmpty(Deque* deque) {
    return deque->node == 0;
}