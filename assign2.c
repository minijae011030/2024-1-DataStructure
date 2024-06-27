#include <stdio.h>
#include <stdlib.h>

typedef struct node {   // 유저의 이름과 쿠폰의 종류, 다음 노드의 정보를 담은 노드
    char name;
    int coupon;
    struct node* nextName;
    struct node* nextCoupon;
} node;

typedef struct couponList { // 쿠폰의 종류를 담을 구조체 배열 노드
    int coupon;
    struct node* nodeHeader;
} couponList;

typedef struct nameList {   // 유저의 이름을 담을 구조체 배열 노드
    char name;
    struct node* nodeHeader;
} nameList;

typedef struct LinkedList { // 다중연결리스트
    struct couponList* cList;
    struct nameList* nList;
} LinkedList;

node* makeNode();   // 노드 생성
LinkedList initLinkedList();    // 다중연결리스트 초기화

void addShare(LinkedList* L, char name, int coupon);    // 이름과 쿠폰 종류를 입력받아 리스트에 추가하는 함수
void removeShare(LinkedList* L, char name, int coupon); // 이름과 쿠폰 종류를 입력받아 리스트에서 삭제하는 함수
void searchUser(LinkedList* L, int coupon); // 특정 쿠폰 종류를 입력받아 해당 쿠폰 종류를 가진 사용자를 출력하는 함수
void searchCoupon(LinkedList* L, char name);    // 특정 사용자 이름을 입력받아 해당 유저가 가진 쿠폰의 종류를 출력하는 함수

void freeLinkedList(LinkedList* L); // 동적할당
int main() {
    char cmd, user;
    int coupon;

    LinkedList L = initLinkedList();    // 다중연결리스트 초기화

    while (1) {
        scanf("%c", &cmd);
        getchar();

        switch (cmd) {
        case 'a':
            // addShare: 가입자가 쿠폰 구매
            scanf("%d %c", &coupon, &user);
            getchar();
            addShare(&L, user, coupon);

            break;
        case 'r':
            // removeShare: 가입자가 쿠폰 구매 취소하거나 사용 완료
            scanf("%d %c", &coupon, &user);
            getchar();
            removeShare(&L, user, coupon);
            break;
        case 'e':
            // 특정 가입자가 보유한 쿠폰 열람
            scanf("%c", &user);
            getchar();
            searchCoupon(&L, user);
            break;
        case 'g':
            // 특정 쿠폰을 보유한 가입자 열람
            scanf("%d", &coupon);
            getchar();
            searchUser(&L, coupon);
            break;

        case 'q':
            // 동적할당 해제 후 프로그램 종료
            freeLinkedList(&L);
            return 0;

        }
    }

}

node* makeNode() {  // 노드 생성
    node* newNode = (node*)malloc(sizeof(node));
    newNode->nextName = NULL;
    newNode->nextCoupon = NULL;

    return newNode;
};

LinkedList initLinkedList() {   // 다중연결리스트 초기화
    LinkedList L;
    L.cList = (couponList*)malloc(sizeof(couponList) * 4);  // 쿠폰 구조체 배열 생성
    L.nList = (nameList*)malloc(sizeof(nameList) * 5);  // 사용자 구조체 배열 생성

    for (int i = 0; i < 4; i++) {   // 쿠폰 리스트 초기화
        L.cList[i].coupon = i + 1;
        L.cList[i].nodeHeader = makeNode();
    }

    for (int i = 0; i < 5; i++) {   // 가입자 리스트 초기화
        L.nList[i].name = i + 65;
        L.nList[i].nodeHeader = makeNode();
    }

    return L;
}

void addShare(LinkedList* L, char name, int coupon) {   // 이름과 쿠폰 종류를 입력받아 리스트에 추가하는 함수
    if (coupon <= 0 || coupon >= 5) {   // 유효하지 않은 쿠폰
        printf("invalid coupon\n");
        return;
    }

    if (name <= 64 || name >= 70) { // 유효하지 않은 유저
        printf("invalid user\n");
        return;
    }

    int nameIdx = name - 65;    // 이름 구조체 배열에서 해당하는 유저의 인덱스
    int couponIdx = coupon - 1; // 쿠폰 구조체 배열에서 해당하는 쿠폰의 인덱스

    node* newNode = makeNode(); // 노드 생성 후 값 할당
    newNode->coupon = coupon;
    newNode->name = name;

    node* couponP = L->nList[nameIdx].nodeHeader;   // 이름 구조체 배열에서 해당하는 유저를 찾아 노드의 헤더로 이동
    while (couponP->nextCoupon != NULL && couponP->nextCoupon->coupon < coupon) {   // 특정한 위치로 이동
        couponP = couponP->nextCoupon;
    }

    newNode->nextCoupon = couponP->nextCoupon;  // 노드 연결
    couponP->nextCoupon = newNode;

    node* nameP = L->cList[couponIdx].nodeHeader;   // 쿠폰 구조체 배열에서 해당하는 쿠폰을 찾아 노드의 헤더로 이동
    while (nameP->nextName != NULL && nameP->nextName->name < name) {   // 특정한 위치로 이동
        nameP = nameP->nextName;
    }

    newNode->nextName = nameP->nextName;    // 노드 연결
    nameP->nextName = newNode;


    printf("OK\n");

    return;
}

void removeShare(LinkedList* L, char name, int coupon) {    // 이름과 쿠폰 종류를 입력받아 리스트에서 삭제하는 함수
    int nameIdx = name - 65;    // 이름 구조체 배열에서 해당하는 유저의 인덱스
    int couponIdx = coupon - 1; // 쿠폰 구조체 배열에서 해당하는 쿠폰의 인덱스

    node* currentCoupon = L->nList[nameIdx].nodeHeader->nextCoupon; // 현재 노드를 저장
    node* prevCoupon = L->nList[nameIdx].nodeHeader;    // 이전 노드 저장

    while (currentCoupon != NULL) { // 현재 쿠폰이 null이 아닐 때까지
        if (currentCoupon->coupon == coupon) {  // 현재 노드의 쿠폰 명이 찾는 쿠폰 명과 일치할 시
            prevCoupon->nextCoupon = currentCoupon->nextCoupon; // 연결 끊기
            break;
        }

        // 노드 이동
        prevCoupon = currentCoupon;
        currentCoupon = currentCoupon->nextCoupon;
    }

    node* currentName = L->cList[couponIdx].nodeHeader->nextName;   // 현재 노드를 저장
    node* prevName = L->cList[couponIdx].nodeHeader;    // 이전 노드 저장

    while (currentName != NULL) {   // 현재 유저가 null이 아닐 때까지
        if (currentName->name == name) {    // 현재 노드의 유저 며이 찾는 유저 명과 일치할 시
            prevName->nextName = currentName->nextName; // 연결 끊기
            free(currentName);  // 노드 메모리 해제
            printf("OK\n");
            return;
        }

        // 노드 이동
        prevName = currentName;
        currentName = currentName->nextName;
    }

    printf("Not found\n");  // 해당하는 노드를 찾지 못했을 때

    return;
}


void searchUser(LinkedList* L, int coupon) {    // 특정 쿠폰 종류를 입력받아 해당 쿠폰 종류를 가진 사용자를 출력하는 함수
    int couponIdx = coupon - 1; // 쿠폰 구조체 배열에서 해당하는 쿠폰의 인덱스
    int count = 0;

    node* nameP = L->cList[couponIdx].nodeHeader;   // 해당하는 쿠폰을 가진 유저 리스트의 헤더

    while (nameP->nextName != NULL) {   // 다음 노드가 null이 아닐 때까지
        nameP = nameP->nextName;    // 노드 이동
        printf("%c ", nameP->name); // 정보 출력
        count++;
    }

    if (count == 0) printf("%d", count);    // 출력된 유저가 없을 시 0 출력
    printf("\n");

    return;
}

void searchCoupon(LinkedList* L, char name) {   // 특정 사용자 이름을 입력받아 해당 유저가 가진 쿠폰의 종류를 출력하는 함수
    int nameIdx = name - 65;    // 이름 구조체 배열에서 해당하는 유저의 인덱스
    int count = 0;

    node* couponP = L->nList[nameIdx].nodeHeader;   // 해당하는 유저가 가진 쿠폰 리스트의 헤더

    while (couponP->nextCoupon != NULL) {   // 다음 노드가 null이 아닐 때까지
        couponP = couponP->nextCoupon;  // 노드 이동
        printf("%d ", couponP->coupon); // 정보 출력
        count++;
    }

    if (count == 0) printf("%d", count);    // 출력된 쿠폰이 없을 시 0 출력
    printf("\n");

    return;
}

void freeLinkedList(LinkedList* L) {    // 동적할당
    for (int i = 0; i < 5; i++) {   // 쿠폰 구조체 배열 순회
        node* currentnNode = L->cList[i].nodeHeader;    // 해당 쿠폰의 유저 리스트의 헤더

        while (currentnNode != NULL) {  // 다음 노드가 null이 아닐 때까지
            node* tmp = currentnNode;
            currentnNode = currentnNode->nextCoupon;
            free(tmp);  // 노드 메모리 해제
        }
    }

    free(L->cList); // 쿠폰 구조체 배열 동적할당
    free(L->nList); // 유저 구조체 배열 동적할당

    free(L);    // 다중연결리스트 동적할당
}