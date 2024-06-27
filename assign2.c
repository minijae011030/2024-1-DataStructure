#include <stdio.h>
#include <stdlib.h>

typedef struct node {   // ������ �̸��� ������ ����, ���� ����� ������ ���� ���
    char name;
    int coupon;
    struct node* nextName;
    struct node* nextCoupon;
} node;

typedef struct couponList { // ������ ������ ���� ����ü �迭 ���
    int coupon;
    struct node* nodeHeader;
} couponList;

typedef struct nameList {   // ������ �̸��� ���� ����ü �迭 ���
    char name;
    struct node* nodeHeader;
} nameList;

typedef struct LinkedList { // ���߿��Ḯ��Ʈ
    struct couponList* cList;
    struct nameList* nList;
} LinkedList;

node* makeNode();   // ��� ����
LinkedList initLinkedList();    // ���߿��Ḯ��Ʈ �ʱ�ȭ

void addShare(LinkedList* L, char name, int coupon);    // �̸��� ���� ������ �Է¹޾� ����Ʈ�� �߰��ϴ� �Լ�
void removeShare(LinkedList* L, char name, int coupon); // �̸��� ���� ������ �Է¹޾� ����Ʈ���� �����ϴ� �Լ�
void searchUser(LinkedList* L, int coupon); // Ư�� ���� ������ �Է¹޾� �ش� ���� ������ ���� ����ڸ� ����ϴ� �Լ�
void searchCoupon(LinkedList* L, char name);    // Ư�� ����� �̸��� �Է¹޾� �ش� ������ ���� ������ ������ ����ϴ� �Լ�

void freeLinkedList(LinkedList* L); // �����Ҵ�
int main() {
    char cmd, user;
    int coupon;

    LinkedList L = initLinkedList();    // ���߿��Ḯ��Ʈ �ʱ�ȭ

    while (1) {
        scanf("%c", &cmd);
        getchar();

        switch (cmd) {
        case 'a':
            // addShare: �����ڰ� ���� ����
            scanf("%d %c", &coupon, &user);
            getchar();
            addShare(&L, user, coupon);

            break;
        case 'r':
            // removeShare: �����ڰ� ���� ���� ����ϰų� ��� �Ϸ�
            scanf("%d %c", &coupon, &user);
            getchar();
            removeShare(&L, user, coupon);
            break;
        case 'e':
            // Ư�� �����ڰ� ������ ���� ����
            scanf("%c", &user);
            getchar();
            searchCoupon(&L, user);
            break;
        case 'g':
            // Ư�� ������ ������ ������ ����
            scanf("%d", &coupon);
            getchar();
            searchUser(&L, coupon);
            break;

        case 'q':
            // �����Ҵ� ���� �� ���α׷� ����
            freeLinkedList(&L);
            return 0;

        }
    }

}

node* makeNode() {  // ��� ����
    node* newNode = (node*)malloc(sizeof(node));
    newNode->nextName = NULL;
    newNode->nextCoupon = NULL;

    return newNode;
};

LinkedList initLinkedList() {   // ���߿��Ḯ��Ʈ �ʱ�ȭ
    LinkedList L;
    L.cList = (couponList*)malloc(sizeof(couponList) * 4);  // ���� ����ü �迭 ����
    L.nList = (nameList*)malloc(sizeof(nameList) * 5);  // ����� ����ü �迭 ����

    for (int i = 0; i < 4; i++) {   // ���� ����Ʈ �ʱ�ȭ
        L.cList[i].coupon = i + 1;
        L.cList[i].nodeHeader = makeNode();
    }

    for (int i = 0; i < 5; i++) {   // ������ ����Ʈ �ʱ�ȭ
        L.nList[i].name = i + 65;
        L.nList[i].nodeHeader = makeNode();
    }

    return L;
}

void addShare(LinkedList* L, char name, int coupon) {   // �̸��� ���� ������ �Է¹޾� ����Ʈ�� �߰��ϴ� �Լ�
    if (coupon <= 0 || coupon >= 5) {   // ��ȿ���� ���� ����
        printf("invalid coupon\n");
        return;
    }

    if (name <= 64 || name >= 70) { // ��ȿ���� ���� ����
        printf("invalid user\n");
        return;
    }

    int nameIdx = name - 65;    // �̸� ����ü �迭���� �ش��ϴ� ������ �ε���
    int couponIdx = coupon - 1; // ���� ����ü �迭���� �ش��ϴ� ������ �ε���

    node* newNode = makeNode(); // ��� ���� �� �� �Ҵ�
    newNode->coupon = coupon;
    newNode->name = name;

    node* couponP = L->nList[nameIdx].nodeHeader;   // �̸� ����ü �迭���� �ش��ϴ� ������ ã�� ����� ����� �̵�
    while (couponP->nextCoupon != NULL && couponP->nextCoupon->coupon < coupon) {   // Ư���� ��ġ�� �̵�
        couponP = couponP->nextCoupon;
    }

    newNode->nextCoupon = couponP->nextCoupon;  // ��� ����
    couponP->nextCoupon = newNode;

    node* nameP = L->cList[couponIdx].nodeHeader;   // ���� ����ü �迭���� �ش��ϴ� ������ ã�� ����� ����� �̵�
    while (nameP->nextName != NULL && nameP->nextName->name < name) {   // Ư���� ��ġ�� �̵�
        nameP = nameP->nextName;
    }

    newNode->nextName = nameP->nextName;    // ��� ����
    nameP->nextName = newNode;


    printf("OK\n");

    return;
}

void removeShare(LinkedList* L, char name, int coupon) {    // �̸��� ���� ������ �Է¹޾� ����Ʈ���� �����ϴ� �Լ�
    int nameIdx = name - 65;    // �̸� ����ü �迭���� �ش��ϴ� ������ �ε���
    int couponIdx = coupon - 1; // ���� ����ü �迭���� �ش��ϴ� ������ �ε���

    node* currentCoupon = L->nList[nameIdx].nodeHeader->nextCoupon; // ���� ��带 ����
    node* prevCoupon = L->nList[nameIdx].nodeHeader;    // ���� ��� ����

    while (currentCoupon != NULL) { // ���� ������ null�� �ƴ� ������
        if (currentCoupon->coupon == coupon) {  // ���� ����� ���� ���� ã�� ���� ��� ��ġ�� ��
            prevCoupon->nextCoupon = currentCoupon->nextCoupon; // ���� ����
            break;
        }

        // ��� �̵�
        prevCoupon = currentCoupon;
        currentCoupon = currentCoupon->nextCoupon;
    }

    node* currentName = L->cList[couponIdx].nodeHeader->nextName;   // ���� ��带 ����
    node* prevName = L->cList[couponIdx].nodeHeader;    // ���� ��� ����

    while (currentName != NULL) {   // ���� ������ null�� �ƴ� ������
        if (currentName->name == name) {    // ���� ����� ���� ���� ã�� ���� ��� ��ġ�� ��
            prevName->nextName = currentName->nextName; // ���� ����
            free(currentName);  // ��� �޸� ����
            printf("OK\n");
            return;
        }

        // ��� �̵�
        prevName = currentName;
        currentName = currentName->nextName;
    }

    printf("Not found\n");  // �ش��ϴ� ��带 ã�� ������ ��

    return;
}


void searchUser(LinkedList* L, int coupon) {    // Ư�� ���� ������ �Է¹޾� �ش� ���� ������ ���� ����ڸ� ����ϴ� �Լ�
    int couponIdx = coupon - 1; // ���� ����ü �迭���� �ش��ϴ� ������ �ε���
    int count = 0;

    node* nameP = L->cList[couponIdx].nodeHeader;   // �ش��ϴ� ������ ���� ���� ����Ʈ�� ���

    while (nameP->nextName != NULL) {   // ���� ��尡 null�� �ƴ� ������
        nameP = nameP->nextName;    // ��� �̵�
        printf("%c ", nameP->name); // ���� ���
        count++;
    }

    if (count == 0) printf("%d", count);    // ��µ� ������ ���� �� 0 ���
    printf("\n");

    return;
}

void searchCoupon(LinkedList* L, char name) {   // Ư�� ����� �̸��� �Է¹޾� �ش� ������ ���� ������ ������ ����ϴ� �Լ�
    int nameIdx = name - 65;    // �̸� ����ü �迭���� �ش��ϴ� ������ �ε���
    int count = 0;

    node* couponP = L->nList[nameIdx].nodeHeader;   // �ش��ϴ� ������ ���� ���� ����Ʈ�� ���

    while (couponP->nextCoupon != NULL) {   // ���� ��尡 null�� �ƴ� ������
        couponP = couponP->nextCoupon;  // ��� �̵�
        printf("%d ", couponP->coupon); // ���� ���
        count++;
    }

    if (count == 0) printf("%d", count);    // ��µ� ������ ���� �� 0 ���
    printf("\n");

    return;
}

void freeLinkedList(LinkedList* L) {    // �����Ҵ�
    for (int i = 0; i < 5; i++) {   // ���� ����ü �迭 ��ȸ
        node* currentnNode = L->cList[i].nodeHeader;    // �ش� ������ ���� ����Ʈ�� ���

        while (currentnNode != NULL) {  // ���� ��尡 null�� �ƴ� ������
            node* tmp = currentnNode;
            currentnNode = currentnNode->nextCoupon;
            free(tmp);  // ��� �޸� ����
        }
    }

    free(L->cList); // ���� ����ü �迭 �����Ҵ�
    free(L->nList); // ���� ����ü �迭 �����Ҵ�

    free(L);    // ���߿��Ḯ��Ʈ �����Ҵ�
}