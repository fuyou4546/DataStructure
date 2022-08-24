#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "Others.h"

typedef struct LNode {
    Data* data;
    struct LNode *next;
}Link;

typedef struct {
    Link* head, *tail;
    int len;
}LinkList;

Status MakeNode(Link** p, Data* d);
void FreeNode(Link** p);
Status InitList(LinkList** L);
Status DestroyList(LinkList** L);
Status ClearList(LinkList* L);
Status InsFirst(Link* h, Link* s);
Status DelFirst(Link* h, Link** q);
Status Append(LinkList* L, Link* s);
Status Remove(LinkList* L, Link** q);
Status InsBefore(LinkList* L, Link** p, Link* s);
Status InsAfter(LinkList* L, Link** p, Link* s);
Status DelAfter(LinkList* L, Link* p, Link** s);
Status SetCurElem(Link* p, Data d);
Data* GetCurElem(Link* p);
Bool ListEmpty(LinkList* L);
int ListLength(LinkList* L);
Link* GetHead(LinkList* L);
Link* GetLast(LinkList* L);
Link* PriorLink(LinkList* L, Link* p);
Link* NextLink(LinkList* L, Link* p);
Status LocateLink(LinkList* L, int i, Link** p);
Link* LocateElem(LinkList* L, Data* d, Status (*compare)(Data*, Data*));
Status ListInsert(LinkList* L, int i, Data* d);
Status ListDelete(LinkList* L, int i, Data** d);
Status ListTraverse(LinkList* L, void (*visit)(Data*));

#endif _LINKLIST_H_
