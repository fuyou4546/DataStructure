#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

MatGraph* AdjListToMat(AdjListGraph* G);
int isEL(MatGraph* G);
void ALBFS(AdjListGraph* G);
int* singleShortestPath(AdjListGraph* G, int u);
void ALDFS(AdjListGraph* G);
int ALGraphIsTree(AdjListGraph* G);
