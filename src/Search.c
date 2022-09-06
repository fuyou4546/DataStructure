#include "../include/Search.h"

#define MAX_LEN 10

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

int BST_Delete(BiTree* T, int key) {
    BSTNode* p = *T, *pre = NULL, *q = NULL;
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
        BST_Delete(T, q->data);
        p->data = temp;
    }
    else {
        if (p->lchild) {
            if (!pre) *T = p->lchild;
            else if (pre->lchild == p) pre->lchild = p->lchild;
            else pre->rchild = p->lchild;
        }
        else if (p->rchild) {
            if (!pre) *T = p->rchild;
            else if (pre->lchild == p) pre->lchild = p->rchild;
            else pre->rchild = p->rchild;
        }
        else {
            if (!pre) *T = NULL;
            else if (pre->lchild == p) pre->lchild = NULL;
            else pre->rchild = NULL;
        }
        free(p);
    }
    return 1;
}

int BST_Delete_Path(BiTree* T, int key, BiTree* path, int* top) {
    BSTNode* p = *T, *pre = NULL, *q = NULL;
    int temp = 0;
    *top = -1;
    while (p && p->data != key) {
        pre = p;
        path[++(*top)] = p;
        if (p->data > key) p = p->lchild;
        else p = p->rchild;
    }
    if (!p) return 0;
    if (p->lchild && p->rchild) {
        q = p->rchild;
        while (q && q->lchild) q = q->lchild;
        temp = q->data;
        BST_Delete_Path(T, q->data, path, top);
        p->data = temp;
    }
    else {
        if (p->lchild) {
            if (!pre) *T = p->lchild;
            else if (pre->lchild == p) pre->lchild = p->lchild;
            else pre->rchild = p->lchild;
        }
        else if (p->rchild) {
            if (!pre) *T = p->rchild;
            else if (pre->lchild == p) pre->lchild = p->rchild;
            else pre->rchild = p->rchild;
        }
        else {
            if (!pre) *T = NULL;
            else if (pre->lchild == p) pre->lchild = NULL;
            else pre->rchild = NULL;
        }
        free(p);
    }
    return 1;
}

// 中序遍历
int isbst(BiTree T, int* max) {
    if (!T) return 1;
    int left = isbst(T->lchild, max);
    if (!left || *max >= T->data) {
        return 0;
    }
    *max = T->data;
    return isbst(T->rchild, max); 
}
int isBST(BiTree T) {
    int max = INT_MIN;
    return isbst(T, &max);
}

AVLNode* AVL_Search(BiTree T, int key) {
    return BST_Search(T, key);
}

BiTree AVL_Rotate(BiTree T, char* mode) {
    BiTree temp = NULL;
    if (!strcmp(mode, "LL")) {
        temp = T->lchild;
        T->lchild = temp->rchild;
        temp->rchild = T;
        return temp;
    }
    if (!strcmp(mode, "RR")) {
        temp = T->rchild;
        T->rchild = temp->lchild;
        temp->lchild = T;
        return temp;
    }
    if (!strcmp(mode, "LR")) {
        temp = AVL_Rotate(T->lchild, "RR");
        T->lchild = temp;
        return AVL_Rotate(T, "LL");
    }
    if (!strcmp(mode, "RL")) {
        temp = AVL_Rotate(T->rchild, "LL");
        T->rchild = temp;
        return AVL_Rotate(T, "RR");
    }
    return NULL;
}

int AVL_Insert(BiTree* T, int key) {
    // path 记录 根到插入点的路径, path[top]为插入点
    // mode 记录 若路径上的结点失衡, 其失衡的模式
    AVLNode* p = *T, *path[MAX_LEN];
    char mode[MAX_LEN][3] = { 0 };
    int top = -1;
    // 找插入点
    while (p) {
        path[++top] = p;
        if (key == p->data) return 0;
        if (key < p->data) {
            p = p->lchild;
            if (top > -1) mode[top][0] = 'L';
            if (top) mode[top - 1][1] = 'L';
        }
        else {
            p = p->rchild;
            if (top > -1) mode[top][0] = 'R';
            if (top) mode[top - 1][1] = 'R';
        }
    }
    // 初始化并插入新结点
    p = calloc(1, sizeof(AVLNode));
    p->data = key;
    if (top == -1) {
        *T = p;
        return 1;
    }
    AVLNode *q = path[top];
    if (key < q->data) {
        q->lchild = p;
    }
    else q->rchild = p;
    // 找出路径上离插入点最近的失衡结点 q = path[height]
    int hl = 0, hr = 0, flag = 0, height = 0;
    for (int i = top - 1; i >= 0; i--) {
        q = path[i];
        height = i;
        hl = getHeight(q->lchild);
        hr = getHeight(q->rchild);
        if (abs(hl - hr) > 1) {
            flag = 1;
            break;
        }
    }
    // 没有失衡点
    if (!flag) return 1;
    // 结点q失衡, 用旋转后的结点替代q
    q = AVL_Rotate(q, mode[height]);
    if (!height) *T = q;
    else {
        if (mode[height - 1][0] == 'L') {
            path[height - 1]->lchild = q;
        }
        else path[height - 1]->rchild = q;
    }
    return 1;
}

BiTree AVL_Init(int* key, int n) {
    BiTree T = NULL;
    for (int i = 0; i < n; i++) {
        AVL_Insert(&T, key[i]);
    }
    return T;
}

int isavl(BiTree T, int* flag) {
    if (!T || !*flag) return 0;
    int hl = isavl(T->lchild, flag);
    int hr = isavl(T->rchild, flag);
    if (abs(hl - hr) > 1) *flag = 0;
    return (hl > hr ? hl : hr) + 1;
}
int isAVL(BiTree T) {
    int flag = 1;
    if (isBST(T)) {
        isavl(T, &flag);
        return flag;
    }
    return 0;
}

int AVL_Delete(BiTree* T, int key) {
    BiTree p = *T, path[MAX_LEN];
    int top = -1;
    if (!BST_Delete_Path(T, key, path, &top)) return 0;
    AVLNode* q = NULL;
    int hl = 0, hr = 0, flag = 0;
    for (int i = top; i >= 0; i--) {
        q = path[i];
        hl = getHeight(q->lchild);
        hr = getHeight(q->rchild);
        if (abs(hl - hr) > 1) {
            if (hl - hr > 1) {
                p = q->lchild;
                hl = getHeight(p->lchild);
                hr = getHeight(p->rchild);
                if (hl >= hr) q = AVL_Rotate(q, "LL");
                else q = AVL_Rotate(q, "LR");
            }
            else {
                p = q->rchild;
                hl = getHeight(p->lchild);
                hr = getHeight(p->rchild);
                if (hr >= hl) q = AVL_Rotate(q, "RR");
                else q = AVL_Rotate(q, "RL");
            }
            if (!i) *T = q;
            else if (path[i - 1]->lchild == path[i]) {
                path[i - 1]->lchild = q;
            }
            else path[i - 1]->rchild = q;
        }
    }
    return 1;
}
