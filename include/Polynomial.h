#include <stdio.h>
#include <stdlib.h>
#include "Others.h"
#include "LinkList.h"

typedef struct PolynNode {
    float coef;
    int expn;
    struct PolynNode* next;
}PolynNode;

typedef LinkList Polynomial;

void CreatPolyn(Polynomial** P, int n, Data* d);
void DestroyPolyn(Polynomial** P);
int PolynLength(Polynomial* P);
void AddPolyn(Polynomial* P1, Polynomial* P2);
void SubtractPolyn(Polynomial* P1, Polynomial* P2);
void MutiplyPolyn(Polynomial* P1, Polynomial* P2);
void PrintPolyn(Polynomial* P);
