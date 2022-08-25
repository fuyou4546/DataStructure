#include "../include/Graph.h"

int MatIsVex(MatGraph* G, int x) {
    return G->Vex[x];
}
int MatIsAdj(MatGraph* G, int x, int y) {
    return MatIsVex(G, x) && MatIsvex(G, y) && G->Edge[x][y];
}
int MatInsertVex(MatGraph* G, int x) {
    if (MatIsVex(G, x)) return 0;
    G->Vex[x] = 1;
    G->vexnum++;
    return 1;
}
int MatDeleteVex(MatGraph* G, int x) {
    if (!MatIsVex(G, x)) return 0;
    for (int i = 1; i < MaxVerTexNum; i++) {
        MatRemoveArc(G, x, i);
        MatRemoveArc(G, i, x);
    }
    G->Vex[x] = 0;
    G->vexnum--;
    return 1;
}
int MatAddArc(MatGraph* G, int x, int y) {
    if (MatIsAdj(G, x, y)) return 0;
    if (!MatIsVex(G, x)) {
        MatInsertVex(G, x);
    }
    if (!MatIsVex(G, y)) {
        MatInsertVex(G, y);
    }
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
MatGraph* initMatGraph(int* inode, int *jnode, int n) {
    MatGraph* G = calloc(1, sizeof(MatGraph));
    for (int i = 0; i < n; i++) {
        MatAddArc(G, inode[i], jnode[i]);
    }
    return G;
}
