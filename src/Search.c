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

// -----------------BST-----------------

int SgetHeight(SearchTree T) {
    if (!T) return 0;
    int hl = SgetHeight(T->lchild);
    int hr = SgetHeight(T->rchild);
    return (hl > hr ? hl : hr) + 1;
}

void BST_inOrder(BSTTree T) {
    if (!T) return;
    BST_inOrder(T->lchild);
    printf("%d ", T->data);
    BST_inOrder(T->rchild);
}

BSTNode* BST_Search(BSTTree T, int key) {
    while (T && key != T->data) {
        if (key < T->data) T = T->lchild;
        else T = T->rchild;
    }
    return T;
}

int BST_Insert(BSTTree* T, int key) {
    if (!(*T)) {
        (*T) = calloc(1, sizeof(BSTNode));
        (*T)->data = key;
        return 1;
    }
    if (key == (*T)->data) return 0;
    if (key < (*T)->data) return BST_Insert(&(*T)->lchild, key);
    return BST_Insert(&(*T)->rchild, key);
}

BSTTree BST_Init(int* key, int n) {
    BSTTree T = NULL;
    for (int i = 0; i < n; i++) {
        BST_Insert(&T, key[i]);
    }
    return T;
}

int BST_Delete(BSTTree* T, int key) {
    BSTNode* p = *T, *pre = NULL, *q = NULL;
    int temp = 0;
    while (p && p->data != key) {
        pre = p;
        if (p->data > key) {
            p = p->lchild;
        }
        else p = p->rchild;
    }
    if (!p) {
        return 0;
    }
    if (p->lchild && p->rchild) {
        pre = p;
        q = p->rchild;
        while (q && q->lchild) {
            pre = q;
            q = q->lchild;
        }
        temp = q->data;
        BST_Delete(&pre, q->data);
        p->data = temp;
    }
    else {
        if (p->lchild) {
            if (!pre) {
                *T = p->lchild;
            }
            else if (pre->lchild == p) {
                pre->lchild = p->lchild;
            }
            else {
                pre->rchild = p->lchild;
            }
        }
        else if (p->rchild) {
            if (!pre) {
                *T = p->rchild;
            }
            else if (pre->lchild == p) {
                pre->lchild = p->rchild;
            }
            else {
                pre->rchild = p->rchild;
            }
        }
        else {
            if (!pre) {
                *T = NULL;
            }
            else if (pre->lchild == p) {
                pre->lchild = NULL;
            }
            else {
                pre->rchild = NULL;
            }
        }
        free(p);
    }
    return 1;
}

int BST_Delete_Path(BSTTree* T, int key, BSTTree* path, int* top) {
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
int isbst(BSTTree T, int* max) {
    if (!T) return 1;
    int left = isbst(T->lchild, max);
    if (!left || *max >= T->data) {
        return 0;
    }
    *max = T->data;
    return isbst(T->rchild, max); 
}
int isBST(BSTTree T) {
    int max = INT_MIN;
    return isbst(T, &max);
}

int BST_findMinAndMax(BSTTree T, int* minKey, int* maxKey) {
    if (!T) return 0;
    BSTTree p = T;
    while (p && p->lchild) {
        p = p->lchild;
    }
    *minKey = p->data;
    p = T;
    while (p && p->rchild) {
        p = p->rchild;
    }
    *maxKey = p->data;
    return 1;
}

void BST_printKeyGTE(BSTTree T, int k) {
    if (!T) return;
    BST_printKeyGTE(T->rchild, k);
    if (T->data < k) return;
    printf("%d ", T->data);
    BST_printKeyGTE(T->lchild, k);
}

int BST_addCount(BSTTree T) {
    if (!T) return 0;
    int cl = BST_addCount(T->lchild);
    int cr = BST_addCount(T->rchild);
    return T->count = cl + cr + 1;
}

BSTNode* BST_KthLess(BSTTree T, int k) {
    if (!T) return NULL;
    int left = T->lchild ? T->lchild->count : 0;
    if (k == left + 1) return T;
    if (k < left + 1) return BST_KthLess(T->lchild, k);
    return BST_KthLess(T->rchild, k - left - 1);
}

// -----------------AVL-----------------

AVLNode* AVL_Search(AVLTree T, int key) {
    return BST_Search(T, key);
}

SearchTree Rotate(SearchTree T, char* mode) {
    SearchTree temp = NULL;
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
        temp = Rotate(T->lchild, "RR");
        T->lchild = temp;
        return Rotate(T, "LL");
    }
    if (!strcmp(mode, "RL")) {
        temp = Rotate(T->rchild, "LL");
        T->rchild = temp;
        return Rotate(T, "RR");
    }
    return NULL;
}

int AVL_Insert(AVLTree* T, int key) {
    // path 记录 根到插入点的路径, path[top]为插入点
    // mode 记录 若路径上的结点失衡, 其失衡的模式
    AVLNode* p = *T, *path[MAX_LEN];
    char mode[MAX_LEN][3] = { 0 };
    int top = -1;
    // 找插入点, 并求路径上各结点可能的旋转模式
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
        hl = SgetHeight(q->lchild);
        hr = SgetHeight(q->rchild);
        if (abs(hl - hr) > 1) {
            flag = 1;
            break;
        }
    }
    // 没有失衡点
    if (!flag) return 1;
    // 结点q失衡, 用旋转后的结点替代q
    q = Rotate(q, mode[height]);
    if (!height) *T = q;
    else {
        if (mode[height - 1][0] == 'L') {
            path[height - 1]->lchild = q;
        }
        else path[height - 1]->rchild = q;
    }
    return 1;
}

AVLTree AVL_Init(int* key, int n) {
    AVLTree T = NULL;
    for (int i = 0; i < n; i++) {
        AVL_Insert(&T, key[i]);
    }
    return T;
}

int isavl(AVLTree T, int* flag) {
    if (!T || !*flag) return 0;
    int hl = isavl(T->lchild, flag);
    int hr = isavl(T->rchild, flag);
    if (abs(hl - hr) > 1) *flag = 0;
    return (hl > hr ? hl : hr) + 1;
}
int isAVL(AVLTree T) {
    int flag = 1;
    isavl(T, &flag);
    return flag;
}

int AVL_Delete(AVLTree* T, int key) {
    AVLTree p = *T, q, path[MAX_LEN];
    int top = -1;
    if (!BST_Delete_Path(T, key, path, &top)) return 0;
    int hl = 0, hr = 0, flag = 0;
    for (int i = top; i >= 0; i--) {
        q = path[i];
        hl = SgetHeight(q->lchild);
        hr = SgetHeight(q->rchild);
        if (abs(hl - hr) > 1) {
            if (hl - hr > 1) {
                p = q->lchild;
                hl = SgetHeight(p->lchild);
                hr = SgetHeight(p->rchild);
                if (hl >= hr) q = Rotate(q, "LL");
                else q = Rotate(q, "LR");
            }
            else {
                p = q->rchild;
                hl = SgetHeight(p->lchild);
                hr = SgetHeight(p->rchild);
                if (hr >= hl) q = Rotate(q, "RR");
                else q = Rotate(q, "RL");
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

// -----------------RB-----------------

RBNode* RB_Search(RBTree T, int key) {
    return BST_Search(T, key);
}

int RB_Insert(RBTree* T, int key) {
    RBTree p = *T, q, path[MAX_LEN];
    char mode[MAX_LEN][3] = { 0 };
    int top = -1;
    // 找插入位置并记录路径上结点及其相对位置
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
    // 记p为当前结点, 染红
    p = calloc(1, sizeof(RBNode));
    p->data = key;
    p->color = 'r';
    while (1) {
        // case2, 当前结点为根结点
        if (top == -1) {
            p->color = 'b';
            *T = p;
            return 1;
        }
        // 当前结点非根节点
        if (mode[top][0] == 'L') {
            path[top]->lchild = p;
        }
        else path[top]->rchild = p;
        // case1, 父结点是黑结点, 无需调整
        if (path[top]->color == 'b') return 1;
        // case3, 父结点是红结点
        q = path[top - 1];
        // case3.1, 叔结点是黑结点
        // 染色, 按相应模式旋转爷结点
        if (!q->lchild || q->lchild->color == 'b' || 
                !q->rchild || q->rchild->color == 'b') {
            q->color = 'r';
            q = Rotate(q, mode[top - 1]);
            q->color = 'b';
            if (top == 1) *T = q;
            else if (mode[top - 2][0] == 'L') {
                path[top - 2]->lchild = q;
            }
            else path[top - 2]->rchild = q;
            return 1;
        }
        // case3.2, 叔结点是红结点
        // 染色, 将爷结点视为当前结点, 路径指针上移两层, 重复case1~3直到退出
        else {
            q->color = 'r';
            path[top]->color = 'b';
            if (mode[top - 1][0] == 'L') {
                path[top - 1]->rchild->color = 'b';
            }
            else path[top - 1]->lchild->color = 'b';
            p = q;
            top -= 2;
        }
    }
}

RBTree RB_Init(int* key, int n) {
    RBTree T = NULL;
    for (int i = 0; i < n; i++) {
        RB_Insert(&T, key[i]);
    }
    return T;
}

int isrb(RBTree T, int blackNum, int countBlack) {
    if (!T) return 1;
    // 红结点相邻
    if (T->color == 'r' && (T->lchild && T->lchild->color == 'r' ||
        T->rchild && T->rchild->color == 'r')) return 0;
    if (T->color == 'b') countBlack++;
    // 黑高是否等
    if (!T->lchild && !T->rchild) return blackNum == countBlack;
    return isrb(T->lchild, blackNum, countBlack) && 
            isrb(T->rchild, blackNum, countBlack);
}
int isRB(RBTree T) {
    if (!T || T->color != 'b' || !isBST(T)) return 0;
    int countBlack = 0;
    RBTree p = T;
    while (p) {
        if (p->color == 'b') countBlack++;
        p = p->lchild;
    }
    return isrb(T, countBlack, 0);
}

int RB_Delete(RBTree* T, int key) {
    RBTree p = *T, path[MAX_LEN];
    int top = -1;
    while (p && p->data != key) {
        path[++top] = p;
        if (key < p->data) {
            p = p->lchild;
        }
        else {
            p = p->rchild;
        }
    }
    if (!p) return 0;
    RBTree q = NULL;
    // case1, 待删结点p有左右孩子, 用直接后继的值替代其值, 转换为删除其直接后继
    if (p->lchild && p->rchild) {
        int temp = 0;
        q = p->rchild;
        while (q && q->lchild) {
            q = q->lchild;
        }
        temp = q->data;
        RB_Delete(T, q->data);
        p->data = temp;
        return 1;
    }
    // case2, 待删结点p只有左或右孩子
    if (p->lchild) {
        p->lchild->color = 'b';
        if (top == -1) {
            *T = p->lchild;
        }
        else if (path[top]->lchild == p) {
            path[top]->lchild = p->lchild;
        }
        else {
            path[top]->rchild = p->lchild;
        }
        return 1;
    }
    if (p->rchild) {
        p->rchild->color = 'b';
        if (top == -1) {
            *T = p->rchild;
        }
        else if (path[top]->lchild == p) {
            path[top]->lchild = p->rchild;
        }
        else {
            path[top]->rchild = p->rchild;
        }
        return 1;
    }
    // case3, 待删结点p无孩子
    // case3.0, 待删结点p为根节点
    if (top == -1) {
        *T = NULL;
        return 1;
    }
    // 记pp为p的双亲结点
    RBTree pp = path[top];
    // case3.1, 待删结点p为红结点, 直接删除
    if (p->color == 'r') {
        if (pp->lchild == p) {
            pp->lchild = NULL;
        }
        else {
            pp->rchild = NULL;
        }
        return 1;
    }
    // case3.2, 待删结点p为黑结点, 将p更新为用来代替待删结点p的结点
    if (pp->lchild == p) {
        pp->lchild = NULL;
    }
    else {
        pp->rchild = NULL;
    }
    p = NULL;
    RBNode* bro = NULL;
    while (1) {
        // case3.2, p是其双亲结点的左结点的情况
        if (pp->lchild == p) {
            bro = pp->rchild;
            // case3.2.1, p的兄弟bro是红色的
            if (bro->color == 'r') {
                bro->color = 'b';
                pp->color = 'r';
                q = Rotate(pp, "RR");
                if (!top) {
                    *T = q;
                }
                else if (path[top - 1]->lchild == pp) {
                    path[top - 1]->lchild = q;
                }
                else {
                    path[top - 1]->rchild = q;
                }
                path[top] = q;
                path[++top] = pp;
            }
            else {
                // case3.2.2, bro是黑色的 且 bro的左孩子是红色的，右孩子是黑色的
                if (bro->lchild && bro->lchild->color == 'r' && 
                        (!bro->rchild || bro->rchild->color == 'b')) {
                    bro->color = 'r';
                    bro->lchild->color = 'b';
                    q = Rotate(bro, "LL");
                    pp->rchild = q;
                }
                // case3.2.3, bro是黑色的 且 bro的右孩子是红色的
                else if (bro->rchild && bro->rchild->color == 'r') {
                    bro->color = pp->color;
                    pp->color = 'b';
                    bro->rchild->color = 'b';
                    q = Rotate(pp, "RR");
                    if (!top) {
                        *T = q;
                    }
                    else if (path[top - 1]->lchild == pp) {
                        path[top - 1]->lchild = q;
                    }
                    else {
                        path[top - 1]->rchild = q;
                    }
                    return 1;
                }
                // case3.2.3, bro是黑色的 且 bro的孩子都是黑色的
                else {
                    bro->color = 'r';
                    if (!top || pp->color == 'r') {
                        pp->color = 'b';
                        return 1;                                
                    }
                    p = pp;
                    pp = path[--top];
                }
            }
        }
        // case3.2, p是其双亲结点的右结点的情况
        else {
            bro = pp->lchild;
            // case3.2.1, p的兄弟bro是红色的
            if (bro->color == 'r') {
                bro->color = 'b';
                pp->color = 'r';
                q = Rotate(pp, "LL");
                if (!top) {
                    *T = q;
                }
                else if (path[top - 1]->lchild == pp) {
                    path[top - 1]->lchild = q;
                }
                else {
                    path[top - 1]->rchild = q;
                }
                path[top] = q;
                path[++top] = pp;
            }
            else {
                // case3.2.2, bro是黑色的 且 bro的右孩子是红色的，左孩子是黑色的
                if (bro->rchild && bro->rchild->color == 'r' && 
                        (!bro->lchild || bro->lchild->color == 'b')) {
                    bro->color = 'r';
                    bro->rchild->color = 'b';
                    q = Rotate(bro, "RR");
                    pp->lchild = q;
                }
                // case3.2.3, bro是黑色的 且 bro的左孩子是红色的
                else if (bro->lchild && bro->lchild->color == 'r') {
                    bro->color = pp->color;
                    pp->color = 'b';
                    bro->lchild->color = 'b';
                    q = Rotate(pp, "LL");
                    if (!top) {
                        *T = q;
                    }
                    else if (path[top - 1]->lchild == pp) {
                        path[top - 1]->lchild = q;
                    }
                    else {
                        path[top - 1]->rchild = q;
                    }
                    return 1;
                }
                // case3.2.3, bro是黑色的 且 bro的孩子都是黑色的
                else {
                    bro->color = 'r';
                    if (!top || pp->color == 'r') {
                        pp->color = 'b';
                        return 1;                                
                    }
                    p = pp;
                    pp = path[--top];
                }
            }
        }
    }
    return 1;
}

// -----------------B-----------------

int B_Search(BTree* T, int key) {
    BNode* p = T->root;
    int left = 0, right = p->n - 1, mid = 0;
    while (p) {
        while (left <= right) {
            mid = (left + right) / 2;
            if (p->key[mid] == key) return 1;
            if (p->key[mid] < key) left = mid + 1;
            else right = mid - 1;
        }
        p = p->child[left];
    }
    return 0;
}

int B_BinarySearch(int* L, int n, int key) {
    int left = 0, right = n - 1, mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (L[mid] == key) return mid;
        if (L[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

int B_Insert(BTree* T, int key) {
    BNode* p = T->root;
    // 若树空
    if (!p) {
        BNode* root = malloc(sizeof(BNode));
        root->child = calloc(T->m, sizeof(BNode*));
        root->key = malloc((T->m - 1) * sizeof(int));
        root->n = 1;
        root->key[0] = key;
        T->root = root;
        T->size = 1;
        return 1;
    }
    int cur, right, mid;
    BNode* path[MAX_LEN];
    int top = -1;
    // 记录路径, cur保存插入位置
    while (p) {
        cur = 0, right = p->n - 1;
        while (cur <= right) {
            mid = (cur + right) / 2;
            if (p->key[mid] == key) return 0;
            if (p->key[mid] < key) cur = mid + 1;
            else right = mid - 1;
        }
        path[++top] = p;
        p = p->child[cur];
    }
    T->size++;
    BNode* q = path[top], *bn = NULL;
    while (top != -1) {
        // 将插入位置之后的键值和子树指针后移
        for (int i = q->n - 1; i >= cur; i--) {
            q->key[i + 1] = q->key[i];
            q->child[i + 2] = q->child[i + 1];
        }
        // 插入结点
        q->n++;
        q->key[cur] = key;
        q->child[cur + 1] = bn;
        if (q->n < T->m) break;
        // 若插入后结点关键字数大于等于m-1 分裂
        // bn为分裂出的结点, 保存后一半的键值和子树指针
        bn = malloc(sizeof(BNode));
        bn->child = calloc(T->m, sizeof(BNode*));
        bn->key = malloc((T->m - 1) * sizeof(int));
        bn->n = q->n - q->n / 2 - 1;
        q->n /= 2;  
        // key为要上移的键值, 要将其插入父结点中
        key = q->key[q->n];
        memcpy(bn->key, q->key + q->n + 1, bn->n * sizeof(int));
        memcpy(bn->child, q->child + q->n + 1, (bn->n + 1) * sizeof(BNode*));
        top--;
        // 树根分裂
        if (top == -1) {
            BNode* root = malloc(sizeof(BNode));
            root->child = calloc(T->m, sizeof(BNode*));
            root->key = malloc((T->m - 1) * sizeof(int));
            root->n = 1;
            root->key[0] = key;
            if (q->key[0] < bn->key[0]) {
                root->child[0] = q;
                root->child[1] = bn;
            }
            else {
                root->child[0] = bn;
                root->child[1] = q;
            }
            T->root = root;
        }
        // 查找key在父结点的插入位置
        else {
            q = path[top];
            cur = B_BinarySearch(q->key, q->n, key);
        }
    }
    return 1;
}

BTree* B_Init(int* key, int n, int m) {
    BTree* T = calloc(1, sizeof(BTree));
    T->m = m;
    for (int i = 0; i < n; i++) {
        B_Insert(T, key[i]);
    }
    return T;
}

void isb(BNode* p, int* MAX, int* flag, int m) {
    if (!p || !*flag) return;
    if (p->n >= m) *flag = 0;
    for (int i = 0; i < p->n; i++) {
        isb(p->child[i], MAX, flag, m);
        if (i > 0 && p->key[i] <= p->key[i - 1] || p->key[i] <= *MAX) {
            *flag = 0;
        }
        *MAX = p->key[i];
    }
    isb(p->child[p->n], MAX, flag, m);
}
int isB(BTree* T) {
    int MAX = INT_MIN;
    int flag = 1;
    isb(T->root, &MAX, &flag, T->m);
    return flag;
}

void B_LeOrder(BTree* T) {
    BNode* p = NULL;
    BNode** Q = malloc(T->size * sizeof(BNode*));
    int front = 0, rear = 0, mark = 0;
    Q[rear++] = T->root;
    while (front != rear) {
        mark = rear;
        while (front != mark) {
            p = Q[front++];
            for (int i = 0; i < p->n; i++) {
                printf("%d ", p->key[i]);
                if (p->child[i]) {
                    Q[rear++] = p->child[i];
                }
            }
            printf("| ");
            if (p->child[p->n]) {
                Q[rear++] = p->child[p->n];
            }
        }
        printf("\n");
    }
}

int B_Delete(BTree* T, int key) {
    BNode* p = T->root, *q = NULL;
    int m = T->m, top = -1;
    BNode* path[MAX_LEN];
    int cur[MAX_LEN];
    int pcur = 0, qcur = 0;
    while (p) {
        path[++top] = p;
        cur[top] = B_BinarySearch(p->key, p->n, key);
        if (cur[top] < p->n && p->key[cur[top]] == key) {
            q = p;
            qcur = cur[top];
            // 如果要删的结点不是终端节点, 用直接后继替代, 转为删除直接后继
            p = p->child[qcur + 1];
            while (p) {
                path[++top] = p;
                cur[top] = 0;
                p = p->child[0];
            }
            q->key[qcur] = path[top]->key[0];
        }
        else p = p->child[cur[top]];
    }
    // 树空
    if (top == -1) return 0;
    T->size--;
    // 根结点是终端结点
    if (!top) {
        p->n--;
        if (!cur[top]) T->root = NULL;
        else {
            for (int i = cur[top]; i < path[top]->n; i++) {
                path[top]->key[i] = path[top]->key[i + 1];
            }
        }
        return 1;
    }
    while (1) {
        p = path[top];
        pcur = cur[top];
        q = path[top - 1];
        qcur = cur[top - 1];
        BNode* bro = NULL;
        // 要删的结点键值数 >= (m + 1)/2, 直接删
        if (p->n >= (m + 1) / 2) {
            p->n--;
            for (int i = pcur; i < p->n; i++) {
                p->key[i] = p->key[i + 1];
                p->child[i] = p->child[i + 1];
            }
            p->child[p->n] = p->child[p->n + 1];
            return 1;
        }
        // 要删的结点是双亲的最右子树
        if (qcur == q->n) {
            bro = q->child[qcur - 1];
            // 左兄够借
            if (bro->n >= (m + 1) / 2) {
                p->child[p->n] = p->child[p->n - 1];
                for (int i = p->n - 1; i > 0; i--) {
                    p->key[i] = p->key[i - 1];
                    p->child[i] = p->child[i - 1];
                }
            }
        }
    }
    return 0;
}
