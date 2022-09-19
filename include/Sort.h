#include <stdlib.h>
#include <stdio.h>
#include "Structures.h"
#include <time.h>

int isAscending(int* L, int n);
void straightInsertionSort(int* L, int n);
void binaryInsertionSort(int* L, int n);
void shellSort(int* L, int n);
void bubbleSort(int* L, int n);
void quickSort(int* L, int n);
void selectSort(int* L, int n);
void heapBuild(int* L, int n);
void heapSort(int* L, int n);
void mergeSort(int* L, int n);
void radixSort(int* L, int n);
void bidiBubbleSort(int* L, int n);
void moveOddBeforeEven(int* L, int n);
int quickSelect(int* L, int n, int k);
void colorPartition(int* L, int n);
int setPartition(int* L, int n);
void selectSortLinkList(LinkList* L);
int isHeap(int* L, int n);
void countSort(int* L, int n);
void kMergeSort(int** L, int* len, int n, int total, int* res);
