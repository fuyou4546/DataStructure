#include <stdio.h>
#include <stdlib.h>

#define MaxVerTexNum 20

// 邻接矩阵
typedef struct {
    int Vex[MaxVerTexNum];
    int Edge[MaxVerTexNum][MaxVerTexNum];
    int vexnum, arcnum;
} MatGraph;
int MatIsVex(MatGraph* G, int x);
int MatIsAdj(MatGraph* G, int x, int y);
int MatInsertVex(MatGraph* G, int x);
int MatDeleteVex(MatGraph* G, int x);
int MatAddArc(MatGraph* G, int x, int y);
int MatRemoveArc(MatGraph* G, int x, int y);
MatGraph* MatInitGraph(int* inode, int* jnode, int n);
MatGraph* MatInitWithWeight(int* inode, int *jnode, int* weight, int n);

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
int ALIsVex(AdjListGraph* G, int x);
int ALIsAdj(AdjListGraph* G, int x, int y);
int ALInsertVex(AdjListGraph* G, int x);
int ALDeleteVex(AdjListGraph* G, int x);
int ALAddArc(AdjListGraph* G, int x, int y);
int ALRemoveArc(AdjListGraph* G, int x, int y);
int ALFirstNeighbor(AdjListGraph* G, int x);
int ALNextNeighbor(AdjListGraph* G, int x, int y);
int ALOutDegree(AdjListGraph* G, int x);
AdjListGraph* ALInitGraph(int* inode, int* jnode, int n);

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
int OrthIsVex(OrthListGraph* G, int x);
int OrthIsAdj(OrthListGraph* G, int x, int y);
int OrthInsertVex(OrthListGraph* G, int x);
int OrthDeleteVex(OrthListGraph* G, int x);
int OrthAddArc(OrthListGraph* G, int x, int y);
int OrthRemoveArc(OrthListGraph* G, int x, int y);
int OrthFirstNeighbor(OrthListGraph* G, int x);
int OrthNextNeighbor(OrthListGraph* G, int x, int y);
int OrthOutDegree(OrthListGraph* G, int x);
int OrthInDegree(OrthListGraph* G, int x);
OrthListGraph* OrthInitGraph(int* inode, int* jnode, int n);

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
int MLIsVex(MulListGraph* G, int x);
int MLIsAdj(MulListGraph* G, int x, int y);
int MLInsertVex(MulListGraph* G, int x);
int MLDeleteVex(MulListGraph* G, int x);
int MLAddArc(MulListGraph* G, int x, int y);
int MLRemoveArc(MulListGraph* G, int x, int y);
int MLFirstNeighbor(MulListGraph* G, int x);
int MLNextNeighbor(MulListGraph* G, int x, int y);
int MLDegree(MulListGraph* G, int x);
MulListGraph* MLInitGraph(int* inode, int* jnode, int n);
