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

int isEL(MatGraph* G) {
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
    free(visited);
}

int* ALsingleShortestPath(AdjListGraph* G, int u) {
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
    free(Q);
    free(visited);
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
    free(visited);
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
    free(visited);
    // 连通 且 度=(顶点数-1)*2
    return vexnum == G->vexnum && edgenum == (vexnum - 1) * 2;
}

void ALDFSwS(AdjListGraph* G, int* visited, int u) {
    if (visited[u]) return;
    int* st = malloc((G->vexnum + 1) * sizeof(int));
    int top = -1, p = 0;
    st[++top] = u;
    while (top != -1) {
        p = st[top--];
        visited[p] = 1;
        printf("%d ", p);
        for (ArcNode* v = G->vertices[p].first; v; v = v->next) {
            if (!visited[v->adjvex]) {
                // 必须在for内标记, 避免再次入栈
                visited[v->adjvex] = 1;
                st[++top] = v->adjvex;
            }
        }
    }
    free(st);
}
void ALDFSwithStack(AdjListGraph* G) {
    int* visited = calloc(1 + G->vexnum, sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        if (G->vertices[i].data) {
            ALDFSwS(G, visited, i);
        }
    }
    free(visited);
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
                if (x->adjvex == v) {
                    free(Q);
                    return 1;
                }
                visited[x->adjvex] = 1;
                Q[rear++] = x->adjvex;
            }
        }
    }
    free(Q);
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
    if (mode == 1) havePath_bfs(G, visited, u, v);
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
    free(visited);
    free(path);
}

int* Prim(MatGraph* G) {
    int* visited = calloc(G->vexnum + 1, sizeof(int));
    // dist[i] = d 表示在{V-T}中, 距离{T}最近的
    int* dist = malloc((G->vexnum + 1) * sizeof(int));
    int* path = malloc((G->vexnum + 1) * sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) dist[i] = INT_MAX;
    // 任选一顶点作为起始点加入T
    int u = 1, w = 0;
    visited[u] = 1;
    dist[u] = 0;
    path[u] = 0;
    // 循环顶点数-1次(再加入n-1个顶点)即可形成MST
    for (int i = 1; i < G->vexnum; i++) {
        w = INT_MAX;
        for (int j = 1; j <= G->vexnum; j++) {
            if (!visited[j] && dist[j] < w) {
                w = dist[j];
                u = j;
            }
        }
        visited[u] = 1;
        // 在新顶点u加入T后, 更新各顶点到T的最小距离
        for (int j = 1; j <= G->vexnum; j++) {
            if (!visited[j] && G->Edge[u][j] < dist[j]) {
                dist[j] = G->Edge[u][j];
                path[j] = u;
            }
        }
    }
    free(visited);
    free(dist);
    return path;
}

void KheapAdjust(MulArcNode** heap, int k, int n) {
    MulArcNode* temp = heap[k];
    for (int i = 2 * k; i <= n; i *= 2) {
        if (i < n && heap[i]->weight > heap[i + 1]->weight) {
            i++;
        }
        if (temp->weight <= heap[i]->weight) {
            break;
        }
        heap[k] = heap[i];
        k = i;
    }
    heap[k] = temp;
}
void KheapBuild(MulArcNode** heap, int n) {
    for (int i = n / 2; i > 0; i--) {
        KheapAdjust(heap, i, n);
    }
}
int* Kruskal(MulListGraph* G) {
    MulArcNode** heap = malloc((G->arcnum + 1) * sizeof(MulArcNode*));
    int* path = calloc(G->vexnum + 1, sizeof(int));
    int count = 0;
    for (int i = 1; i <= G->vexnum; i++) {
        for (MulArcNode* p = G->vertices[i].firstedge; p;) {
            if (p->ivex == i) {
                heap[++count] = p;
                p = p->ilink;
            }
            else p = p->jlink;
        }
    }
    KheapBuild(heap, G->arcnum);
    UFinit();
    MulArcNode* temp = NULL;
    count = 0;
    for (int i = G->arcnum; count < G->vexnum - 1; i--) {
        temp = heap[1];
        if (UFfind(temp->ivex) != UFfind(temp->jvex)) {
            UFmerge(temp->ivex, temp->jvex);
            path[count++] = temp->id;
        }
        heap[1] = heap[i];
        heap[i] = temp;
        KheapAdjust(heap, 1, i - 1);
    }
    return path;
}

int* Dijkstra(MatGraph* G, int u) {
    int* visited = calloc(1 + G->vexnum, sizeof(int));
    int* dist = malloc((1 + G->vexnum) * sizeof(int));
    int* path = malloc((1 + G->vexnum) * sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        dist[i] = G->Edge[u][i];
        if (G->Edge[u][i] != INT_MAX) path[i] = u;
    }
    path[u] = 0;
    visited[u] = 1;
    int v = 0, w = 0;
    // 只是确定循环数
    for (int i = 1; i < G->vexnum; i++) {
        w = INT_MAX;
        for (int j = 1; j <= G->vexnum; j++) {
            if (!visited[j] && dist[j] < w) {
                w = dist[j];
                v = j;
            }
        }
        visited[v] = 1;
        for (int j = 1; j <= G->vexnum; j++) {
            if (!visited[j] && G->Edge[v][j] != INT_MAX && dist[v] + G->Edge[v][j] < dist[j]) {
                dist[j] = dist[v] + G->Edge[v][j];
                path[j] = v;
            }
        }
    }
    free(visited);
    free(dist);
    return path;
}

int** Floyd(MatGraph* G) {
    int** path = malloc((1 + G->vexnum) * sizeof(int*));
    for (int i = 0; i <= G->vexnum; i++) path[i] = malloc((1 + G->vexnum) * sizeof(int));
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 1; j <= G->vexnum; j++) {
            path[i][j] = G->Edge[i][j];
        }
    }
    for (int k = 1; k <= G->vexnum; k++) {
        for (int i = 1; i <= G->vexnum; i++) {
            for (int j = 1; j <= G->vexnum; j++) {
                if (path[i][k] != INT_MAX && path[k][j] != INT_MAX 
                    && path[i][k] + path[k][j] < path[i][j]) {
                    path[i][j] = path[i][k] + path[k][j];
                }
            }
        }
    }
    return path;
}

int* TopologicalSort(AdjListGraph* G) {
    int* st = malloc((1 + G->vexnum) * sizeof(int));
    int* indegree = calloc(1 + G->vexnum, sizeof(int));
    int* seq = malloc((1 + G->vexnum) * sizeof(int));
    int top = -1, u = 0, cur = 0;
    for (int i = 1; i <= G->vexnum; i++) {
        for (ArcNode* p = G->vertices[i].first; p; p = p->next) {
            indegree[p->adjvex]++;
        }
    }
    for (int i = 1; i <= G->vexnum; i++) {
        if (!indegree[i]) st[++top] = i;
    }
    while (top != -1) {
        u = st[top--];
        seq[cur++] = u;
        for (ArcNode* p = G->vertices[u].first; p; p = p->next) {
            indegree[p->adjvex]--;
            if (!indegree[p->adjvex]) st[++top] = p->adjvex;
        }
    }
    free(st);
    free(indegree);
    return seq;
}

int* CriticalPath(OrthListGraph* G) {
    int* st = malloc((1 + G->vexnum) * sizeof(int));
    int* indegree = calloc(1 + G->vexnum, sizeof(int));
    // ve[i] 表示 顶点i的最早发生时间
    int* ve = calloc(1 + G->vexnum, sizeof(int));
    // vl[i] 表示 顶点i的最迟发生时间
    int* vl = malloc((1 + G->vexnum) * sizeof(int));
    // 前期保存拓扑序列, 后期保存关键路径
    int* path = malloc((1 + G->vexnum) * sizeof(int));
    int top = -1, cur = G->vexnum, u = 0;
    // 源点最早为0
    ve[1] = 0, path[0] = 0;
    // 初始化 vl 并 统计各顶点入度, 进行拓扑排序
    for (int i = 1; i <= G->vexnum; i++) {
        vl[i] = INT_MAX;
        for (OrthArcNode* p = G->vertices[i].firstin; p; p = p->headlink) {
            indegree[p->headvex]++;
        }
    }
    for (int i = 1; i <= G->vexnum; i++) {
        if (!indegree[i]) st[++top] = i;
    }
    while (top != -1) {
        u = st[top--];
        path[cur--] = u;
        for (OrthArcNode* p = G->vertices[u].firstout; p; p = p->taillink) {
            if (ve[u] + p->weight > ve[p->headvex]) {
                ve[p->headvex] = ve[u] + p->weight;
            }
            indegree[p->headvex]--;
            if (!indegree[p->headvex]) {
                st[++top] = p->headvex;
            }
        }
    }
    // 汇点的最迟 = 汇点的最早
    vl[G->vexnum] = ve[G->vexnum];
    for (int i = 1; i <= G->vexnum; i++) {
        u = path[i];
        for (OrthArcNode* p = G->vertices[u].firstin; p; p = p->headlink) {
            if (vl[u] - p->weight < vl[p->tailvex]) {
                vl[p->tailvex] = vl[u] - p->weight;
            }
        }
    }
    u = 1;
    OrthArcNode* p = G->vertices[u].firstout;
    while (p) {
        // ve[u] 表示 弧<u,p->headvex> 的最早开始时间
        // vl[p->headvex]-p->weight 表示 弧<u,p->headvex> 的最迟开始时间
        if (ve[u] == vl[p->headvex] - p->weight) {
            path[++path[0]] = u;
            u = p->headvex;
            p = G->vertices[u].firstout;
        }
        else p = p->taillink;
    }
    // 添加上述循环没添加的汇点
    path[++path[0]] = G->vexnum;
    free(st);
    free(ve);
    free(vl);
    return path;
}

void TSdfs(AdjListGraph* G, int u, int* visited, int* seq, int* time) {
    if (visited[u]) return;
    visited[u] = 1;
    for (ArcNode* p = G->vertices[u].first; p; p = p->next) {
        TSdfs(G, p->adjvex, visited, seq, time);
    }
    seq[u] = ++(*time);
}
int* TopologicalSortUseDFS(AdjListGraph* G) {
    int* visited = calloc(1 + G->vexnum, sizeof(int));
    int* seq = malloc((1 + G->vexnum) * sizeof(int));
    int time = 0;
    for (int i = 1; i <= G->vexnum; i++) {
        TSdfs(G, i, visited, seq, &time);
    }
    free(visited);
    return seq;
}
