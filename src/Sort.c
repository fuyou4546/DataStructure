#include "../include/Sort.h"

int isAscending(int* L, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (L[i] > L[i + 1]) return 0;
    }
    return 1;
}

void straightInsertionSort(int* L, int n) {
    int temp, i, j;
    for (i = 1; i < n; i++) {
        if (L[i] < L[i - 1]) {
            // 记录要前插的键值
            temp = L[i];
            // 将已有序部分中插入点后的键值后移
            for (j = i; j && temp < L[j - 1]; j--) {
                L[j] = L[j - 1];
            }
            // 插入
            L[j] = temp;
        }
    }
}

void binaryInsertionSort(int* L, int n) {
    int i, j, temp, left, right, mid;
    for (i = 1; i < n; i++) {
        if (L[i] < L[i - 1]) {
            temp = L[i];
            left = 0;
            right = i - 1;
            while (left <= right) {
                mid = (left + right) / 2;
                if (L[mid] > L[i]) right = mid - 1;
                else left = mid + 1;
            }
            for (j = i; j > left; j--) {
                L[j] = L[j - 1];
            }
            L[j] = temp;
        }
    }
}
