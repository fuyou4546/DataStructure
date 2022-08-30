#include "../include/GraphFunc.h"

MatGraph* AdjListToMat(AdjListGraph* G) {
    MatGraph* M = calloc(1, sizeof(MatGraph));
    ArcNode* p = NULL;
    for (int i = 1; i <= G->vexnum; i++) {
        p = G->vertices[i].first;
        MatInsertVex(M, i);
        while (p) {
            MatAddArc(M, i, p->adjvex);
            p = p->next;
        }
    }
    return M;
}

int haveELpath(MatGraph* G) {
    int count = 0, degree = 0;
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = i; j <= G->vexnum; j++) {
            degree += G->Edge[i][j];
        }
        if (degree & 1) count++;
        if (count > 2) return 0;
        degree = 0;
    }
    return count == 0 || count == 2;
}

void bfs(AdjListGraph* G, int* visited, int vex) {
    if (visited[vex]) return;
    visited[vex] = 1;
    printf("%d ", vex);
    int front = 0, rear = 0, Q[100], p = 0;
    Q[rear++] = vex;
    while (front != rear) {
        p = Q[front++];
        for (ArcNode* v = G->vertices[p].first; v; v = v->next) {
            if (!visited[v->adjvex]) {
                visited[v->adjvex] = 1;
                printf("%d ", v->adjvex);
                Q[rear++] = v->adjvex;
            }
        }
    }
}
void ALBFS(AdjListGraph* G) {
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        bfs(G, visited, i);
    }
}

int* singleShortestPath(AdjListGraph* G, int u) {
    int* path = malloc((G->vexnum + 1) * sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) path[i] = INT_MAX;
    int* Q = malloc(G->vexnum * sizeof(int));
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    int front = 0, rear = 0, p = 0;
    Q[rear++] = u;
    visited[u] = 1;
    // 自身路径为0
    path[u] = 0;
    while (front != rear) {
        p = Q[front++];
        for (ArcNode* v = G->vertices[p].first; v; v = v->next) {
            if (!visited[v->adjvex]) {
                path[v->adjvex] = path[p] + 1;
                visited[v->adjvex] = 1;
                Q[rear++] = v->adjvex;
            }
        }
    }
    return path;
}

void dfs(AdjListGraph* G, int* visited, int u) {
    if (visited[u]) return;
    printf("%d ", u);
    visited[u] = 1;
    for (ArcNode* v = G->vertices[u].first; v; v = v->next) {
        dfs(G, visited, v->adjvex);
    }
}
void ALDFS(AdjListGraph* G) {
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        dfs(G, visited, i);
    }
}

int dfsGIT(AdjListGraph* G, int* visited, int* count, int* flag, int u, int pre) {
    if (visited[u]) {
        // 成环
        if (u != pre) *flag = 1;
        return 0;
    }
    visited[u] = 1;
    (*count)++;
    for (ArcNode* v = G->vertices[u].first; v; v = v->next) {
        if (*flag) return 0;
        dfsGIT(G, visited, count, flag, v->adjvex, &u);
        if (*count == G->vexnum) return 1;
    }
}
int ALGraphIsTree(AdjListGraph* G) {
    int count = 0, flag = 0;
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    return dfsGIT(G, visited, &count, &flag, 1, 0);
}
