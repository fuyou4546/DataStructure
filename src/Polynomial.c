#include "../include/Polynomial.h"

void CreatPolyn(Polynomial** P, int n, Data* d) {
    InitList(P);
    Link* q = (*P)->head; 
    for (int i = 0; i < n; i++) {
        Link* s = NULL;
        if (!(LocateElem(*P, &d[i], Equal_Data1))) {
            MakeNode(&s, &d[i]);
            InsAfter(*P, &q, s);
        }
    }
    (*P)->tail = q;
}

void DestroyPolyn(Polynomial** P) {
    DestroyList(P);
}

int PolynLength(Polynomial* P) {
    return P->len;
}

void AddPolyn(Polynomial* P1, Polynomial* P2) {
    Link* p1 = GetHead(P1), *p2 = GetHead(P2);
    Link* q1 = p1->next, *q2 = p2->next;
    Data* d1 = NULL, *d2 = NULL;
    int add = 0;
    while (q1 && q2) {
        d1 = q1->data;
        d2 = q2->data;
        if (d1->x < d2->x) {
            p1 = q1;
            q1 = q1->next;
        }
        else if (d1->x == d2->x) {
            add = d1->y + d2->y;
            if (!add) {
                DelAfter(P1, p1, &q1);
                FreeNode(&q1);
            }
            else {
                Data temp = { 0 };
                temp.x = d1->x;
                temp.y = add;
                SetCurElem(q1, temp);
                p1 = q1;
            }
            DelAfter(P2, p2, &q2);
            FreeNode(&q2);
            q2 = p2->next;
            q1 = p1->next;
        }
        else {
            DelAfter(P2, p2, &q2);
            InsAfter(P1, &p1, q2);
            q2 = p2->next;
            q1 = p1->next;
        }
    }
    if (!ListEmpty(P2)) {
        Append(P1, q2);
    }
    FreeNode(&p2);
}

void SubtractPolyn(Polynomial* P1, Polynomial* P2) {
    
}

void MutiplyPolyn(Polynomial* P1, Polynomial* P2) {

}

void PrintPolyn(Polynomial* P) {
    Link* q = P->head->next;
    int expn = 0, coef = 0;
    while (q) {
        expn = q->data->x;
        coef = q->data->y;
        if (coef > 0 && q != P->head) {
            printf("+");
        }
        printf("%dx^%d", coef, expn);
        q = q->next;
    }
    printf("\n");
}
