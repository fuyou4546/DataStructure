#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

MatGraph* AdjListToMat(AdjListGraph* G);
int isEL(MatGraph* G);
void AL_BFS(AdjListGraph* G);
int* AL_singleShortestPath(AdjListGraph* G, int u);
void AL_DFS(AdjListGraph* G);
int AL_GraphIsTree(AdjListGraph* G);
void AL_DFSwithStack(AdjListGraph* G);
int ALhavePath(AdjListGraph* G, int u, int v, int mode);
void ALallPath(AdjListGraph* G, int u, int v);
int* Prim(MatGraph* G);
int* Kruskal(AdjListGraph* G);
int* Dijkstra(MatGraph* G, int u);
int** Floyd(MatGraph* G);
