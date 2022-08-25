#include <stdio.h>
#include <stdlib.h>

#define MaxVerTexNum 100

// 邻接矩阵
typedef struct {
    int Vex[MaxVerTexNum];
    int Edge[MaxVerTexNum][MaxVerTexNum];
    int vexnum, arcnum;
} MatGraph;

// 邻接表
typedef struct ArcNode {
    int adjvex;
    struct ArcNode* next;
    int info;
} ArcNode;
typedef struct {
    int data;
    ArcNode *first;
} VexNode, AdjList[MaxVerTexNum];
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} AdjListGraph;

// 十字链表
typedef struct OrthArcNode {
    int tailvex, headvex;
    struct OrthArcNode* taillink, *headlink;
    int info;
} OrthArcNode;
typedef struct {
    int data;
    OrthArcNode* firstin, *firstout;
} OrthVexNdoe, OrthList[MaxVerTexNum];
typedef struct {
    OrthList vertices;
    int vexnum, arcnum;
} OrthListGraph;

// 多重链表
typedef struct MulArcNode {
    int mark;
    int ivex, jvex;
    struct MulArcNode* ilink, *jlink;
    int info;
} MulArcNode;
typedef struct {
    int data;
    MulArcNode* firstedge;
} MulVexNode, MulList[MaxVerTexNum];
typedef struct {
    MulList vertices;
    int vexnum, arcnum;
} MulListGraph;

int MatIsAdj(MatGraph* G, int x, int y);
int MatIsVex(MatGraph* G, int x);
int MatAddArc(MatGraph* G, int x, int y);
int MatRemoveArc(MatGraph* G, int x, int y);
int MatInsertVex(MatGraph* G, int x);
int MatDeleteVex(MatGraph* G, int x);
MatGraph* initMatGraph(int* inode, int *jnode, int n);
