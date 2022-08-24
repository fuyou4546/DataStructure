#include "../include/SLinkList.h"

void InitSpace_SL(SLinkList space) {
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        space[i].cur = i + 1;
    }
    space[MAX_SIZE - 1].cur = 0;
}

// space[0].cur指向备用链表
int Malloc_SL(SLinkList space) {
    int i = space[0].cur;
    if (i) space[0].cur = space[i].cur;
    return i;
}

void Free_SL(SLinkList space, int i) {
    space[i].cur = space[0].cur;
    space[0].cur = i;
}

void InitList_SL(SLinkList space, int* Head) {
    InitSpace_SL(space);
    *Head = Malloc_SL(space);
    space[*Head].cur = 0;
}

void ClearList_SL(SLinkList space, int Head) {
    int p = space[Head].cur;
    while (p) {
        space[Head].cur = space[p].cur;
        Free_SL(space, p);
        p = space[Head].cur;
    }
}

void DestroyList_SL(SLinkList space, int* Head) {
    ClearList_SL(space, *Head);
    Free_SL(space, *Head);
    *Head = 0;
}

Status GetElem_SL(SLinkList space, int Head, int i, int* e) {
    if (i < 1 || i > MAX_SIZE - 1) return ERROR;
    int count = 1, p = space[Head].cur;
    while (p) {
        if (count == i) {
            *e = space[p].data;
            return OK;
        }
        p = space[p].cur;
    }
    return ERROR;
}

int LocateElem_SL(SLinkList space, int Head, int e, Status (*compare)(int, int)) {
    int i = space[Head].cur, count = 1;
    while (i) {
        if (compare(space[i].data, e)) {
            return count;
        }
        i = space[i].cur;
        count++;
    }
    // 没找到时会返回0
    return 0;
}

Status ListInsert_SL(SLinkList space, int Head, int i, int e) {
    if (i < 1 || i > SIZE_MAX - 2) return ERROR;
    int count = 1, p = Head;
    while (p && count++ < i) {
        p = space[p].cur;
    }
    if (!p) return ERROR;
    int k = Malloc_SL(space);
    if (!k) return ERROR;
    space[k].data = e;
    space[k].cur = space[p].cur;
    space[p].cur = k;
    return OK;
}

Status ListDelete_SL(SLinkList space, int Head, int i, int* e) {
    if (i < 1 || i > SIZE_MAX - 1) return ERROR;
    int count = 1, p = Head;
    while (p && count++ < i) {
        p = space[p].cur;
    }
    if (!p) return ERROR;
    int k = space[p].cur;
    if (!k) return ERROR;
    *e = space[k].data;
    space[p].cur = space[k].cur;
    Free_SL(space, k);
    return OK;
}

void ListTraverse_SL(SLinkList space, int Head, void (*visit)(int)) {
    int p = space[Head].cur;
    while (p) {
        visit(space[p].data);
        p = space[p].cur;
    }
}
