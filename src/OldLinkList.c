#include "../include/OldLinkList.h"

void CreateList(OldLinkList Head, int n) {
    Head = (OldLinkList)malloc(sizeof(OldLNode));
    Head->next = NULL;
    OldLinkList p = NULL;
    for (int i = 0; i < n; i++) {
        p = (OldLinkList)malloc(sizeof(OldLNode));
        scanf("%d", &p->data);
        // 头插
        p->next = Head->next;
        Head->next = p;
    }
}

void DestroyList_Link(OldLinkList Head) {
    if (!Head) return;
    DestroyList_Link(Head->next);
    free(Head);
}

Status GetElem_Link(OldLinkList Head, int i, int* e) {
    OldLinkList p = Head->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    *e = p->data;
    return OK;
}

int LocateElem_Link(OldLinkList Head, int e, int (*compare)(int, int)) {
    OldLinkList p = Head->next;
    int count = 0;
    while (p && !compare(p->data, e)) {
        p = p->next;
        count++;
    }
    return count;
}

// 第i个位置插在前面
Status ListInsert_Link(OldLinkList Head, int i, int e) {
    OldLinkList p = Head;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j >= i) return ERROR;
    OldLinkList node = (OldLinkList)malloc(sizeof(OldLNode));
    node->data = e;
    node->next = p->next;
    p->next = node;
    return OK;
}

Status ListDelete_Link(OldLinkList Head, int i, int* e) {
    OldLinkList p = Head;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j >= i) return ERROR;
    OldLinkList temp = p->next;
    *e = temp->data;
    p->next = temp->next;
    free(temp);
    return OK;
}

void ListTraverse_Link(OldLinkList Head, void (*visit)(int)) {
    OldLinkList p = Head->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
}

void MergeAscendingList_Link(OldLinkList Head1, OldLinkList Head2, OldLinkList Head3) {
    OldLinkList p1 = Head1->next, p2 = Head2->next;
    // Head3利用Head1
    OldLinkList p3 = Head3 = Head1;
    while (p1 && p2) {
        if (p1->data < p2->data) {
            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        }
        else {
            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
        p3->next = p1 ? p1 : p2;
        free(Head2);
    }
}
