#include <stdio.h>
#include <stdlib.h>
#include "../include/Structures.h"
#include "bigNumOperation.c"
#include "eightPuzzle.c"
#include "allOutQueueSeq.c"

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

typedef struct LNode2 {
    int data;
    struct LNode2* next;
} Link2, *t;

int fab(int k, int m) {
    int* dp = (int*)calloc(m + 1, sizeof(int));
    dp[k] = dp[k - 1] = 1;
    for (int i = k + 1; i <= m; i++) {
        dp[i] = (dp[i - 1] << 1) - dp[i - k - 1];
    }
    return dp[m];
}
int test() {
    int* a = malloc(15 * 4);
    a[0] = 1;
    int k = 1, n = 15, arrsize = 15;
    int max = INT_MAX, b = 1;
    while (k <= n - 1) {
        if (k >= arrsize) return -1;
        b *= k;
        max >>= 1;
        if (b > max) return -2;
        a[k] = (k*a[k - 1]) << 1;
        k++;
    }
    printf("%d", a[10]);
    free(a);
    return 1;
}
int getM_sameLen(int* a, int* b, int len) {
    int l1 = 0, l2 = 0, r1 = 7, r2 = 7, m1, m2, k = len;
    while (k > 1) {
        m1 = (l1 + r1) >> 1;
        m2 = (l2 + r2) >> 1;
        if (a[m1] == b[m2]) {
            return a[m1];
        }
        if (a[m1] < b[m2]) {
            r2 = m2;
            if (k & 1) l1 = m1;
            else l1 = m1 + 1;
        }
        else {
            r1 = m1;
            if (k & 1) l2 = m2;
            else l2 = m2 + 1;
        }
        k = (k + 1) >> 1;
    }
    return a[l1] < b[l2] ? a[l1] : b[l2];
}
int getM(int* a, int* b, int len1, int len2) {
    int l1 = 0, l2 = 0, k = (len1 + len2 + 1) / 2;
    int cur1, cur2, half = 0;
    while (1) {
        if (l1 == len1) return b[l2 + k - 1];
        if (l2 == len2) return a[l1 + k - 1];
        if (k == 1) return min(a[l1], b[l2]);
        half = k >> 1;
        cur1 = min(l1 + half, len1) - 1;
        cur2 = min(l2 + half, len2) - 1;
        if (a[cur1] < b[cur2]) {
            k -= cur1 - l1 + 1;
            l1 = cur1 + 1;
        }
        else {
            k -= cur2 - l2 + 1;
            l2 = cur2 + 1;
        }
    }
    return -1;
}

void Del_x(t* L, int x) {
    if (!(*L)) return;
    if ((*L)->data == x) {
        Link2* p = *L;
        *L = (*L)->next;
        free(p);
        Del_x(L, x);
    }
    else Del_x(&((*L)->next), x);
}
void trans(Link2* h) {
    Link2* p = h->next, *q = h->next, *r;
    while (q && q->next) {
        p = p->next;
        q = q->next->next;
    }
    q = p->next;
    p->next = NULL;
    p = q->next;
    q->next = NULL;
    while (p) {
        r = p->next;
        p->next = q;
        q = p;
        p = r;
    }
    p = h->next;
    while (q) {
        r = q->next;
        q->next = p->next;
        p->next = q;
        p = q->next;
        q = r;
    }
    
}

void DS21(BiTree T, int* dst, int index) {
    if (!T) return;
    dst[index] = T->data;
    DS21(T->lchild, dst, index * 2);
    DS21(T->rchild, dst, index * 2 + 1);
}

void testDS21() {
    int* dst = calloc(101, sizeof(int));
    BiNode node10 = {10, NULL, NULL, 0, 0}, node9 = {9, NULL, NULL, 0, 0}, node8 = {8, NULL, &node10, 0, 0};
    BiNode node7 = {7, NULL, &node9, 0, 0}, node6 = {6, &node8, NULL, 0, 0}, node5 = {5, &node6, &node7, 0, 0};
    BiNode node4 = {4, NULL, NULL, 0, 0}, node3 = {3, NULL, NULL, 0, 0}, node2 = {2, &node4, &node5, 0, 0};
    BiNode node1 = {1, &node2, &node3, 0, 0};
    BiTree root = &node1;
    // DS21(root, dst, 1);
    // for (int i = 1; i <= 100; i++) {
    //     printf("%d ", dst[i]);
    //     if (!(i % 10)) printf("\n");
    // }
    printf("%d", getWPL(root));
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

int s1[100], s2[100];
int top1 = -1, top2 = -1;
void stackQueue(int mode, int x) {
    if (!mode) {
        if (top1 != 99) {
            s1[++top1] = x;
            printf("入队成功\n");
        }
        else {
            if (top2 == -1) {
                while (top1 != -1) {
                    s2[++top2] = s1[top1--];
                }
                s1[++top1] = x;
                printf("入队成功\n");
            }
            else printf("队列满\n");
        }
    }
    else {
        if (top2 != -1) {
            printf("%d出队\n", s2[top2--]);
        }
        else {
            if (top1 == 99) {
                while (top2 != 99) {
                    s2[++top2] = s1[top1--];
                }
                printf("%d出队\n", s2[top2--]);
            }
            else printf("队列空\n");
        }
    }
}

Link* front = NULL, *rear = NULL;
void linkCircularQueue(int mode, int x) {
    if (!mode) {
        front = rear = malloc(sizeof(Link));
        rear->next = front;
    }
    if (mode == 1) {
        if (rear->next == front) {
            Link* node = malloc(sizeof(Link));
            node->next = front;
            rear->next = node;
        }
        rear->key = x;
        rear = rear->next;
    }
    if (mode == 2) {
        if (front == rear) {
            printf("队列空\n");
        }
        else {
            front = front->next;
        }
    }
}

void testKMP() {
    char* pat = "abcabbcaa";
    int len = strlen(pat);
    int* next = malloc(len * sizeof(int));
    getNext(pat, next);
    for (int i = 0; i < len; i++) {
        printf("%d ", next[i]);
    }
}
void testAllOut() {
    int L[] = {1, 2, 3, 4};
    allOneSideOutSeq(L, sizeof(L) / sizeof(int));
}

void testC() {
    union {
        int a;
        char ch[2];
    } u;
    u.ch[0] = 1;
    u.ch[1] = 2;
    printf("%x", u);
}

void testBigNum() {
    char* num1 = "999999975463";
    char* num2 = "236451879";
    char* sum = bigAdd(num1, num2);
    printf("%20s\n + %17s\n = %17s", num1, num2, sum);
}

void solution() {
    // printf("%d", C21(1, 29, 2));
    // testFILE();
    // testChangeLink();
    // testKMP();
    // testDS21();
    // testAllOut();
    testBigNum();
}
