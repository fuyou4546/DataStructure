#include <stdio.h>
#include <stdlib.h>
#include "Others.h"

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef struct {
    int* elem;
    int length;
    int listsize;
} SqList;

Status InitList_Sq(SqList*);
void DestroyList_Sq(SqList*);
Status ClearList_Sq(SqList*);
Bool ListEmpty_Sq(SqList*);
int ListLength_Sq(SqList*);
Status GetElem_Sq(SqList*, int, int*);
int LocateElem_Sq(SqList*, int, int (*)(int, int));
Status PriorElem_Sq(SqList*, int, int*);
Status NextElem_Sq(SqList*, int, int*);
Status ListInsert_Sq(SqList*, int, int);
Status ListDelete_Sq(SqList*, int, int*);
void ListTraverse_Sq(SqList*, void (*)(int));
void MergeAscendingList_Sq(SqList*, SqList*, SqList*);
