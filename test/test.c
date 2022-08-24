#include "test.h"

void myprint(int a) {
    printf("%d ", a);
}
void testSqList() {
    SqList* List1 = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(List1);
    SqList* List2 = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(List2);
    for (int i = 0; i < 5; i++) {
        ListInsert_Sq(List1, 1, 10 - 2 * i);
        ListInsert_Sq(List2, i + 1, 3 * i - 4);
    }
    int num = 0;
    ListDelete_Sq(List2, 1, &num);
    printf("%d\n", num);
    GetElem_Sq(List1, 3, &num);
    printf("%d\n", num);
    NextElem_Sq(List1, num, &num);
    printf("%d\n", num);
    SqList* List3 = (SqList*)malloc(sizeof(SqList));
    ListTraverse_Sq(List1, myprint);
    ListTraverse_Sq(List2, myprint);
    MergeAscendingList_Sq(List1, List2, List3);
    ListTraverse_Sq(List3, myprint);
    ClearList_Sq(List3);
    DestroyList_Sq(List1);
    DestroyList_Sq(List2);
    DestroyList_Sq(List3);
}

void difference_SL(SLinkList space) {
    int Head;
    InitList_SL(space, &Head);
    int p = Head;
    int m = 4, n = 4, temp = 0;
    // scanf("%d%d", &m, &n);
    int input1[4] = {1, 3, 4, 2};
    int input2[4] = {2, 3, 3, 5};
    // 输入A集合中的m个数, 加入静态链表
    for (int i = 0; i < m; i++) {
        // scanf("%d", &temp);
        temp = input1[i];
        ListInsert_SL(space, Head, 1, temp);
    }
    // 输入B集合中的n个数, 若A中已有则删, 没有则插入
    int find = 0;
    for (int i = 0; i < n; i++) {
        // scanf("%d", &temp);
        temp = input2[i];
        find = LocateElem_SL(space, Head, temp, Equal);
        if (find) {
            ListDelete_SL(space, Head, find, &temp);
        }
        else ListInsert_SL(space, Head, 2, temp);
    }
    ListTraverse_SL(space, Head, myprint);
}
void testSLinkList() {
    component *space = (component*)malloc(sizeof(SLinkList));
    difference_SL(space);
    free(space);
}

void testPolynomial() {
    Polynomial* P1 = NULL, *P2 = NULL;
    Data d1[4] = {{1, 2}, {3, -4}, {5, 2}, {7, 7}};
    Data d2[7] = {{1, -3}, {3, 4}, {4, -2}, {5, -2}, {6, 3}, {7, -2}, {9, 3}};
    CreatPolyn(&P1, 4, d1);
    CreatPolyn(&P2, 7, d2);
    AddPolyn(P1, P2);
    PrintPolyn(P1);
}
