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
    Node* tree = buildDecisionTree();  // 트리 생성

    for (int i = 0; i < 3; i++) {   // 세 번 프로그램 실행
        printf("***Please answer questions\n");
        runDecisionTree(tree);
    }

    return 0;
}

Node* buildDecisionTree() {
    printf("*** Let's build a dichotomous QA system\n");
    Node* root = makeInternalNode(0);   // 깊이를 0으로 설정

    return root;
}

Node* makeExternalNode() {  // 외부노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));


    printf("Enter decision: "); // 결정 입력받기
    gets(newNode->question);
    newNode->left = NULL;   // 외부노드로 설정
    newNode->right = NULL;

    return newNode;
}

Node* makeInternalNode(int depth) { // 내부노드 생성
    Node* newNode = (Node*)malloc(sizeof(Node));

    char question[256]; // 질문 입력받기
    printf("Enter question: ");
    gets(question);
    strcpy(newNode->question, question);


    printf("Question if yes to '%s'? ", question);  // 왼쪽 자식에 대한 설정
    char child[10];
    gets(child);

    if (strcmp(child, "yes") == 0) {    // 내부노드를 만들 떄
        if (depth < 4) {    // 유효한 깊이일 떄
            newNode->left = makeInternalNode(depth + 1);    // 내부노드 생성
        }
        else {    // 유효하지 않은 깊이일 때
            printf("invalid depth. make external node.\n"); // 외부노드 생성
            newNode->left = makeExternalNode(depth + 1);
        }
    }
    else {    // 외부노드를 만들 때
        if (depth >= 2) {   // 유효한 깊이일 때
            newNode->left = makeExternalNode(depth + 1);    // 외부노드 생성
        }
        else {    // 유효하지 않은 깊이일 때
            printf("invalid depth. make internal node.\n"); // 내부노드 생성
            newNode->left = makeInternalNode(depth + 1);
        }

    }

    printf("Question if no to '%s'? ", question);   // 오른쪽 자식에 대한 설정
    gets(child);

    if (strcmp(child, "yes") == 0) {    // 내부노드 생성
        if (depth < 4) {    // 유효한 깊이일 떄
            newNode->right = makeInternalNode(depth + 1);   // 내부노드 생성
        }
        else {    // 유효하지 않은 깊이일 때
            printf("invalid depth. make external node.\n"); // 외부노드 생성
            newNode->right = makeExternalNode(depth + 1);
        }

    }
    else {    // 외부노드를 만들 때
        if (depth >= 2) {   // 유효한 깊이일 때
            newNode->right = makeExternalNode(depth + 1);   // 외부노드 생성
        }
        else {    // 유효하지 않은 깊이일 때
            printf("invalid depth. make internal node.\n"); // 내부노드 생성
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

    if (isInternal(tree)) { // 내부노드일 때
        char answer[10];    // 대답 입력받기
        gets(answer);
        if (strcmp(answer, "yes") == 0) {   // 대답이 yes이면 왼쪽 자식노드 진출
            processNode(tree->left);
        }
        else {    // 대압이 no이면 오른쪽 자식노드 진출
            processNode(tree->right);
        }
    }

}

bool isInternal(Node* node) {   // 내부노드인지 검사하는 함수
    if (node->left != NULL && node->right != NULL)
        return true;

    return false;
}