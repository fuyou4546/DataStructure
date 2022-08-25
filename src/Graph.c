#include "../include/Graph.h"

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
    p = G->vertices[y].first;
    while (p) {
        if (p->adjvex == x) return 1;
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
    G->vertices[x].data = 0;
    G->vertices[x].first = NULL;
    for (int i = 1; i <= G->vexnum; i++) {
        ALRemoveArc(G, i, x);
    }
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
    while (p->next) {
        if (p->next->adjvex == y) {
            p->next = p->next->next;
            G->arcnum--;
            return 1;
        }
    }
    return 0;
}
int ALFirstNeighbor(AdjListGraph* G, int x) {
    if (!ALIsVex(G, x)) return 0;
    return G->vertices[x].first->adjvex;
}
int ALNextNeighbor(AdjListGraph* G, int x, int y) {
    ArcNode* p = G->vertices[x].first->next;
    while (p) {
        if (p->adjvex == y) {
            if (p->next) return p->next->adjvex;
            return -1;
        }
    }
    return 0;
}
AdjListGraph* ALInitGraph(int* inode, int* jnode, int n) {
    AdjListGraph* G = calloc(1, sizeof(AdjListGraph));
    for (int i = 0; i < n; i++) {
        ALAddArc(G, inode[i], jnode[i]);
    }
    return G;
}

