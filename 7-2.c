#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int n;
    struct node* next;
} node;

node* initNode(int n);
node* unionFunction(node* arr1, node* arr2);
node* intersectFunction(node* arr1, node* arr2);
void printNode(node* arr);

int main() {
    int n1, n2;

    scanf("%d", &n1);
    node* arr1 = initNode(n1);

    scanf("%d", &n2);
    node* arr2 = initNode(n2);

    // 합집합
    node* unionResult = unionFunction(arr1, arr2);
    if (unionResult->next != NULL) {
        printNode(unionResult);
        printf("\n");
    }
    else {
        printf(" 0\n");
    }

    // 교집합
    node* intersectResult = intersectFunction(arr1, arr2);
    if (intersectResult->next != NULL) {
        printNode(intersectResult);
        printf("\n");
    }
    else {
        printf(" 0\n");
    }


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

node* unionFunction(node* arr1, node* arr2) {
    node* header = (node*)malloc(sizeof(node*));
    header->next = NULL;
    node* p = header;

    node* a = arr1->next;
    node* b = arr2->next;

    while (a != NULL && b != NULL) {
        while (p->next != NULL) {
            p = p->next;
        }

        if (a->n < b->n) {
            node* newNode = (node*)malloc(sizeof(node));
            newNode->n = a->n;
            newNode->next = NULL;

            p->next = newNode;
            a = a->next;
        }
        else if (a->n > b->n) {
            node* newNode = (node*)malloc(sizeof(node));
            newNode->n = b->n;
            newNode->next = NULL;

            p->next = newNode;
            b = b->next;
        }
        else {
            node* newNode = (node*)malloc(sizeof(node));
            newNode->n = a->n;
            newNode->next = NULL;

            p->next = newNode;
            a = a->next;
            b = b->next;
        }
    }

    while (a != NULL) {
        while (p->next != NULL) {
            p = p->next;
        }

        node* newNode = (node*)malloc(sizeof(node));
        newNode->n = a->n;
        newNode->next = NULL;
        p->next = newNode;
        a = a->next;
    }

    while (b != NULL) {
        while (p->next != NULL) {
            p = p->next;
        }

        node* newNode = (node*)malloc(sizeof(node));
        newNode->n = b->n;
        newNode->next = NULL;
        p->next = newNode;
        b = b->next;
    }

    return header;
}

node* intersectFunction(node* arr1, node* arr2) {
    node* header = (node*)malloc(sizeof(node*));
    header->next = NULL;
    node* p = header;

    node* a = arr1->next;
    node* b = arr2->next;

    while (a != NULL && b != NULL) {
        if (a->n < b->n) {
            a = a->next;
        }
        else if (a->n > b->n) {
            b = b->next;
        }
        else {
            while (p->next != NULL) {
                p = p->next;
            }

            node* newNode = (node*)malloc(sizeof(node));
            newNode->n = a->n;
            newNode->next = NULL;

            p->next = newNode;
            a = a->next;
            b = b->next;
        }
    }

    return header;
}

void printNode(node* arr) {
    node* p = arr;
    while (p->next != NULL) {
        p = p->next;
        printf(" %d", p->n);
    }

    return;
}