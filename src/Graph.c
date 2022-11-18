#include "../include/Graph.h"

// 邻接矩阵
int MatIsVex(MatGraph* G, int x) {
    return G->Vex[x];
}
int MatIsAdj(MatGraph* G, int x, int y) {
    return MatIsVex(G, x) && MatIsVex(G, y) && G->Edge[x][y];
}
int MatInsertVex(MatGraph* G, int x) {
    if (MatIsVex(G, x)) return 0;
    G->Vex[x] = 1;
    G->vexnum++;
    return 1;
}
int MatDeleteVex(MatGraph* G, int x) {
    if (!MatIsVex(G, x)) return 0;
    for (int i = 1; i <= G->vexnum; i++) {
        MatRemoveArc(G, x, i);
        MatRemoveArc(G, i, x);
    }
    G->Vex[x] = 0;
    G->vexnum--;
    return 1;
}
int MatAddArc(MatGraph* G, int x, int y) {
    if (MatIsAdj(G, x, y)) return 0;
    if (!MatIsVex(G, x)) MatInsertVex(G, x);
    if (!MatIsVex(G, y)) MatInsertVex(G, y);
    G->Edge[x][y] = 1;
    G->arcnum++;
    return 1;
}
int MatRemoveArc(MatGraph* G, int x, int y) {
    if (!MatIsAdj(G, x, y)) return 0;
    G->Edge[x][y] = 0;
    G->arcnum--;
    return 1;
}
MatGraph* MatInitGraph(int* inode, int *jnode, int n) {
    MatGraph* G = calloc(1, sizeof(MatGraph));
    for (int i = 0; i < n; i++) {
        MatAddArc(G, inode[i], jnode[i]);
    }
    return G;
}
MatGraph* MatInitWithWeight(int* inode, int *jnode, int* weight, int n) {
    MatGraph* G = calloc(1, sizeof(MatGraph));
    for (int i = 0; i < n; i++) {
        MatAddArc(G, inode[i], jnode[i]);
        G->Edge[inode[i]][jnode[i]] = weight[i];
    }
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 1; j <= G->vexnum; j++) {
            if (i != j && !G->Edge[i][j]) G->Edge[i][j] = INT_MAX;
        }
    }
    return G;
}


// 邻接表
int ALIsVex(AdjListGraph* G, int x) {
    return G->vertices[x].data;
}
int ALIsAdj(AdjListGraph* G, int x, int y) {
    if (!ALIsVex(G, x) || !ALIsVex(G, y)) return 0;
    ArcNode* p = G->vertices[x].first;
    while (p) {
        if (p->adjvex == y) return 1;
        p = p->next;
    }
    return 0;
}
int ALInsertVex(AdjListGraph* G, int x) {
    if (ALIsVex(G, x)) return 0;
    G->vertices[x].data = 1;
    G->vexnum++;
    return 1;
}
int ALDeleteVex(AdjListGraph* G, int x) {
    if (!ALIsVex(G, x)) return 0;
    for (int i = 1; i <= G->vexnum; i++) {
        ALRemoveArc(G, i, x);
    }
    G->arcnum -= ALOutDegree(G, x);
    G->vertices[x].data = 0;
    G->vertices[x].first = NULL;
    G->vexnum--;
    return 1;
}
int ALAddArc(AdjListGraph* G, int x, int y) {
    if (ALIsAdj(G, x, y)) return 0;
    if (!ALIsVex(G, x)) ALInsertVex(G, x);
    if (!ALIsVex(G, y)) ALInsertVex(G, y);
    ArcNode* p = calloc(1, sizeof(ArcNode));
    p->adjvex = y;
    p->next = G->vertices[x].first;
    G->vertices[x].first = p;
    G->arcnum++;
    return 1;
}
int ALRemoveArc(AdjListGraph* G, int x, int y) {
    if (!ALIsAdj(G, x, y)) return 0;
    ArcNode* p = G->vertices[x].first;
    if (p->adjvex == y) {
        G->vertices[x].first = p->next;
    }
    else while (p->next) {
        if (p->next->adjvex == y) {
            p->next = p->next->next;
            break;
        }
        p = p->next;
    }
    G->arcnum--;
    return 1;
}
int ALFirstNeighbor(AdjListGraph* G, int x) {
    if (!ALIsVex(G, x)) return 0;
    ArcNode* p = G->vertices[x].first;
    if (!p) return 0;
    return p->adjvex;
}
int ALNextNeighbor(AdjListGraph* G, int x, int y) {
    ArcNode* p = G->vertices[x].first;
    while (p) {
        if (p->adjvex == y) {
            if (p->next) return p->next->adjvex;
            return -1;
        }
        p = p->next;
    }
    return 0;
}
int ALOutDegree(AdjListGraph* G, int x) {
    if (!ALIsVex(G, x)) return 0;
    ArcNode* p = G->vertices[x].first;
    int count = 0;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}
AdjListGraph* ALInitGraph(int* inode, int* jnode, int n) {
    AdjListGraph* G = calloc(1, sizeof(AdjListGraph));
    for (int i = 0; i < n; i++) {
        ALAddArc(G, inode[i], jnode[i]);
    }
    return G;
}


// 十字链表
int OrthIsVex(OrthListGraph* G, int x) {
    return G->vertices[x].data;
}
int OrthIsAdj(OrthListGraph* G, int x, int y) {
    if (!OrthIsVex(G, x) || !OrthIsVex(G, y)) return 0;
    OrthArcNode* p = G->vertices[x].firstout;
    while (p) {
        if (p->headvex == y) return 1;
        p = p->taillink;
    }
    return 0;
}
int OrthInsertVex(OrthListGraph* G, int x) {
    if (OrthIsVex(G, x)) return 0;
    G->vertices[x].data = 1;
    G->vexnum++;
    return 1;
}
int OrthDeleteVex(OrthListGraph* G, int x) {
    if (!OrthIsVex(G, x)) return 0;
    // 删弧尾是x的弧
    OrthArcNode* p = G->vertices[x].firstout;
    while (p) {
        OrthRemoveArc(G, x, p->headvex);
        p = G->vertices[x].firstout;
    }
    // 删弧头是x的弧
    p = G->vertices[x].firstin;
    while (p) {
        OrthRemoveArc(G, p->tailvex, x);
        p = G->vertices[x].firstin;
    }
    G->vertices[x].data = 0;
    G->vexnum--;
    return 1;
}
int OrthAddArc(OrthListGraph* G, int x, int y) {
    if (OrthIsAdj(G, x, y)) return 0;
    if (!OrthIsVex(G, x)) OrthInsertVex(G, x);
    if (!OrthIsVex(G, y)) OrthInsertVex(G, y);
    OrthArcNode* p = calloc(1, sizeof(OrthArcNode));
    p->tailvex = x;
    p->headvex = y;
    // 将p插入以x为弧尾的链表
    p->taillink = G->vertices[x].firstout;
    G->vertices[x].firstout = p;
    // 将p插入以y为弧头的链表
    p->headlink = G->vertices[y].firstin;
    G->vertices[y].firstin = p;
    G->arcnum++;
    return 1;
}
int OrthRemoveArc(OrthListGraph* G, int x, int y) {
    if (!OrthIsAdj(G, x, y)) return 0;
    // 在以x为弧尾的链表中删除弧x->y
    OrthArcNode* p = G->vertices[x].firstout;
    if (p->headvex == y) {
        G->vertices[x].firstout = p->taillink;
    }
    else while (p->taillink) {
        if (p->taillink->headvex == y) {
            p->taillink = p->taillink->taillink;
            break;
        }
        p = p->taillink;
    }
    // 在以y为弧头的链表中删除弧x->y
    p = G->vertices[y].firstin;
    if (p->tailvex == x) {
        G->vertices[y].firstin = p->headlink;
    }
    else while (p->headlink) {
        if (p->headlink->tailvex == x) {
            p->headlink = p->headlink->headlink;
            break;
        }
        p = p->headlink;
    }
    G->arcnum--;
    return 1;
}
int OrthFirstNeighbor(OrthListGraph* G, int x) {
    if (!OrthIsVex(G, x)) return 0;
    OrthArcNode* p = G->vertices[x].firstout;
    if (!p) return 0;
    return p->headvex;
}
int OrthNextNeighbor(OrthListGraph* G, int x, int y) {
    OrthArcNode* p = G->vertices[x].firstout;
    while (p) {
        if (p->headvex == y) {
            if (p->taillink) return p->taillink->headvex;
            return -1;
        }
        p = p->taillink;
    }
    return 0;
}
int OrthOutDegree(OrthListGraph* G, int x) {
    if (!OrthIsVex(G, x)) return 0;
    OrthArcNode* p = G->vertices[x].firstout;
    int count = 0;
    while (p) {
        count++;
        p = p->taillink;
    }
    return count;
}
int OrthInDegree(OrthListGraph* G, int x) {
    if (!OrthIsVex(G, x)) return 0;
    OrthArcNode* p = G->vertices[x].firstin;
    int count = 0;
    while (p) {
        count++;
        p = p->headlink;
    }
    return count;
}
OrthListGraph* OrthInitGraph(int* inode, int* jnode, int n) {
    OrthListGraph* G = calloc(1, sizeof(OrthListGraph));
    for (int i = 0; i < n; i++) {
        OrthAddArc(G, inode[i], jnode[i]);
    }
    return G;
}
OrthListGraph* OrthInitWithIdAndWeight(int* inode, int* jnode, int* weight, int n) {
    OrthListGraph* G = calloc(1, sizeof(OrthListGraph));
    for (int i = 0; i < n; i++) {
        OrthAddArc(G, inode[i], jnode[i]);
        G->vertices[inode[i]].firstout->id = i + 1;
        G->vertices[inode[i]].firstout->weight = weight[i];
    }
    return G;
}


// 多重链表, 简单图
int MLIsVex(MulListGraph* G, int x) {
    return G->vertices[x].data;
}
int MLIsAdj(MulListGraph* G, int x, int y) {
    if (!MLIsVex(G, x) || !MLIsVex(G, y)) return 0;
    MulArcNode* p = G->vertices[x].firstedge;
    while (p) {
        if (p->ivex == x) {
            if (p->jvex == y) return 1;
            p = p->ilink;
        }
        else {
            if (p->ivex == y) return 1;
            p = p->jlink;
        }
    }
    return 0;
}
int MLInsertVex(MulListGraph* G, int x) {
    if (MLIsVex(G, x)) return 0;
    G->vertices[x].data = 1;
    G->vexnum++;
    return 1;
}
int MLDeleteVex(MulListGraph* G, int x) {
    if (!MLIsVex(G, x)) return 0;
    MulArcNode* p = G->vertices[x].firstedge;
    while (p) {
        if (p->ivex == x) {
            MLRemoveArc(G, x, p->jvex);
            p = p->ilink;
        }
        else {
            MLRemoveArc(G, p->ivex, x);
            p = p->jlink;
        }
    }
    G->vertices[x].data = 0;
    G->vexnum--;
    return 1;
}
int MLAddArc(MulListGraph* G, int x, int y) {
    if (MLIsAdj(G, x, y)) return 0;
    if (!MLIsVex(G, x)) MLInsertVex(G, x);
    if (!MLIsVex(G, y)) MLInsertVex(G, y);
    MulArcNode* p = calloc(1, sizeof(MulArcNode));
    p->ivex = x;
    p->jvex = y;
    p->ilink = G->vertices[x].firstedge;
    G->vertices[x].firstedge = p;
    p->jlink = G->vertices[y].firstedge;
    G->vertices[y].firstedge = p;
    G->arcnum++;
    return 1;
}
int MLAddArcWithIdAndWeight(MulListGraph* G, int x, int y, int id, int weight) {
    if (MLIsAdj(G, x, y)) return 0;
    if (!MLIsVex(G, x)) MLInsertVex(G, x);
    if (!MLIsVex(G, y)) MLInsertVex(G, y);
    MulArcNode* p = calloc(1, sizeof(MulArcNode));
    p->ivex = x;
    p->jvex = y;
    p->id = id;
    p->weight = weight;
    p->ilink = G->vertices[x].firstedge;
    G->vertices[x].firstedge = p;
    p->jlink = G->vertices[y].firstedge;
    G->vertices[y].firstedge = p;
    G->arcnum++;
    return 1;
}
int MLRemoveArc(MulListGraph* G, int x, int y) {
    // if (!MLIsAdj(G, x, y)) return 0;
    MulArcNode* p = G->vertices[x].firstedge, *pre = NULL;
    int flag = 0;
    while (p) {
        if (p->ivex == x) {
            if (p->jvex == y) {
                if (!pre) G->vertices[x].firstedge = p->ilink;
                else {
                    if (flag) pre->ilink = p->ilink;
                    else pre->jlink = p->ilink;
                }
                break;
            }
            flag = 1;
            pre = p;
            p = p->ilink;
        }
        else {
            if (p->ivex == y) {
                if (!pre) G->vertices[x].firstedge = p->jlink;
                else {
                    if (flag) pre->ilink = p->jlink;
                    else pre->jlink = p->jlink;
                }
                break;
            }
            flag = 0;
            pre = p;
            p = p->jlink;
        }
    }
    pre = NULL;
    p = G->vertices[y].firstedge;
    while (p) {
        if (p->ivex == y) {
            if (p->jvex == x) {
                if (!pre) G->vertices[y].firstedge = p->ilink;
                else {
                    if (flag) pre->ilink = p->ilink;
                    else pre->jlink = p->ilink;
                }
                break;
            }
            flag = 1;
            pre = p;
            p = p->ilink;
        }
        else {
            if (p->ivex == x) {
                if (!pre) G->vertices[y].firstedge = p->jlink;
                else {
                    if (flag) pre->ilink = p->jlink;
                    else pre->jlink = p->jlink;
                }
                break;
            }
            flag = 0;
            pre = p;
            p = p->jlink;
        }
    }
    G->arcnum--;
    return 1;
}
int MLFirstNeighbor(MulListGraph* G, int x) {
    if (!MLIsVex(G, x)) return 0;
    MulArcNode* p = G->vertices[x].firstedge;
    if (!p) return 0;
    return p->ivex == x ? p->jvex : p->ivex;
}
int MLNextNeighbor(MulListGraph* G, int x, int y) {
    MulArcNode* p = G->vertices[x].firstedge;
    while (p) {
        if (p->ivex == x) {
            if (p->jvex == y) {
                if (p->ilink) {
                    return p->ilink->ivex == x ? p->ilink->jvex : p->ilink->ivex;
                }
                return -1;
            }
            p = p->ilink;
        }
        else {
            if (p->ivex == y) {
                if (p->jlink) {
                    return p->jlink->ivex == x ? p->jlink->jvex : p->jlink->ivex;
                }
                return -1;
            }
            p = p->jlink;
        }
    }
    return 0;
}
int MLDegree(MulListGraph* G, int x) {
    if (!MLIsVex(G, x)) return 0;
    MulArcNode* p = G->vertices[x].firstedge;
    int count = 0;
    while (p) {
        count++;
        if (p->ivex == x) p = p->ilink;
        else p = p->jlink;
    }
    return count;
}
MulListGraph* MLInitGraph(int* inode, int* jnode, int n) {
    MulListGraph* G = calloc(1, sizeof(MulListGraph));
    for (int i = 0; i < n; i++) {
        MLAddArc(G, inode[i], jnode[i]);
    }
    return G;
}

MulListGraph* MLInitWithIdAndWeight(int* inode, int* jnode, int* weight, int n) {
    MulListGraph* G = calloc(1, sizeof(MulListGraph));
    for (int i = 0; i < n; i++) {
        MLAddArcWithIdAndWeight(G, inode[i], jnode[i], i + 1, weight[i]);
    }
    return G;
}