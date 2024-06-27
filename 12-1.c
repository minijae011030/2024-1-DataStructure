#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* left_child;
    struct Node* right_child;
    int data;
    int node;
} Node;

Node* initTree();
Node* makeNode(int data, int node);
void setChild(Node* parent, Node* left_child, Node* right_child);
void findNode(Node* root, int node);


int main() {
    Node* root = initTree();
    int n;
    scanf("%d", &n);

    findNode(root, n);

    if (n >= 9 || n <= 0) printf("-1");

    return 0;
}

Node* initTree() {
    Node* F1 = makeNode(20, 1);
    Node* F2 = makeNode(30, 2);
    Node* F3 = makeNode(50, 3);
    Node* F4 = makeNode(70, 4);
    Node* F5 = makeNode(90, 5);
    Node* F6 = makeNode(120, 6);
    Node* F7 = makeNode(130, 7);
    Node* F8 = makeNode(80, 8);

    setChild(F6, F7, F8);
    setChild(F2, F4, F5);
    setChild(F3, NULL, F6);
    setChild(F1, F2, F3);

    return F1;
}

Node* makeNode(int data, int node) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->node = node;
    newNode->data = data;
    newNode->left_child = NULL;
    newNode->right_child = NULL;

    return newNode;
}

void setChild(Node* parent, Node* left_child, Node* right_child) {
    parent->left_child = left_child;
    parent->right_child = right_child;

    return;
}

void findNode(Node* root, int node) {
    if (root == NULL)
        return;

    if (root->node == node) {
        printf("%d ", root->data);
        if (root->left_child)
            printf("%d ", root->left_child->data);
        if (root->right_child)
            printf("%d", root->right_child->data);

        return;
    }

    findNode(root->left_child, node);
    findNode(root->right_child, node);
}
