#include <stdlib.h>
#include <stdio.h>
#include "Structures.h"
#include <time.h>

// 所有排序默认升序
int isAscending(int* L, int n);
void straightInsertionSort(int* L, int n);
void binaryInsertionSort(int* L, int n);
void shellSort(int* L, int n);
void bubbleSort(int* L, int n);
void quickSort(int* L, int n);
void selectSort(int* L, int n);
// 大根堆
void heapAdd(int* L, int n, int key);
void heapBuild(int* L, int n);
void heapSort(int* L, int n);
void mergeSort(int* L, int n);
void radixSortUseLink(int* L, int n);
void radixSortUseArray(int* L, int n);
void radixSortUseArrayOptimized(int* L, int n);
void bidiBubbleSort(int* L, int n);
void moveOddBeforeEven(int* L, int n);
int quickSelect(int* L, int n, int k);
void colorPartition(int* L, int n);
int setPartition(int* L, int n);
int setPartition2(int* L, int n);
void selectSortLinkList(LinkList* L);
int isHeap(int* L, int n);
void countSort(int* L, int n);
// 将r个长len[i]的归并段L[i]归并为总长total的升序列res
void kMergeSort(int** L, int* len, int r, int total, int* res);
// 将L划分为r个归并段, 段res[i]长len[i]
void replaceSelectSort(int* L, int n, int w, int** res, int* len, int* r);
