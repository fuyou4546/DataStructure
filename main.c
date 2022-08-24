#include "./test/test.h"
#include "./include/kmp.h"
#define min(A, B) ({ typeof(A) __a = (A); typeof(B) __b = (B); __a < __b ? __a : __b; })

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

typedef struct LNode2 {
    int data;
    struct LNode2* next;
} Link2, *t;

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

int main() {
    // testSLinkList();
    // testPolynomial();
    // Link2 l0 = {6, NULL};
    // Link2 l1 = {5, NULL};
    // Link2 l2 = {4, &l1};
    // Link2 l3 = {3, &l2};
    // Link2 l4 = {2, &l3};
    // Link2 h = {-1, &l4};
    // Link2* l = &h;
    // char* s = "abaaabaaababaabaaabababaababacabacaababa";
    // char* p = "ababa";
    // int res = getIndex(s, p);
    // int a = 0, b[10] = {0};
    BiNode node10 = {10, NULL, NULL, 0, 0}, node9 = {-8, NULL, NULL, 0, 0}, node8 = {8, NULL, &node10, 0, 0};
    BiNode node7 = {7, NULL, &node9, 0, 0}, node6 = {6, &node8, NULL, 0, 0}, node5 = {5, &node6, &node7, 0, 0};
    BiNode node4 = {4, NULL, NULL, 0, 0}, node3 = {3, NULL, NULL, 0, 0}, node2 = {2, &node4, &node5, 0, 0};
    BiNode node1 = {1, &node2, &node3, 0, 0};
    BiTree root = &node1;
    int in[10] = {1,2,3,4,5,6,7,8,9,10};
    int degree[10] = {2,1,3,1,2,0,0,0,0,0};
    int** p = getDataWay(root, 7);
    for (int i = 1; i <= p[0][0]; i++) {
        for (int j = 1; j <= p[i][0]; j++) {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}
