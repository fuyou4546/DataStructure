#include <stdio.h>
#include <stdlib.h>
#include "Others.h"

#define MAX_SIZE 10

typedef struct {
    int data;
    int cur;
}component, SLinkList[MAX_SIZE];

void InitSpace_SL(SLinkList);
Status GetElem_SL(SLinkList, int, int, int*);
int Malloc_SL(SLinkList);
void Free_SL(SLinkList, int);
void InitList_SL(SLinkList, int*);
void ClearList_SL(SLinkList, int);
void DestroyList_SL(SLinkList, int*);
int LocateElem_SL(SLinkList, int, int, int (*)(int, int));
Status ListInsert_SL(SLinkList, int, int, int);
Status ListDelete_SL(SLinkList, int, int, int*);
void ListTraverse_SL(SLinkList, int, void (*)(int));
