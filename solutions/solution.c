#include <stdio.h>
#include <stdlib.h>
#include "../include/Structures.h"

typedef struct {
    char c;
    short s;
    int i;
} D;

typedef struct {
    char c;
    int i;
    short s;
} E;

void DS21(BiTree T, int* dst, int index) {
    if (!T) return;
    dst[index] = T->data;
    DS21(T->lchild, dst, index * 2);
    DS21(T->rchild, dst, index * 2 + 1);
}

void testDS21() {
    int* dst = calloc(101, sizeof(int));
    BiNode node10 = {10, NULL, NULL, 0, 0}, node9 = {-8, NULL, NULL, 0, 0}, node8 = {8, NULL, &node10, 0, 0};
    BiNode node7 = {7, NULL, &node9, 0, 0}, node6 = {6, &node8, NULL, 0, 0}, node5 = {5, &node6, &node7, 0, 0};
    BiNode node4 = {4, NULL, NULL, 0, 0}, node3 = {3, NULL, NULL, 0, 0}, node2 = {2, &node4, &node5, 0, 0};
    BiNode node1 = {1, &node2, &node3, 0, 0};
    BiTree root = &node1;
    DS21(root, dst, 1);
    for (int i = 1; i <= 100; i++) {
        printf("%d ", dst[i]);
        if (!(i % 10)) printf("\n");
    }
}

void testFILE() {
    FILE* src = fopen("solutions/solution.c", "r+");
    FILE* dst = fopen("solutions/output", "w+");
    char buffer[200], test[200];
    fread(buffer, 200, 1, src);
    fwrite(buffer, 200, 1, dst);
    fclose(src);
    fclose(dst);
}

int count_x(int num, int x) {
    int count = 0;
    while (num) {
        if (num % 10 == x) count++;
        num /= 10;
    }
    return count;
}
int C21(int begin, int end, int x) {
    int res = 0;
    for (int num = begin; num <= end; num++) {
        res += count_x(num, x);
    }
    return res;
}

int findMidNum(int* a, int* b, int k) {
    int l1 = 0, l2 = 0, r1 = k - 1, r2 = k - 1;
    int m1, m2;
    while (k > 1) {
        m1 = (l1 + r1) / 2;
        m2 = (l2 + r2) / 2;
        if (a[m1] == b[m2]) return a[m1];
        if (a[m1] > b[m2]) {
            r1 = m1;
            if (k & 1) l2 = m2;
            else l2 = m2 + 1;
        }
        else {
            r2 = m2;
            if (k & 1) l1 = m1;
            else l1 = m1 + 1;
        }
        k = (k + 1) >> 1;
    }
    return a[m1] < b[m2] ? a[m1] : b[m2];
}

void changeLink(Link* head) {
    Link* p = head, *q = head;
    while (q && q->next) {
        p = p->next;
        q = q->next->next;
    }
    q = p->next;
    p->next = NULL;
    p = NULL;
    Link* r = NULL;
    while (q) {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    q = p;
    p = head->next;
    while (q) {
        r = q->next;
        q->next = p->next;
        p->next = q;
        p = q->next;
        q = r;
    }
}

void testChangeLink() {
    Link a5 = {5, NULL, NULL};
    Link a4 = {4, NULL, NULL};
    Link a3 = {3, NULL, NULL};
    Link a2 = {2, NULL, NULL};
    Link a1 = {1, NULL, NULL};
    Link head = {0, NULL, &a1};
    Link* h = &head;
    while (h->next) {
        printf("%d ", h->next->key);
        h = h->next;
    }
    printf("\n");
    h = &head;
    changeLink(h);
    while (h->next) {
        printf("%d ", h->next->key);
        h = h->next;
    }
}

void solution() {
    // printf("%d", C21(1, 29, 2));
    // testFILE();
    testChangeLink();
}