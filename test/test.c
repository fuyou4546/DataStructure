#include "test.h"

void myprint(int a) {
    printf("%d ", a);
}
void testSqList() {
    SqList* List1 = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(List1);
    SqList* List2 = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(List2);
    for (int i = 0; i < 5; i++) {
        ListInsert_Sq(List1, 1, 10 - 2 * i);
        ListInsert_Sq(List2, i + 1, 3 * i - 4);
    }
    int num = 0;
    ListDelete_Sq(List2, 1, &num);
    printf("%d\n", num);
    GetElem_Sq(List1, 3, &num);
    printf("%d\n", num);
    NextElem_Sq(List1, num, &num);
    printf("%d\n", num);
    SqList* List3 = (SqList*)malloc(sizeof(SqList));
    ListTraverse_Sq(List1, myprint);
    ListTraverse_Sq(List2, myprint);
    MergeAscendingList_Sq(List1, List2, List3);
    ListTraverse_Sq(List3, myprint);
    ClearList_Sq(List3);
    DestroyList_Sq(List1);
    DestroyList_Sq(List2);
    DestroyList_Sq(List3);
}

void difference_SL(SLinkList space) {
    int Head;
    InitList_SL(space, &Head);
    int p = Head;
    int m = 4, n = 4, temp = 0;
    // scanf("%d%d", &m, &n);
    int input1[4] = {1, 3, 4, 2};
    int input2[4] = {2, 3, 3, 5};
    // 输入A集合中的m个数, 加入静态链表
    for (int i = 0; i < m; i++) {
        // scanf("%d", &temp);
        temp = input1[i];
        ListInsert_SL(space, Head, 1, temp);
    }
    // 输入B集合中的n个数, 若A中已有则删, 没有则插入
    int find = 0;
    for (int i = 0; i < n; i++) {
        // scanf("%d", &temp);
        temp = input2[i];
        find = LocateElem_SL(space, Head, temp, Equal);
        if (find) {
            ListDelete_SL(space, Head, find, &temp);
        }
        else ListInsert_SL(space, Head, 2, temp);
    }
    ListTraverse_SL(space, Head, myprint);
}
void testSLinkList() {
    component *space = (component*)malloc(sizeof(SLinkList));
    difference_SL(space);
    free(space);
}

void testPolynomial() {
    Polynomial* P1 = NULL, *P2 = NULL;
    Data d1[4] = {{1, 2}, {3, -4}, {5, 2}, {7, 7}};
    Data d2[7] = {{1, -3}, {3, 4}, {4, -2}, {5, -2}, {6, 3}, {7, -2}, {9, 3}};
    CreatPolyn(&P1, 4, d1);
    CreatPolyn(&P2, 7, d2);
    AddPolyn(P1, P2);
    PrintPolyn(P1);
}

void testTree() {
    BiNode node10 = {10, NULL, NULL, 0, 0}, node9 = {-8, NULL, NULL, 0, 0}, node8 = {8, NULL, &node10, 0, 0};
    BiNode node7 = {7, NULL, &node9, 0, 0}, node6 = {6, &node8, NULL, 0, 0}, node5 = {5, &node6, &node7, 0, 0};
    BiNode node4 = {4, NULL, NULL, 0, 0}, node3 = {3, NULL, NULL, 0, 0}, node2 = {2, &node4, &node5, 0, 0};
    BiNode node1 = {1, &node2, &node3, 0, 0};
    BiTree root = &node1;
}

void testGraph() {
    // int inode[] = {1,1,2,3,3,4,5,5,6};
    // int jnode[] = {2,4,5,6,5,2,4,3,1};
    // AdjListGraph* GA = ALInitGraph(inode, jnode, 9);
    // ALDeleteVex(GA, 6);
    // MatGraph *GMat = MatInitGraph(inode, jnode, 9);
    // MatDeleteVex(GMat, 2);
    // OrthListGraph* GO = OrthInitGraph(inode, jnode, 9);
    // int d = OrthInDegree(GO, 6);
    // OrthDeleteVex(GO, 2);
    // int p = OrthOutDegree(GO, 4);
    int inode[] = {1,1,2,3,3,2,3,4,5,1};
    int jnode[] = {2,4,5,6,5,3,4,6,6,3};
    int weight[] = {6,5,5,4,6,5,5,2,6,1};
    int arcnum = sizeof(inode)/sizeof(int);
    MulListGraph* GMul = MLInitWithIdAndWeight(inode, jnode, weight, arcnum);
    int* path = Kruskal(GMul);
    for (int i = 0; i < GMul->vexnum - 1; i++) {
        printf("(%d,%d) ", inode[path[i] - 1], jnode[path[i] - 1]);
    }
}

void testGraphFunc() {
    int inode[] = {1,1,2,2,3,3,4,5};
    int jnode[] = {2,3,4,5,4,6,6,6};
    int weight[] = {3,2,2,3,4,3,2,1};
    // OrthListGraph* G = OrthInitWithIdAndWeight(inode, jnode, weight, 8);
    // int* path = CriticalPath(G);
    // for (int i = 1; i <= path[0] - 1; i++) {
    //     printf("%d->", path[i]);
    // }
    // printf("%d", path[path[0]]);
    AdjListGraph* G = ALInitGraph(inode, jnode, 8);
    int* seq = TopologicalSortUseDFS(G);
    for (int i = 1; i <= G->vexnum; i++) printf("%d ", seq[i]);
}

testData* randData(int x, int y, int n) {
    srand(time(0));
    testData* D = malloc(sizeof(testData));
    D->seq = malloc(n * sizeof(int));
    D->length = n;
    int key = 0;
    while (n) {
        // 高位低位拼接来产生大随机数
        key = (rand() << 15) + rand();
        key = key % (y - x + 1) + x;
        n--;
        D->seq[n] = key;
    }
    return D;
}

testData* randDataUnique(int x, int y, int n) {
    srand(time(0));
    testData* D = malloc(sizeof(testData));
    D->seq = malloc(n * sizeof(int));
    D->length = n;
    RBTree T = NULL;
    int key = 0;
    while (n) {
        // 高位低位拼接来产生大随机数
        key = (rand() << 15) + rand();
        key = key % (y - x + 1) + x;
        // 红黑树去重
        if (RB_Insert(&T, key)) {
            n--;
            D->seq[n] = key;
        }
    }
    return D;
}

void writeRandData() {
    int dataStart = 0;
    int dataEnd = INT_MAX >> 1;
    int dataNum = INT_MAX >> 6;
    testData* D = randData(dataStart, dataEnd, dataNum);
    FILE* fp = fopen("test/input.txt", "w");
    for (int i = 0; i < D->length; i++) {
        fprintf(fp, "%d ", D->seq[i]);
    }
    fclose(fp);
}

testData* readData(int n) {
    testData* D = malloc(sizeof(testData));
    D->length = 0;
    D->seq = malloc(n * sizeof(int));
    FILE* fp = fopen("test/input.txt", "r");
    while(n-- && fscanf(fp, "%d", &D->seq[D->length]) != EOF) {
        D->length++;
    }
    fclose(fp);
    return D;
}

void testBST() {
    int testTimes = 5;
    int dataStart = 0;
    int dataEnd = 1000000;
    int dataNum = 5000;
    int deleteTimes = 2000;
    FILE* fp = fopen("test/output.txt", "w+");
    testData* D = NULL;
    BSTTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randDataUnique(dataStart, dataEnd, dataNum);
        T = BST_Init(D->seq, dataNum);
        BST_addCount(T);
        quickSort(D->seq, D->length);
        for (int i = 1; i < dataNum / 2; i++) {
            if (BST_KthLess(T, i)->data != D->seq[i - 1]) {
                fprintf(fp, "%d ", D->seq[i - 1]);
            }
        }
        // for (int i = 0; i < deleteTimes; i++) {
        //     BST_Delete(&T, D->seq[i]);
        // }
        // if (!isBST(T)) {
        //     for (int i = 0; i < dataNum; i++) {
        //         fprintf(fp, "%d ", D->seq[i]);
        //     }
        //     fprintf(fp, "\n");
        // }
    }
    fclose(fp);
}

void testAVL() {
    int testTimes = 500;
    int dataStart = 0;
    int dataEnd = 1000000;
    int dataNum = 5000;
    int deleteTimes = 2000;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    AVLTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randDataUnique(dataStart, dataEnd, dataNum);
        T = AVL_Init(D->seq, dataNum);
        for (int i = 0; i < deleteTimes; i++) {
            AVL_Delete(&T, D->seq[i]);
        }
        if (!isAVL(T)) {
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
}

void testAVL_single() {
    int deleteTimes = 5;
    int data[] = {935, 709, 151, 536, 998, 606, 396, 782, 582, 117, 736, 439, 798, 801, 774, 992, 245, 353, 203, 877, 577, 255, 787, 953, 400, 731, 397, 583, 945, 691, 940, 218, 756, 586, 607, 485, 333, 264, 843, 54, 876, 673, 646, 837, 288, 418, 268, 107, 85, 133};
    AVLTree T = AVL_Init(data, 50);
    int flag = 0;
    for (int i = 0; i < deleteTimes; i++) {
        AVL_Delete(&T, data[i]);
        flag = isAVL(T);
    }
}

void testRB_single() {
    int dataNum = 20;
    int data[] = {302, 974, 541, 123, 227, 831, 41, 472, 768, 284, 847, 921, 826, 521, 273, 735, 636, 853, 829, 101};
    RBTree T = RB_Init(data, dataNum);
    for (int i = 0; i < 10; i++) {
        RB_Delete(&T, data[i]);
        if (!isRB(T)) {
            printf("%d ", data[i]);
        }
    }
}

void testRB() {
    int testTimes = 500;
    int dataStart = 0;
    int dataEnd = 1000000;
    int dataNum = 5000;
    int deleteTimes = 2000;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    RBTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randDataUnique(dataStart, dataEnd, dataNum);
        T = RB_Init(D->seq, dataNum);
        for (int i = 0; i < deleteTimes; i++) {
            RB_Delete(&T, D->seq[i]);
        }
        if (!isRB(T)) {
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
}

void testSearchFunc() {
    int dataNum = 20;
    int data[] = {302, 974, 541, 123, 227, 831, 41, 472, 768, 284, 847, 921, 826, 521, 273, 735, 636, 853, 829, 101};
    RBTree T = RB_Init(data, dataNum);
    BST_inOrder(T);
    printf("\n");
    BST_addCount(T);
    for (int i = 0; i < 20; i++) {
        printf("%d ", BST_KthLess(T, i + 1)->data);
    }
}

void testB_single() {
    int dataNum = 60;
    int data[] = {935, 709, 151, 536, 998, 900, 44, 100, 606, 396, 782, 582, 117, 736, 439, 798, 801, 774, 992, 245, 353, 600, 203, 877, 577, 255, 901, 12, 3, 8, 787, 953, 400, 731, 397, 583, 945, 691, 940, 218, 756, 586, 607, 485, 333, 264, 843, 54, 300, 301, 876, 673, 646, 837, 288, 418, 268, 107, 85, 133};
    int m = 4;
    BTree* T = B_Init(data, dataNum, m);
    B_LeOrder(T);
    for (int i = 0; i < dataNum; i++) {
        B_Delete(T, data[i]);
        B_LeOrder(T);
    }
}

void testB() {
    int testTimes = 100;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    int deleteTimes = 20;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    BTree* T = NULL;
    srand(time(0));
    for (int i = 0; i < testTimes; i++) {
        D = randDataUnique(dataStart, dataEnd, dataNum);
        T = B_Init(D->seq, dataNum, rand() % 8 + 3);
        if (!isB(T)) {
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
}

void testSearchTime(void (*func)()) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    printf("%3.3fs\n", (float)(end - start) / 1000);
}

void testSearch() {
    // testAVL();
    // testAVL_single();
    // testRB_single();
    // testRB();
    // testSearchFunc();
    // testB_single();
    // testB();
    // testSearchTime(testRB);
    testBST();
}

void testSortTime(void (*func)(int*, int), int n) {
    testData* D = readData(n);
    clock_t start = clock();
    func(D->seq, D->length);
    clock_t end = clock();
    printf("%3.3fs\n", (float)(end - start) / 1000);
}

void testSortAccuracy(void (*func)(int*, int)) {
    int testTimes = 50;
    int dataStart = 0;
    int dataEnd = INT_MAX >> 2;
    int dataNum = 100000;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    int flag = 1;
    for (int i = 0; i < testTimes; i++) {
        D = randDataUnique(dataStart, dataEnd, dataNum);
        func(D->seq, D->length);
        if (!isAscending(D->seq, D->length)) {
            flag = 0;
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
    if (flag) printf("true\n");
    else printf("false\n");
}

void testSelectAccuracy(int (*func)(int*, int, int)) {
    int testTimes = 50;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    int flag = 1;
    int k = 0, val = 0;
    for (int i = 0; i < testTimes; i++) {
        D = randData(dataStart, dataEnd, dataNum);
        k = rand() % dataNum;
        val = func(D->seq, D->length, k);
        quickSort(D->seq, D->length);
        if (D->seq[k] != val) {
            flag = 0;
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
    if (flag) printf("true\n");
    else printf("false\n");
}

void testSortFuncAccuracy() {
    int testTimes = 50;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    int flag = 1;
    for (int i = 0; i < testTimes; i++) {
        D = randData(dataStart, dataEnd, dataNum);
        heapBuild(D->seq, D->length);
        if (!isHeap(D->seq, D->length)) {
            flag = 0;
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
    if (flag) printf("true\n");
    else printf("false\n");
}

void testKMergeSortAccuracy() {
    int testTimes = 50;
    int dataStart = 0;
    int dataEnd = 100000;
    int dataNum = 1000;
    int flag = 1;
    testData* D;
    for (int i = 0; i < testTimes; i++) {
        int n = rand() % 5 + 10, total = 0;
        int* len = malloc(n * sizeof(int));
        int** L = malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            len[j] = rand() % dataNum + dataNum;
            total += len[j];
            D = randData(dataStart, dataEnd, len[j]);
            mergeSort(D->seq, D->length);
            L[j] = D->seq;
        }
        int* res = malloc(total * sizeof(int));
        kMergeSort(L, len, n, total, res);
        if (!isAscending(res, total)) flag = 0;
    }
    if (flag) printf("true\n");
    else printf("false\n");
}

void testReplaceSelectSort() {
    int testTimes = 50;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    testData* D = randData(dataStart, dataEnd, dataNum);
    int w = 10;
    int** res = malloc(w * sizeof(int*));
    for (int i = 0; i < w; i++) {
        res[i] = malloc(4 * w * sizeof(int));
    }
    int* len = calloc(w, sizeof(int));
    int r = 0;
    replaceSelectSort(D->seq, D->length, w, res, len, &r);
}

void testSort() {
    // writeRandData();
    testSortAccuracy(radixSortUseArrayOptimized);
    // testSortTime(quickSort, 30000000);
    // testSortTime(radixSortUseArrayOptimized, 30000000);
    // testSelectAccuracy(quickSelect);
    // testSortFuncAccuracy();
    // testKMergeSortAccuracy();
    // testReplaceSelectSort();
}