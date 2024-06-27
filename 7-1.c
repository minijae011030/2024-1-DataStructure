#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int n;
    struct node* next;
} node;

node* initNode(int n);
int member(node* p, node* A);
int subset(node* arr1, node* arr2);

int main() {
    int n1, n2;

    scanf("%d", &n1);
    node* arr1 = initNode(n1);

    scanf("%d", &n2);
    node* arr2 = initNode(n2);

    printf("%d\n", subset(arr1, arr2));

    return 0;
}

node* initNode(int n) {
    node* head = (node*)malloc(sizeof(node));

    node* p = head;
    for (int i = 0; i < n; i++) {
        node* newNode = (node*)malloc(sizeof(node));
        scanf("%d", &newNode->n);
        newNode->next = NULL;

        while (p->next != NULL) {
            p = p->next;
        }

        newNode->next = p->next;
        p->next = newNode;
    }

    return head;
}

int member(node* p, node* A) {
    while (A->next != NULL) {
        A = A->next;
        if (p->n == A->n) {

            return 1;
        }
    }

    return 0;
}

int subset(node* arr1, node* arr2) {
    if (arr1->next == NULL)
        return 0;

    node* p = arr1->next;
    while (1) {
        if (member(p, arr2)) {
            if (p->next == NULL)
                return 0;
            p = p->next;
        }
        else {
            return p->n;
        }
    }
}