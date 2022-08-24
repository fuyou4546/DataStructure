#include "../include/LinkList.h"

Status MakeNode(Link** p, Data* d) {
    if (*p = (Link*)malloc(sizeof(Link))) {
        (*p)->data = d;
        (*p)->next = NULL;
        return OK;
    }
    return OVERFLOW;
}

void FreeNode(Link** p) {
    free(*p);
    *p = NULL;
}

Status InitList(LinkList** L) {
    if (*L = (LinkList*)malloc(sizeof(LinkList))) {
        Link* head = NULL, *tail = NULL;
        if (MakeNode(&head, NULL) && MakeNode(&tail, NULL)) {
            (*L)->head = head;
            (*L)->tail = tail;
            (*L)->len = 0;
            return OK;
        }
    }
    return ERROR;
}

Status DestroyList(LinkList** L) {
    if (!ClearList(*L)) {
        return ERROR;
    }
    free(*L);
    *L = NULL;
    return OK;
}

Status ClearList(LinkList* L) {
    Link* head = L->head;
    if (!head) {
        return ERROR;
    }
    Link *p = NULL;
    while (head->next) {
        p = head->next;
        head->next = p->next;
        FreeNode(&p);
    }
    return OK;
}

Status InsFirst(Link* h, Link* s) {
    if (!h || !s) {
        return ERROR;
    }
    s->next = h->next;
    h->next = s;
    return OK;
}

Status DelFirst(Link* h, Link** q) {
    if (!h) {
        return ERROR;
    }
    *q = h->next;
    if (!*q) {
        return ERROR;
    }
    h->next = (*q)->next;
    return OK;
}

Status Append(LinkList* L, Link* s) {
    if (!s) return OK;
    InsFirst(L->tail, s);
    int count = 1;
    while (s->next) {
        s = s->next;
        count++;
    }
    L->tail = s;
    L->len += count;
    return OK;
}

Status Remove(LinkList* L, Link** q) {
    Link* p = L->head->next;
    while (p) {
        if (p->next == L->tail) {
            *q = L->tail;
            L->tail = p;
            p->next = NULL;
            L->len--;
            return OK;
        }
    }
    return ERROR;
}

Status InsBefore(LinkList* L, Link** p, Link* s) {
    Link* q = L->head;
    while (q) {
        if (q->next == *p) {
            if (!InsFirst(q, s)) {
                return ERROR;
            }
            *p = s;
            L->len++;
            return OK;
        }
    }
    return ERROR;
}

Status InsAfter(LinkList* L, Link** p, Link* s) {
    if (!InsFirst(*p, s)) {
        return ERROR;
    }
    if (!L->tail || L->tail == *p) {
        L->tail = s;
    }
    *p = s;
    L->len++;
    return OK; 
}

Status DelAfter(LinkList* L, Link* p, Link** s) {
    if (!DelFirst(p, s)) {
        return ERROR;
    }
    if (!L->tail) {
        L->tail = p;
    }
    L->len--;
    return OK;
}

Status SetCurElem(Link* p, Data d) {
    if (!p) {
        return ERROR;
    }
    p->data->x = d.x;
    p->data->y = d.y;
    return OK;
}

Data* GetCurElem(Link* p) {
    if (!p) {
        return NULL;
    }
    return p->data;
}

Bool ListEmpty(LinkList* L) {
    if (L->len) {
        return FALSE;
    }
    return TRUE;
}

int ListLength(LinkList* L) {
    return L->len;
}

Link* GetHead(LinkList* L) {
    return L->head;
}

Link* GetLast(LinkList* L) {
    return L->tail;
}

Link* PriorLink(LinkList* L, Link* p) {
    Link* q = L->head;
    while (q) {
        if (q->next == p) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

Link* NextLink(LinkList* L, Link* p) {
    if (!p) {
        return NULL;
    }
    return p->next;
}

Status LocateLink(LinkList* L, int i, Link** p) {
    if (i < 1 || i > L->len) {
        return ERROR;
    }
    int count = 0;
    Link* q = L->head;
    while (q && count < i) {
        q = q->next;
        count++;
    }
    if (!q) {
        *p = NULL;
        return ERROR;
    }
    *p = q;
    return OK;
}

Link* LocateElem(LinkList* L, Data* d, Status (*compare)(Data*, Data*)) {
    Link* p = L->head;
    if (!p) {
        return NULL;
    }
    p = p->next;
    while (p && p->data) {
        if (compare(p->data, d)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

Status ListInsert(LinkList* L, int i, Data* d) {
    if (i < 1 || i > L->len) {
        return ERROR;
    }
    Link* p = NULL;
    if (!LocateLink(L, i - 1, &p)) {
        return ERROR;
    }
    Link* s = NULL;
    if (!MakeNode(&s, d)) {
        return OVERFLOW;
    }
    return InsAfter(L, &p, s);
}

Status ListDelete(LinkList* L, int i, Data** d) {
    if (i < 1 || i > L->len) {
        return ERROR;
    }
    Link* p = NULL;
    if (!LocateLink(L, i - 1, &p)) {
        return ERROR;
    }
    Link* s = NULL;
    if (!DelAfter(L, p, &s)) {
        return ERROR;
    }
    *d = s->data;
    return OK;
}

Status ListTraverse(LinkList* L, void (*visit)(Data*)) {
    Link* p = L->head;
    if (!p) {
        return ERROR;
    }
    p = p->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    return OK;
}
