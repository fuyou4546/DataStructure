#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct eightNode {
    int depth;
    char str[10];
    int i0;
    int j0;
    int index;
    struct eightNode* pre;
    struct eightNode* next;
} ePNode;

char src[10] = {0};
char dst[10] = {0};
int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int isValid() {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (src[j] - '0' && src[i] - '0' && src[j] < src[i]) count++;
            if (dst[j] - '0' && dst[i] - '0' && dst[j] < dst[i]) count--;
        }
    }
    return !(count & 1);
}
int encode(char* str) {
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (str[j] < str[i]) {
                index += factorial[8 - i];
            }
        }
    }
    return index;
}
ePNode* initNode(int depth, char* str, int i0, int j0, int index, ePNode* pre) {
    ePNode* node = malloc(sizeof(ePNode));
    node->depth = depth;
    node->pre = pre;
    memcpy(node->str, str, 10 * sizeof(char));
    node->i0 = i0;
    node->j0 = j0;
    node->index = index;
    return node;
}
void printNode(ePNode* node, FILE* fp) {
    for (int i = 1; i <= 9; i++) {
        fprintf(fp, "%c", node->str[i - 1]);
        if (!(i % 3)) fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
}
void printPath(ePNode* node) {
    int depth = node->depth;
    FILE* fp = fopen("./solutions/output.txt", "w+");
    while(node) {
        printNode(node, fp);
        node = node->pre;
    }
    fprintf(fp, "depth: %d", depth);
    fclose(fp);
}
void swap(ePNode* node, int i0, int j0) {
    int i = 3 * node->i0 + node->j0;
    int j = 3 * i0 + j0;
    char temp = node->str[i];
    node->str[i] = node->str[j];
    node->str[j] = temp;
}
void bfsAddNode(ePNode** rear, ePNode* temp, char* visited, int i0, int j0) {
    swap(temp, i0, j0);
    int index = encode(temp->str);
    if (!visited[index]) {
        visited[index] = 1;
        (*rear)->next = initNode(temp->depth + 1, temp->str, i0, j0, index, temp);
        *rear = (*rear)->next;
    }
    swap(temp, i0, j0);
}
void dfsAddNode(ePNode* head, ePNode* temp, char* visited, int i0, int j0) {
    swap(temp, i0, j0);
    int index = encode(temp->str);
    if (!visited[index]) {
        visited[index] = 1;
        ePNode* node = initNode(temp->depth + 1, temp->str, i0, j0, index, temp);
        node->next = head->next;
        head->next = node;
    }
    swap(temp, i0, j0);
}
void bfsSearch() {
    ePNode* front = malloc(sizeof(ePNode)), *rear = front;
    front->next = NULL;
    char* visited = calloc(362880, sizeof(char));
    int zeroIndex = 0;
    for (int i = 0; src[i] - '0'; i++, zeroIndex++);
    ePNode* start = initNode(1, src, zeroIndex / 3, zeroIndex % 3, encode(src), NULL);
    visited[start->index] = 1;
    rear->next = start;
    rear = rear->next;
    int endIndex = encode(dst);
    ePNode* temp = NULL;
    int depth = 0;
    while (front != rear) {
        temp = front->next;
        front->next = temp->next;
        if (temp == rear) rear = front;
        if (temp->index == endIndex) {
            printPath(temp);
            free(visited);
            return;
        }
        if (temp->i0 > 0) {
            bfsAddNode(&rear, temp, visited, temp->i0 - 1, temp->j0);
        }
        if (temp->i0 < 2) {
            bfsAddNode(&rear, temp, visited, temp->i0 + 1, temp->j0);
        }
        if (temp->j0 > 0) {
            bfsAddNode(&rear, temp, visited, temp->i0, temp->j0 - 1);
        }
        if (temp->j0 < 2) {
            bfsAddNode(&rear, temp, visited, temp->i0, temp->j0 + 1);
        }
    }
    return;
}
void dfsSearch() {
    ePNode* head = malloc(sizeof(ePNode));
    head->next = NULL;
    char* visited = calloc(factorial[9], sizeof(char));
    int zeroIndex = 0;
    for (int i = 0; src[i] - '0'; i++, zeroIndex++);
    ePNode* start = initNode(1, src, zeroIndex / 3, zeroIndex % 3, encode(src), NULL);
    visited[start->index] = 1;
    head->next = start;
    int endIndex = encode(dst);
    ePNode* temp = NULL;
    int depth = 0;
    while (head->next) {
        temp = head->next;
        head->next = temp->next;
        if (temp->index == endIndex) {
            printPath(temp);
            free(visited);
            return;
        }
        if (temp->i0 > 0) {
            dfsAddNode(head, temp, visited, temp->i0 - 1, temp->j0);
        }
        if (temp->i0 < 2) {
            dfsAddNode(head, temp, visited, temp->i0 + 1, temp->j0);
        }
        if (temp->j0 > 0) {
            dfsAddNode(head, temp, visited, temp->i0, temp->j0 - 1);
        }
        if (temp->j0 < 2) {
            dfsAddNode(head, temp, visited, temp->i0, temp->j0 + 1);
        }
    }
    return;
}
void AstarSearch() {
    
}
void eightPuzzleSearch() {
    // printf("src: ");
    // scanf("%s", &dst);
    // printf("dst: ");
    // scanf("%s", &src);
    memcpy(dst, "156238047", 10 * sizeof(char));
    memcpy(src, "786450321", 10 * sizeof(char));
    if (!isValid()) {
        printf("输入不合法");
        return;
    }
    dfsSearch();
}
