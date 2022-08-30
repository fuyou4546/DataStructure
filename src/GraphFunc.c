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
    int* Q = malloc((G->vexnum + 1) * sizeof(int));
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
        dfsGIT(G, visited, count, flag, v->adjvex, u);
        if (*count == G->vexnum) return 1;
    }
}
void dfsGIT2(AdjListGraph* G, int* visited, int* vexnum, int* edgenum, int u) {
    if (visited[u]) return;
    visited[u] = 1;
    (*vexnum)++;
    for (ArcNode* v = G->vertices[u].first; v; v = v->next) {
        (*edgenum)++;
        dfsGIT2(G, visited, vexnum, edgenum, v->adjvex);
    }
}
int ALGraphIsTree(AdjListGraph* G) {
    // int count = 0, flag = 0;
    int vexnum = 0, edgenum = 0; 
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    // return dfsGIT(G, visited, &count, &flag, 1, 0);
    dfsGIT2(G, visited, &vexnum, &edgenum, 1);
    return vexnum == G->vexnum && edgenum == (vexnum - 1) * 2;
}

void ALDFSwS(AdjListGraph* G, int* visited, int u) {
    if (visited[u]) return;
    int* st = malloc((G->vexnum + 1) * sizeof(int));
    int top = -1, p = 0;
    st[++top] = u;
    while (top != -1) {
        p = st[top--];
        printf("%d ", p);
        for (ArcNode* v = G->vertices[p].first; v; v = v->next) {
            if (!visited[v->adjvex]) {
                visited[v->adjvex] = 1;
                st[++top] = v->adjvex;
            }
        }
    }
}
void ALDFSwithStack(AdjListGraph* G) {
    int* visited = calloc(1 + G->vexnum, sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        ALDFSwS(G, visited, i);
    }
}

int havePath_bfs(AdjListGraph* G, int* visited, int u, int v) {
    int* Q = malloc(G->vexnum * sizeof(int));
    int front = 0, rear = 0, p = 0;
    Q[rear++] = u;
    visited[u] = 1;
    while (front != rear) {
        p = Q[front++];
        for (ArcNode* x = G->vertices[p].first; x; x = x->next) {
            if (!visited[x->adjvex]) {
                if (x->adjvex == v) return 1;
                visited[x->adjvex] = 1;
                Q[rear++] = x->adjvex;
            }
        }
    }
    return 0;
}
int havePath_dfs(AdjListGraph* G, int* visited, int u, int v) {
    if (u == v) return 1;
    if (visited[u]) return 0;
    visited[u] = 1;
    for (ArcNode* p = G->vertices[u].first; p; p = p->next) {
        if (havePath_dfs(G, visited, p->adjvex, v)) return 1;
    }
    return 0;
}
int ALhavePath(AdjListGraph* G, int u, int v, int mode) {
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    if (mode == 1) return havePath_bfs(G, visited, u, v);
    return havePath_dfs(G, visited, u, v);
}

void allpath(AdjListGraph* G, int* visited, int u, int v, int* path, int len) {
    if (visited[u]) return;
    if (u == v) {
        for (int i = 0; i < len - 1; i++) printf("%d->", path[i]);
        printf("%d\n", v);
        return;
    }
    visited[u] = 1;
    path[len] = u;
    for (ArcNode* p = G->vertices[u].first; p; p = p->next) {
        allpath(G, visited, p->adjvex, v, path, len + 1);
    }
    // 现场恢复要写在循环外, 与 visited[u] = 1 呼应
    visited[u] = 0;
}
void ALallPath(AdjListGraph* G, int u, int v) {
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    int* path = malloc((G->vexnum + 1) * sizeof(int));
    allpath(G, visited, u, v, path, 0);
}
