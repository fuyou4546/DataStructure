#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/Structures.h"

typedef struct {
    int* seq;
    int length;
} testData;

void testSqList();
void testLinkList();
void testSLinkList();
void testPolynomial();
void testTree();
void testGraph();
void testGraphFunc();
void testSearch();
testData* randData(int x, int y, int n);
void testBST();
