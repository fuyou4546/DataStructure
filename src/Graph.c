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
    if (!ALIsVex(G, x) || !ALIsVex(G, y)) return 0;
    ArcNode* p = G->vertices[x].first;
    if (!p) return 0;
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
    int outdegree = 0;
    while (p) {
        outdegree++;
        p = p->next;
    }
    return outdegree;
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
    ArcNode* p = G->vertices[x].firstout;
    while (p) {
        if (p->adjvex == y) return 1;
        p = p->next;
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
    OrthArcNode* p = G->vertices[x].firstout;
    while (p) {
        OrthRemoveArc(G, x, p->headvex);
    }
    G->vertices[x].data = 0;
    return 1;
}
int OrthAddArc(OrthListGraph* G, int x, int y) {
    if (OrthIsAdj(G, x, y)) return 0;
    if (!OrthIsVex(G, x)) OrthInsertVex(G, x);
    if (!OrthIsVex(G, y)) OrthInsertVex(G, y);
    OrthArcNode* p = calloc(1, sizeof(OrthArcNode));
    p->tailvex = x;
    p->headvex = y;
    p->taillink = G->vertices[x].firstout;
    G->vertices[x].firstout = p;
    p->headlink = G->vertices[y].firstin;
    G->vertices[y].firstin = p;
    G->arcnum++;
    return 1;
}
int OrthRemoveArc(OrthListGraph* G, int x, int y) {
    if (!OrthIsVex(G, x) || !OrthIsVex(G, y)) return 0;
    OrthArcNode* p = G->vertices[x].firstout;
    if (p->headvex == y) {
        p = p->headlink;
    }
    else while (p->headlink) {
        if (p->headlink->headvex == y) {
            p->headlink = p->headlink->headlink;
            break;
        }
        p = p->headlink;
    }
    p = G->vertices[y].firstin;
    if (p->taillink == x) {
        p = p->taillink;
    }
    else while (p->taillink) {
        if (p->taillink->tailvex == x) {
            p->taillink = p->taillink->taillink;
            break;
        }
        p = p->taillink;
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
int OrthNextNeighbor(OrthListGraph* G, int x, int y);
int OrthOutDegree(OrthListGraph* G, int x);
OrthListGraph* OrthInitGraph(int* inode, int* jnode, int n);
