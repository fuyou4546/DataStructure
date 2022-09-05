#include "../include/Search.h"

int Binary_Search(SqList* L, int key) {
    int len = L->length;
    int low = 0, high = len - 1, mid = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        if (L->elem[mid] == key) return mid;
        if (L->elem[mid] > key) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int bsr(SqList* L, int key, int low, int high) {
    if (low > high) return 0;
    int mid = (low + high) / 2;
    if (L->elem[mid] == key) return mid;
    if (L->elem[mid] < key) return bsr(L, key, mid + 1, high);
    return bsr(L, key, low, mid - 1);
}
int Binary_Search_Recursion(SqList* L, int key) {
    return bsr(L, key, 1, L->length);
}

BSTNode* BST_Search(BiTree T, int key) {
    while (T && key != T->data) {
        if (key < T->data) T = T->lchild;
        else T = T->rchild;
    }
    return T;
}

int BST_Insert(BiTree* T, int key) {
    if (!(*T)) {
        (*T) = calloc(1, sizeof(BSTNode));
        (*T)->data = key;
        return 1;
    }
    if (key == (*T)->data) return 0;
    if (key < (*T)->data) return BST_Insert(&(*T)->lchild, key);
    return BST_Insert(&(*T)->rchild, key);
}

BiTree BST_Init(int* key, int n) {
    BiTree T = NULL;
    for (int i = 0; i < n; i++) {
        BST_Insert(&T, key[i]);
    }
    return T;
}

int BST_Delete(BiTree T, int key) {
    BSTNode* p = T, *pre = p, *q = NULL;
    int temp = 0;
    while (p && p->data != key) {
        pre = p;
        if (p->data > key) p = p->lchild;
        else p = p->rchild;
    }
    if (!p) return 0;
    if (p->lchild && p->rchild) {
        q = p->rchild;
        while (q && q->lchild) q = q->lchild;
        temp = q->data;
        BST_Delete(p, q->data);
        p->data = temp;
    }
    else {
        if (p->lchild) {
            if (pre->lchild == p) pre->lchild = p->lchild;
            else pre->rchild = p->lchild;
        }
        else if (p->rchild) {
            if (pre->lchild == p) pre->lchild = p->rchild;
            else pre->rchild = p->rchild;
        }
        else {
            if (pre->lchild == p) pre->lchild = NULL;
            else pre->rchild = NULL;
        }
        free(p);
    }
    return 1;
}

// 中序遍历
int _MAX = 0;
int isBST(BiTree T) {
    if (!T) return 1;
    int left = isBST(T->lchild);
    if (!left || _MAX >= T->data) return 0;
    _MAX = T->data;
    return isBST(T->rchild); 
}
