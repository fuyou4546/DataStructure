#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode {
    int data;
    struct BiNode* lchild, *rchild, *parent;
    int ltag, rtag;
} BiNode, *BiTree;

typedef struct CSNode {
    int data;
    struct CSNode* firstchild, *nextsibling;
} CSNode, *CSTree;

void addParent(BiTree T);
void createPreThread(BiTree T);
void createInThread(BiTree T);
void createPostThread(BiTree T);
void preThreadOrder(BiTree T);
void inThreadOrder(BiTree T);
void postThreadOrder(BiTree T);
void preOrder(BiTree T);
void inOrder(BiTree T);
void postOrder(BiTree T);
int getHeight(BiTree T);
int isCBiTree(BiTree T);
BiTree exchange(BiTree T);
void freeXSubTree(BiTree T, int x);
void findXAncestors(BiTree T, int x);
BiNode* findPublicAncestor(BiTree T, BiNode* p, BiNode* q);
void findPublicAncestor2(BiTree T, BiNode* p, BiNode* q, BiTree* res);
int getWidth(BiTree T);
int* preToPost(int* pre, int n);
BiNode* linkLeafs(BiTree T);
int isSimilar(BiTree T1, BiTree T2);
BiNode* inPostPreNode(BiNode* p);
int getWPL(BiTree T);
void printInOrderExp(BiTree T);
int countLeafs(CSTree T);
int getCSHeight(CSTree T);
CSTree buildCSTree(int* in, int* degree);
int** getDataWay(BiTree T, int data);