#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int front, rear, q;
    int* arr;
} Queue;

Queue initQueue(int q);
void enqueue(Queue* queue, int element);
void dequeue(Queue* queue);
void print_queue(Queue* queue);

int isEmpty(Queue* queue);
int isFull(Queue* queue);

int main() {
    int q, n, element;
    scanf("%d", &q);
    Queue queue = initQueue(q);

    scanf("%d", &n);
    getchar();

    char cmd;
    for (int i = 0; i < n; i++) {
        scanf("%c", &cmd);
        getchar();

        switch (cmd) {
        case 'I':
            scanf("%d", &element);
            getchar();

            enqueue(&queue, element);
            break;
        case 'D':
            // delete
            dequeue(&queue);
            break;
        case 'P':
            // print
            print_queue(&queue);
            break;
        }
    }
    return 0;
}

Queue initQueue(int q) {
    Queue queue;

    queue.rear = 0;
    queue.front = 0;
    queue.q = q;

    queue.arr = (int*)malloc(sizeof(int) * q);

    for (int i = 0; i < q; i++) {
        queue.arr[i] = 0;
    }

    return queue;
}

void enqueue(Queue* queue, int element) {
    if (isFull(queue)) {
        // 포화 상태
        printf("overflow");
        print_queue(queue);
        exit(1);
    }

    queue->rear++;
    if (queue->rear >= queue->q)
        queue->rear -= queue->q;

    queue->arr[queue->rear] = element;

    return;
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        // 공백 상태
        printf("underflow");
        exit(1);
    }

    queue->front++;
    if (queue->front >= queue->q)
        queue->front -= queue->q;

    queue->arr[queue->front] = 0;

    return;
}

void print_queue(Queue* queue) {
    for (int i = 0; i < queue->q; i++)
        printf(" %d", queue->arr[i]);

    printf("\n");

    return;
}

int isEmpty(Queue* queue) {
    return (queue->rear) % (queue->q) == queue->front;
}

int isFull(Queue* queue) {
    if ((queue->rear + 1) % queue->q == queue->front) return 1;

    return 0;
}