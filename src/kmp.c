#include "../include/kmp.h"

void getNext(char* p, int* next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (p[i + 1]) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
}

void getNextval(char* p, int* next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (p[i + 1]) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            if (p[i] != p[j]) next[i] = j;
            else next[i] = next[j];
        }
        else j = next[j];
    }
}

int* getIndex(char* s, char* p) {
    int* next = malloc(strlen(p) * sizeof(int));
    int* mark = malloc(strlen(s) * sizeof(int));
    getNextval(p, next);
    int i = 0, j = 0, count = 0;
    while (s[i]) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
            if (!p[j]) {
                printf("%d\n", i - j);
                mark[++count] = i - j;
                i -= j - 1;
                j = 0;
            }
        }
        else j = next[j];
    }
    free(next);
    mark[0] = count;
    return mark;
}