#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char question[256];
    struct Node* left;
    struct Node* right;
} Node;

Node* buildDecisionTree();
Node* makeExternalNode();
Node* makeInternalNode(int depth);
void runDecisionTree(Node* tree);
void processNode(Node* tree);

bool isInternal(Node* node);

int main() {
    Node* tree = buildDecisionTree();  // Ʈ�� ����

    for (int i = 0; i < 3; i++) {   // �� �� ���α׷� ����
        printf("***Please answer questions\n");
        runDecisionTree(tree);
    }

    return 0;
}

Node* buildDecisionTree() {
    printf("*** Let's build a dichotomous QA system\n");
    Node* root = makeInternalNode(0);   // ���̸� 0���� ����

    return root;
}

Node* makeExternalNode() {  // �ܺγ�� ����
    Node* newNode = (Node*)malloc(sizeof(Node));


    printf("Enter decision: "); // ���� �Է¹ޱ�
    gets(newNode->question);
    newNode->left = NULL;   // �ܺγ��� ����
    newNode->right = NULL;

    return newNode;
}

Node* makeInternalNode(int depth) { // ���γ�� ����
    Node* newNode = (Node*)malloc(sizeof(Node));

    char question[256]; // ���� �Է¹ޱ�
    printf("Enter question: ");
    gets(question);
    strcpy(newNode->question, question);


    printf("Question if yes to '%s'? ", question);  // ���� �ڽĿ� ���� ����
    char child[10];
    gets(child);

    if (strcmp(child, "yes") == 0) {    // ���γ�带 ���� ��
        if (depth < 4) {    // ��ȿ�� ������ ��
            newNode->left = makeInternalNode(depth + 1);    // ���γ�� ����
        }
        else {    // ��ȿ���� ���� ������ ��
            printf("invalid depth. make external node.\n"); // �ܺγ�� ����
            newNode->left = makeExternalNode(depth + 1);
        }
    }
    else {    // �ܺγ�带 ���� ��
        if (depth >= 2) {   // ��ȿ�� ������ ��
            newNode->left = makeExternalNode(depth + 1);    // �ܺγ�� ����
        }
        else {    // ��ȿ���� ���� ������ ��
            printf("invalid depth. make internal node.\n"); // ���γ�� ����
            newNode->left = makeInternalNode(depth + 1);
        }

    }

    printf("Question if no to '%s'? ", question);   // ������ �ڽĿ� ���� ����
    gets(child);

    if (strcmp(child, "yes") == 0) {    // ���γ�� ����
        if (depth < 4) {    // ��ȿ�� ������ ��
            newNode->right = makeInternalNode(depth + 1);   // ���γ�� ����
        }
        else {    // ��ȿ���� ���� ������ ��
            printf("invalid depth. make external node.\n"); // �ܺγ�� ����
            newNode->right = makeExternalNode(depth + 1);
        }

    }
    else {    // �ܺγ�带 ���� ��
        if (depth >= 2) {   // ��ȿ�� ������ ��
            newNode->right = makeExternalNode(depth + 1);   // �ܺγ�� ����
        }
        else {    // ��ȿ���� ���� ������ ��
            printf("invalid depth. make internal node.\n"); // ���γ�� ����
            newNode->right = makeInternalNode(depth + 1);
        }

    }

    return newNode;
}

void runDecisionTree(Node* tree) {
    printf("***Please answer questions\n");
    processNode(tree);
}

void processNode(Node* tree) {
    printf("%s ", tree->question);

    if (isInternal(tree)) { // ���γ���� ��
        char answer[10];    // ��� �Է¹ޱ�
        gets(answer);
        if (strcmp(answer, "yes") == 0) {   // ����� yes�̸� ���� �ڽĳ�� ����
            processNode(tree->left);
        }
        else {    // ����� no�̸� ������ �ڽĳ�� ����
            processNode(tree->right);
        }
    }

}

bool isInternal(Node* node) {   // ���γ������ �˻��ϴ� �Լ�
    if (node->left != NULL && node->right != NULL)
        return true;

    return false;
}