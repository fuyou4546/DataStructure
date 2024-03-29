#include "../include/Tree.h"

void visit(BiTree T) {
    printf("%d ", T->data);
}

void preOrder(BiTree T) {
    if (!T) return;
    visit(T);
    preOrder(T->lchild);
    preOrder(T->rchild);
}

void inOrder(BiTree T) {
    if (!T) return;
    inOrder(T->lchild);
    visit(T);
    inOrder(T->rchild);
}

void postOrder(BiTree T) {
    if (!T) return;
    postOrder(T->lchild);
    postOrder(T->rchild);
    visit(T);
}

void levelOrder(BiTree T) {
    BiTree* queue = malloc(MAX_TREE_SIZE * sizeof(BiTree));
    int front = 0, rear = 0;
    queue[rear++] = T;
    BiTree temp = NULL;
    while (front != rear) {
        temp = queue[front++];
        visit(temp);
        if (temp->lchild) queue[rear++] = temp->lchild;
        if (temp->rchild) queue[rear++] = temp->rchild;
    }
}

void addP(BiTree T, BiNode* p) {
    if (!T) return;
    T->parent = p;
    addP(T->lchild, T);
    addP(T->rchild, T);
}

void addParent(BiTree T) {
    BiNode* p = NULL;
    addP(T, p);
}

int getHeight(BiTree T) {
    if (!T) return 0;
    int hl = getHeight(T->lchild);
    int hr = getHeight(T->rchild);
    return (hl > hr ? hl : hr) + 1;
}

int isCBiTree(BiTree T) {
    BiNode* Q[1000], *p = NULL;
    int front = 0, rear = 0;
    Q[rear++] = T;
    while (rear != front) {
        p = Q[front++];
        if (p) {
            Q[rear++] = p->lchild;
            Q[rear++] = p->rchild;
        }
        else {
            for (; front < rear; front++) {
                if (Q[front]) return 0;
            }
        }
    }
    return 1;
}

BiTree exchange(BiTree T) {
    if (!T) return NULL;
    BiTree left = exchange(T->lchild);
    BiTree right = exchange(T->rchild);
    T->lchild = right;
    T->rchild = left;
    return T;
}

void freeTree(BiTree* T) {
    if (!(*T)) return;
    freeTree(&((*T)->lchild));
    freeTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
}

void freeXSubTree(BiTree T, int x) {
    if (!T) return;
    if (T->lchild && T->lchild->data == x) {
        freeTree(&(T->lchild));
        T->lchild = NULL;
        return;
    }
    if (T->rchild && T->rchild->data == x) {
        freeTree(&(T->rchild));
        T->rchild = NULL;
        return;
    }
    freeXSubTree(T->lchild, x);
    freeXSubTree(T->rchild, x);
}

int _flag = 0;
void findXAncestors(BiTree T, int x) {
    if (_flag || !T) return;
    findXAncestors(T->lchild, x);
    findXAncestors(T->rchild, x);
    if (_flag || T->data == x) {
        if (_flag) visit(T);
        else _flag = 1;
    }
}

BiNode* findPublicAncestor(BiTree T, BiNode* p, BiNode* q) {
    if (!T || T == p || T == q) return T;
    BiNode* x = findPublicAncestor(T->lchild, p, q);
    BiNode* y = findPublicAncestor(T->rchild, p, q);
    if (x && y) return T;
    if (x) return x;
    return y;
}

void findPublicAncestor2(BiTree T, BiNode* p, BiNode* q, BiTree* res) {
    if (!T || T == p || T == q) {
        *res = T;
        return;
    }
    findPublicAncestor2(T->lchild, p, q, res);
    BiNode* x = *res;
    findPublicAncestor2(T->rchild, p, q, res);
    BiNode* y = *res;
    if (x && y) *res = T;
    else if (x) *res = x;
    else *res = y;
}

int getWidth(BiTree T) {
    BiNode* Q[100];
    int front = 0, rear = 0, width = 0, w, temp;
    BiNode* p = T;
    Q[rear++] = T;
    while (front != rear) {
        w = 0;
        temp = rear;
        while (front != temp) {
            p = Q[front++];
            w++;
            if (p->lchild) Q[rear++] = p->lchild;
            if (p->rchild) Q[rear++] = p->rchild;
        }
        if (w > width) width = w;
    }
    return width;
}

void preToP(int* pre, int* post, int pre_l, int pre_r, int post_l, int post_r) {
    if (pre_l > pre_r) return;
    post[post_r] = pre[pre_l];
    int half = (pre_r - pre_l) / 2;
    preToP(pre, post, pre_l + 1, pre_l + half, post_l, post_l + half - 1);
    preToP(pre, post, pre_l + half + 1, pre_r, post_l + half, post_r - 1);
}

int* preToPost(int* pre, int n) {
    int* post = (int*)malloc(n * sizeof(int));
    preToP(pre, post, 0, n - 1, 0, n - 1);
    return post;
}

void linkL(BiTree T, BiTree* pre) {
    if (!T) return;
    if (!T->lchild && !T->rchild) {
        (*pre)->rchild = T;
        *pre = T;
    }
    linkL(T->lchild, pre);
    linkL(T->rchild, pre);
}
BiNode* linkLeafs(BiTree T) {
    BiNode* head = (BiNode*)malloc(sizeof(BiNode));
    head->data = -1, head->lchild = NULL, head->rchild = NULL;
    BiNode* p = head;
    linkL(T, &p);
    return head;
}

int isSimilar(BiTree T1, BiTree T2) {
    if (!T1 && !T2) return 1;
    if (T1 && T2) return isSimilar(T1->lchild, T2->lchild) && isSimilar(T1->rchild, T2->rchild);
    return 0;
}

void preThread(BiTree T, BiTree* pre) {
    if (!T) return;
    if (!T->lchild) {
        T->lchild = *pre;
        T->ltag = 1;
    }
    if (*pre && !(*pre)->rchild) {
        (*pre)->rchild = T;
        (*pre)->rtag = 1;
    }
    *pre = T;
    if (!T->ltag) preThread(T->lchild, pre);
    if (!T->rtag) preThread(T->rchild, pre);
}

void createPreThread(BiTree T) {
    BiNode* pre = NULL;
    preThread(T, &pre);
    pre->rchild = NULL;
    pre->rtag = 1;
}

void preThreadOrder(BiTree T) {
    while (T) {
        visit(T);
        if (!T->ltag) T = T->lchild;
        else T = T->rchild;
    }
}

void inThread(BiTree T, BiTree* pre) {
    if (!T) return;
    inThread(T->lchild, pre);
    if (!T->lchild) {
        T->lchild = *pre;
        T->ltag = 1;
    }
    if (*pre && !(*pre)->rchild) {
        (*pre)->rchild = T;
        (*pre)->rtag = 1;
    }
    *pre = T;
    inThread(T->rchild, pre);
}

void createInThread(BiTree T) {
    BiNode* pre = NULL;
    inThread(T, &pre);
    pre->rchild = NULL;
    pre->rtag = 1;
}

void inThreadOrder(BiTree T) {
    if (!T) return;
    while (!T->ltag) T = T->lchild;
    while (T) {
        visit(T);
        if (T->rtag) T = T->rchild;
        else {
            T = T->rchild;
            while (!T->ltag) T = T->lchild;
        }
    }
}

void postThread(BiTree T, BiTree* pre) {
    if (!T) return;
    postThread(T->lchild, pre);
    postThread(T->rchild, pre);
    if (!T->lchild) {
        T->lchild = *pre;
        T->ltag = 1;
    }
    if (*pre && !(*pre)->rchild) {
        (*pre)->rchild = T;
        (*pre)->rtag = 1;
    }
    *pre = T;
}

void createPostThread(BiTree T) {
    addParent(T);
    BiNode* pre = NULL;
    postThread(T, &pre);
    if (!pre->rchild) {
        pre->rtag = 1;
    }
}

void postThreadOrder(BiTree T) {
    BiNode* p = T, *pre = NULL;
    while (p) {
        // 找最左的未访问结点
        while (p->lchild != pre && !p->ltag) {
            p = p->lchild;
        }
        // 若该结点非空且是有线索后继的结点, 访问并依此访问其后继, 同时更新pre
        while (p && p->rtag) {
            visit(p);
            pre = p;
            p = p->rchild;
        }
        // 若该无线索后继结点是根, 访问并退出
        if (p == T) {
            visit(p);
            return;
        }
        // 若该结点非空且其左右子树均已访问, 访问并依此访问其双亲结点, 同时更新pre
        while (p && p->rchild == pre) {
            visit(p);
            pre = p;
            p = p->parent;
        }
        // 若该结点非空且有右子树, 更新p
        if (p && !p->rtag) p = p->rchild;
    }
}

BiNode* inPostPreNode(BiNode* p) {
    if (!p->rtag) return p->rchild;
    if (!p->ltag) return p->lchild;
    if (!p->lchild) return NULL;
    while (p->ltag && p->lchild) p = p->lchild;
    if (!p->ltag) return p->lchild;
    return NULL;
}

int getW(BiTree T, int h) {
    static int wpl = 0;
    if (!T->lchild && !T->rchild) {
        wpl += T->data * h;
    }
    if (T->lchild) getW(T->lchild, h + 1);
    if (T->rchild) getW(T->rchild, h + 1);
    return wpl;
}
int getWPL(BiTree T) {
    return getW(T, 0);
}

void printIOE(BiTree T, int h) {
    if (!T) return;
    if (T->lchild || T->rchild) {
        if (h) printf("(");
        printIOE(T->lchild, h + 1);
    }
    printf("%d", T->data);
    if (T->lchild || T->rchild) {
        printIOE(T->rchild, h + 1);
        if (h) printf(")");
    }
}
void printInOrderExp(BiTree T) {
    printIOE(T, 0);
}

int countLeafs(CSTree T) {
    if (!T) return 0;
    if (!T->firstchild) return countLeafs(T->nextsibling) + 1;
    return countLeafs(T->firstchild) + countLeafs(T->nextsibling);
}

int getCSHeight(CSTree T) {
    if (!T) return 0;
    int x = getCSHeight(T->firstchild);
    int y = getCSHeight(T->nextsibling);
    return x + 1 > y ? x + 1 : y;
}

CSTree buildCSTree(int* in, int* degree) {
    CSNode* Q[100], *p = NULL;
    int front = 0, rear = 0;
    CSTree T = malloc(sizeof(CSNode));
    T->nextsibling = NULL;
    Q[rear++] = T;
    while (front != rear) {
        p = Q[front];
        p->data = in[front];
        if (degree[front]) {
            CSNode* child = malloc(sizeof(CSNode));
            Q[rear++] = child;
            p->firstchild = child;
            p = child;
            for (int i = 1; i < degree[front]; i++) {
                CSNode* sibling = malloc(sizeof(CSNode));
                Q[rear++] = sibling;
                p->nextsibling = sibling;
                p = sibling;
            }
            p->nextsibling = NULL;
        }
        front++;
    }
    return T;
}

void getDW(BiTree T, int data, int** path, int* p, int* i) {
    if (!T) return;
    p[0]++;
    p[p[0]] = T->data;
    data -= T->data;
    if (!data) {
        path[0][0]++;
        path[*i] = malloc((p[0] + 1) * sizeof(int));
        for (int j = 0; j <= p[0]; j++) {
            path[*i][j] = p[j];
        }
        (*i)++;
    }
    getDW(T->lchild, data, path, p, i);
    getDW(T->rchild, data, path, p, i);
    p[0]--;
}
int** getDataWay(BiTree T, int data) {
    int** path = malloc(10*sizeof(int*));
    path[0] = malloc(sizeof(int));
    path[0][0] = 0;
    int* p = malloc(20*sizeof(int));
    p[0] = 0;
    int i = 1;
    getDW(T, data, path, p, &i);
    path = realloc(path, i * sizeof(int*));
    return path;
}

void UFinit() {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        UFset[i] = i;
    }
}
int UFfind(int x) {
    if (x == UFset[x]) {
        return x;
    }
    return UFset[x] = UFfind(UFset[x]);
}
void UFmerge(int x, int y) {
    UFset[UFfind(x)] = UFfind(y);
}

int countNode(BiTree T) {
    if (!T) return 0;
    return countNode(T->lchild) + countNode(T->rchild) + 1;
}

BiTree preInbuild(int* pre, int* mark, int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    BiNode* node = malloc(sizeof(BiNode));
    node->data = pre[pl];
    int index = mark[pre[pl]];
    node->lchild = preInbuild(pre, mark, pl + 1, pl + index - il, il, index - 1);
    node->rchild = preInbuild(pre, mark, pl + index - il + 1, pr, index + 1, ir);
    return node;
}
BiTree preAndInBuildTree(int* pre, int* in, int n) {
    int* mark = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mark[in[i]] = i;
    }
    return preInbuild(pre, mark, 0, n - 1, 0, n - 1);
}

BiTree postInbuild(int* post, int* mark, int pl, int pr, int il, int ir) {
    if (pl > pr) return NULL;
    BiNode* node = malloc(sizeof(BiNode));
    node->data = post[pr];
    int index = mark[post[pr]];
    node->lchild = postInbuild(post, mark, pl, pl + index - il - 1, il, index - 1);
    node->rchild = postInbuild(post, mark, pl + index - il, pr - 1, index + 1, ir);
    return node;
}
BiTree postAndInBuildTree(int* post, int* in, int n) {
    int* mark = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mark[in[i]] = i;
    }
    return postInbuild(post, mark, 0, n - 1, 0, n - 1);
}

BiTree levelInbuild(int* level, int* mark, int* temp, int left, int right) {
    if (left > right) return NULL;
    BiTree node = malloc(sizeof(BiTree));
    int index = mark[level[left]];
    node->data = level[left];
    int cur1 = left, cur2 = index + 1;
    for (int i = left + 1; i <= right; i++) {
        if (mark[level[i]] < index) temp[cur1++] = level[i];
        if (mark[level[i]] > index) temp[cur2++] = level[i];
    }
    node->lchild = levelInbuild(temp, mark, level, left, index - 1);
    node->rchild = levelInbuild(temp, mark, level, index + 1, right);
    return node;
}
BiTree levelAndInBuildTree(int* level, int* in, int n) {
    int* mark = malloc(n * sizeof(int));
    int* temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mark[in[i]] = i;
    }
    return levelInbuild(level, mark, temp, 0, n - 1);
}

CSTree buildCSTree2(int* in, int* degree, int n) {
    CSTree* pointer = calloc(n, sizeof(CSTree));
    for (int i = 0; i < n; i++) {
        pointer[i]->data = in[i];
    }
    // 孩子结点的索引
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i]) {
            // 双亲i连接首孩子cur
            cur++;
            pointer[i]->firstchild = pointer[cur];
            for (int j = 1; j < degree[i]; j++) {
                // 孩子cur依次连接兄弟cur+1
                cur++;
                pointer[cur - 1]->nextsibling = pointer[cur];
            }
        }
    }
}

void preOrderNonRecursive(BiTree T) {
    BiTree* stack = malloc(MAX_TREE_SIZE * sizeof(BiTree));
    int top = 0;
    while (T || top) {
        if (T) {
            visit(T);
            stack[top++] = T;
            T = T->lchild;
        }
        else {
            T = stack[--top]->rchild;
        }
    }
}

void inOrderNonRecursive(BiTree T) {
    BiTree* stack = malloc(MAX_TREE_SIZE * sizeof(BiTree));
    int top = 0;
    while (T && top) {
        if (T) {
            stack[top++] = T;
            T = T->lchild;
        }
        else {
            T = stack[--top];
            visit(T);
            T = T->rchild;
        }
    }
}

void postOrderNonRecursive(BiTree T) {
    BiTree* stack = malloc(MAX_TREE_SIZE * sizeof(BiTree));
    int top = 0;
    // 标记最近访问结点
    BiTree pre = NULL;
    while (T || top) {
        if (T) {
            stack[top++] = T;
            T = T->lchild;
        }
        else {
            T = stack[top - 1];
            if (T->rchild && T->rchild != pre) {
                T = T->rchild;
            }
            else {
                visit(T);
                pre = T;
                // 借while循环, 在下次循环else中取上层结点
                // 若不置空直接取上层结点, 则在下次循环中可能进入if访问左子树, 产生循环
                T = NULL;
                top--;
            }
        }
    }
}
