#include "../include/SqList.h"

Status InitList_Sq(SqList* L) {
    if (!L) L = (SqList*)malloc(sizeof(SqList));
    if (!L) exit(OVERFLOW);
    L->elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

void DestroyList_Sq(SqList* L) {
    free(L);
}

Status ClearList_Sq(SqList* L) {
    free(L->elem);
    return InitList_Sq(L);
}

Bool ListEmpty_Sq(SqList* L) {
    return L->length > 0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList* L) {
    return L->length;
}

Status GetElem_Sq(SqList* L, int i, int* e) {
    int len = L->length;
    if (i < len || i > len) return ERROR;
    *e = L->elem[i - 1];
    return OK;
}

int LocateElem_Sq(SqList* L, int e, int (*compare)(int a, int b)) {
    int len = L->length;
    for (int i = 0; i < len; i++) {
        if (compare(e, L->elem[i])) return i + 1;
    }
    return 0;
}

Status PriorElem_Sq(SqList* L, int cur_e, int* pre_e) {
    int index = LocateElem_Sq(L, cur_e, Equal);
    if (index > 1) {
        *pre_e = L->elem[index - 1];
        return OK;
    }
    return ERROR;
}

Status NextElem_Sq(SqList* L, int cur_e, int* next_e) {
    int index = LocateElem_Sq(L, cur_e, Equal);
    if (index && index < L->length) {
        *next_e = L->elem[index + 1];
        return OK;
    }
    return ERROR;
}

Status ListInsert_Sq(SqList* L, int i, int e) {
    // 先判断i, 再看是否溢出, 再插入并使长度加1
    int len = L->length;
    if (i < 1 || i > len + 1) return ERROR;
    if (L->length >= L->listsize) {
        int* newbase = (int*)realloc(L->elem, 
            (L->listsize + LIST_INCREMENT) * sizeof(int));
        if (!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LIST_INCREMENT;
    }
    int *p = L->elem + i - 1, *q = L->elem + len;
    while (q > p) {
        *q= *(q - 1);
        q--;
    }
    *p = e;
    L->length++;
    return OK;
}

Status ListDelete_Sq(SqList* L, int i, int* e) {
    int len = L->length;
    if (i < 1 || i > len) return ERROR;
    int *p = L->elem + i - 1, *q = L->elem + len;
    *e = *p;
    while (p < q) {
        *p = *(p + 1);
        p++;
    }
    L->length--;
    return OK;
}

void ListTraverse_Sq(SqList* L, void (*visit)(int)) {
    int *p = L->elem, *q = p + L->length;
    while (p < q) {
        visit(*p++);
    }
}

void MergeAscendingList_Sq(SqList* L1, SqList* L2, SqList* L3) {
    int len1 = L1->length, len2 = L2->length;
    int len3 = len1 + len2;
    L3->elem = (int*)malloc(len3 * sizeof(int));
    if (!L3->elem) exit(-2);
    L3->length = L3->listsize = len3;
    int* p1 = L1->elem, *p2 = L2->elem, *p3 = L3->elem;
    int* q1 = L1->elem + len1, *q2 = L2->elem + len2;
    while (p1 < q1 && p2 < q2) {
        *p3++ = *p1 < *p2 ? *p1++ : *p2++;
    }
    while (p1 < q1) *p3++ = *p1++;
    while (p2 < q2) *p3++ = *p2++;
}