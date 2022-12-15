#include <stdio.h>
#include <stdlib.h>

typedef struct queueLink {
    int key;
    struct queueLink* next;
    struct queueLink* pre;
} qlink;
typedef struct queueList {
    qlink* left;
    qlink* right;
} qlist;

qlist* initqlist() {
    return calloc(1, sizeof(qlist));
}
void pushLeft(qlist* ql, int key) {
    qlink* node = calloc(1, sizeof(qlink));
    node->key = key;
    node->next = ql->left;
    if (ql->left) {
        ql->left->pre = node;
    }
    else {
        ql->right = node;
    }
    ql->left = node;
}
void pushRight(qlist* ql, int key) {
    qlink* node = calloc(1, sizeof(qlink));
    node->key = key;
    node->pre = ql->right;
    if (ql->right) {
        ql->right->next = node;
    }
    else {
        ql->left = node;
    }
    ql->right = node;
}
int popLeft(qlist* ql) {
    if (!ql->left) return -1;
    int key = ql->left->key;
    if (ql->right == ql->left) {
        ql->right = NULL;
    }
    else {
        ql->left->next->pre = NULL;
    }
    ql->left = ql->left->next;
    return key;
}
int popRight(qlist* ql) {
    if (!ql->right) return -1;
    int key = ql->right->key;
    if (ql->left == ql->right) {
        ql->left = NULL;
    }
    else {
        ql->right->pre->next = NULL;
    }
    ql->right = ql->right->pre;
    return key;
}
extern int factorial[];
int encodeSeq(int* seq, int n) {
    int index = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (seq[j] < seq[i]) {
                index += factorial[n - 1 - i];
            }
        }
    }
    return index;
}
int isVisited(char* visited, int* seq, int n) {
    int index = encodeSeq(seq, n);
    if (!visited[index]) {
        visited[index] = 1;
        return 0;
    }
    return 1;
}
void getAllRightOutSeq(int* L, int n, int cur, qlist* ql, int* seq, int k, char* visited, int* count) {
    if (!ql->left && cur == n) {
        if (!isVisited(visited, seq, n)) {
            (*count)++;
            // for (int i = 0; i < n; i++) {
            //     printf("%d", seq[i]);
            // }
            // printf("  ");
        }
        return;
    }
    if (cur < n) {
        pushLeft(ql, L[cur]);
        getAllRightOutSeq(L, n, cur + 1, ql, seq, k, visited, count);
        popLeft(ql);
        pushRight(ql, L[cur]);
        getAllRightOutSeq(L, n, cur + 1, ql, seq, k, visited, count);
        popRight(ql);
    }
    if (ql->right) {
        seq[k] = popRight(ql);
        getAllRightOutSeq(L, n, cur, ql, seq, k + 1, visited, count);
        pushRight(ql, seq[k]);
    }
}
void allOneSideOutSeq(int* L, int n) {
    qlist* queue = initqlist();
    int* seq = malloc(n * sizeof(int));
    char* visited = calloc(factorial[n], sizeof(char));
    int count = 0;
    getAllRightOutSeq(L, n, 0, queue, seq, 0, visited, &count);
    printf("\ntotal: %d", count);
}
