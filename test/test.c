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
    int inode[] = {1,1,2,3,3,4,5,5,6};
    int jnode[] = {2,4,5,6,5,2,4,3,1};
    AdjListGraph* GA = ALInitGraph(inode, jnode, 9);
    ALDeleteVex(GA, 2);
    MatGraph *GMat = MatInitGraph(inode, jnode, 9);
    MatDeleteVex(GMat, 2);
    OrthListGraph* GO = OrthInitGraph(inode, jnode, 9);
    int d = OrthInDegree(GO, 6);
    OrthDeleteVex(GO, 2);
    int p = OrthOutDegree(GO, 4);
    MulListGraph* GMul = MLInitGraph(inode, jnode, 9);
    MLDeleteVex(GMul, 5);
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
    testData* D = malloc(sizeof(testData));
    D->seq = malloc(n * sizeof(int));
    D->length = n;
    AVLTree T = NULL;
    int key = 0;
    Sleep(10);
    srand(time(0));
    while (n) {
        key = rand() % (y - x + 1) + x;
        if (!AVL_Search(T, key)) {
            AVL_Insert(&T, key);
            n--;
            D->seq[n] = key;
        }
    }
    return D;
}

void testBST() {
    int testTimes = 500;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 50;
    int deleteTimes = 10;
    FILE* fp = fopen("test/output.txt", "w+");
    testData* D = NULL;
    BSTTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randData(dataStart, dataEnd, dataNum);
        T = BST_Init(D->seq, dataNum);
        for (int i = 0; i < deleteTimes; i++) {
            BST_Delete(&T, D->seq[i]);
        }
        if (!isBST(T)) {
            for (int i = 0; i < dataNum; i++) {
                fprintf(fp, "%d ", D->seq[i]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void testAVL() {
    int testTimes = 200;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    int deleteTimes = 40;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    AVLTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randData(dataStart, dataEnd, dataNum);
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
    int data[] = {245, 622, 83, 143, 213, 179, 527, 127, 404, 43, 125, 616, 507, 851, 463, 992, 366, 520, 646, 795};
    RBTree T = RB_Init(data, dataNum);
    int flag = isRB(T);
}

void testRB() {
    int testTimes = 500;
    int dataStart = 0;
    int dataEnd = 1000;
    int dataNum = 100;
    int deleteTimes = 20;
    FILE* fp = fopen("test/output.txt", "w");
    testData* D = NULL;
    RBTree T = NULL;
    for (int i = 0; i < testTimes; i++) {
        D = randData(dataStart, dataEnd, dataNum);
        T = RB_Init(D->seq, dataNum);
        if (!isRB(T)) {
            for (int i = 0; i < dataNum - 1; i++) {
                fprintf(fp, "%d, ", D->seq[i]);
            }
            fprintf(fp, "%d\n", D->seq[dataNum - 1]);
        }
    }
    fclose(fp);
}

void testSearch() {
    //testAVL();
    //testAVL_single();
    //testRB_single();
    testRB();
}
