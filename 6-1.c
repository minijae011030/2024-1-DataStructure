#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coef;
    int exp;
    struct node* next;
} node;

void appendTerm(node* header, int coef, int exp);
node* addPoly(node* xHeader, node* yHeader);

int main() {
    int num, coef, exp;
    node* firstPoly = (node*)malloc(sizeof(node));
    node* secondPoly = (node*)malloc(sizeof(node));

    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &coef);
        scanf("%d", &exp);
        appendTerm(firstPoly, coef, exp);
    }

    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &coef);
        scanf("%d", &exp);
        appendTerm(secondPoly, coef, exp);
    }

    node* result = addPoly(firstPoly, secondPoly);

    node* p = result->next;

    while (p != NULL) {
        if (p->coef != 0) {
            printf(" %d %d", p->coef, p->exp);
        }
        p = p->next;
    }

    return 0;
}

void appendTerm(node* header, int coef, int exp) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;

    while (header->next != NULL) header = header->next;

    header->next = newNode;

    return;
}

node* addPoly(node* x, node* y) {
    node* result = (node*)malloc(sizeof(node));
    result->next = NULL;

    node* i = x->next;
    node* j = y->next;

    while (i != NULL && j != NULL) {
        if (i->exp > j->exp) {
            appendTerm(result, i->coef, i->exp);
            i = i->next;
        }
        else if (i->exp < j->exp) {
            appendTerm(result, j->coef, j->exp);
            j = j->next;
        }
        else {
            int sum = i->coef + j->coef;
            appendTerm(result, sum, i->exp);
            i = i->next;
            j = j->next;
        }
    }

    while (i != NULL) {
        appendTerm(result, i->coef, i->exp);
        i = i->next;
    }

    while (j != NULL) {
        appendTerm(result, j->coef, j->exp);
        j = j->next;
    }

    return result;
}