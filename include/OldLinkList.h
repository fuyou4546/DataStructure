#include <stdio.h>
#include <stdlib.h>
#include "Others.h"

typedef struct OldLNode {
    int data;
    struct OldLNode* next;
}OldLNode, *OldLinkList;

void CreateList_Link(OldLinkList, int);
void DestroyList_Link(OldLinkList);
Status GetElem_Link(OldLinkList, int, int*);
int LocateElem_Link(OldLinkList, int, int (*)(int, int));
Status PriorElem_Link(OldLinkList, int, int*);
Status NextElem_Link(OldLinkList, int, int*);
Status ListInsert_Link(OldLinkList, int, int);
Status ListDelete_Link(OldLinkList, int, int*);
void ListTraverse_Link(OldLinkList, void (*)(int));
void MergeAscendingList_Link(OldLinkList, OldLinkList, OldLinkList);
