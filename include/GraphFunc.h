#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

MatGraph* AdjListToMat(AdjListGraph* G);
int isEL(MatGraph* G);
void ALBFS(AdjListGraph* G);
int* ALsingleShortestPath(AdjListGraph* G, int u);
void ALDFS(AdjListGraph* G);
int ALGraphIsTree(AdjListGraph* G);
void ALDFSwithStack(AdjListGraph* G);
// mode = 1(bfs), 2(dfs)
int ALhavePath(AdjListGraph* G, int u, int v, int mode);
void ALallPath(AdjListGraph* G, int u, int v);
// 返回 path[u]=v 表示 e(u,v)
int* Prim(MatGraph* G);
int* PrimWithHeap(AdjListGraph* G);
// 返回 边的id
int* Kruskal(MulListGraph* G);
int* Dijkstra(MatGraph* G, int u);
int** Floyd(MatGraph* G);
int* TopologicalSort(AdjListGraph* G);
// 返回关键路径, 首元素为路径长
int* CriticalPath(OrthListGraph* G);
int* TopologicalSortUseDFS(AdjListGraph* G);
