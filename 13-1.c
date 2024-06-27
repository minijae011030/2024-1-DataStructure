#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int id;
    int data;
} Node;

typedef struct Tree {
    struct Node* root;
} Tree;

Node* makeNode(int id, int data);
void setChild(Node* parent, Node* left, Node* right);
Tree initTree();
Node* findNode(Node* root, int id);
void preOrder(Node* node); // 선위순회
void inOrder(Node* node);   // 중위순회
void postOrder(Node* node); // 후위순회

int main() {
    Tree tree = initTree();

    int cmd, id;
    scanf("%d %d", &cmd, &id);

    Node* startNode = findNode(tree.root, id);

    if (startNode) {
        switch (cmd) {
        case 1:
            preOrder(startNode);
            break;
        case 2:
            inOrder(startNode);
            break;
        case 3:
            postOrder(startNode);
            break;
        }
    }
    else {
        printf("-1");
    }


    return 0;
}

Node* makeNode(int id, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->id = id;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void setChild(Node* parent, Node* left, Node* right) {
    parent->left = left;
    parent->right = right;

    return;
}

Tree initTree() {
    Tree tree;

    Node* n1 = makeNode(1, 20);
    Node* n2 = makeNode(2, 30);
    Node* n3 = makeNode(3, 50);
    Node* n4 = makeNode(4, 70);
    Node* n5 = makeNode(5, 90);
    Node* n6 = makeNode(6, 120);
    Node* n7 = makeNode(7, 130);
    Node* n8 = makeNode(8, 80);

    tree.root = n1;

    setChild(n1, n2, n3);
    setChild(n2, n4, n5);
    setChild(n3, NULL, n6);
    setChild(n6, n7, n8);

    return tree;
}

Node* findNode(Node* root, int id) {
    if (root == NULL) return NULL;
    if (root->id == id)  return root;

    Node* leftResult = findNode(root->left, id);
    if (leftResult != NULL) return leftResult;

    return findNode(root->right, id);
}

void preOrder(Node* node) {
    if (node == NULL) return;

    printf(" %d", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Node* node) {
    if (node == NULL) return;

    inOrder(node->left);
    printf(" %d", node->data);
    inOrder(node->right);
}

void postOrder(Node* node) {
    if (node == NULL) return;

    postOrder(node->left);
    postOrder(node->right);
    printf(" %d\n", node->data);
}