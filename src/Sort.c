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

void shellSort(int* L, int n) {
    int incr = 1, temp, i, j;
    while (incr < n) incr = (incr << 1) + 1;
    incr >>= 1;
    for (; incr; incr >>= 1) {
        for (i = incr; i < n; i++) {
            if (L[i] < L[i - incr]) {
                temp = L[i];
                for (j = i; j >= incr && temp < L[j - incr]; j -= incr) {
                    L[j] = L[j - incr];
                }
                L[j] = temp;
            }
        }
    }
}

void bubbleSort(int* L, int n) {
    // flag 标记一趟遍历是否交换, 未发生交换说明已排好序
    int temp, flag = 0;
    for (int i = 0; i < n - 1; i++) {
        flag = 0;
        for (int j = n - 1; j > i; j--) {
            if (L[j] < L[j - 1]) {
                flag = 1;
                temp = L[j];
                L[j] = L[j - 1];
                L[j - 1] = temp;
            }
        }
        if (!flag) return;
    }
}

int partition(int* L, int left, int right) {
    // 随机取基准, 与低位交换
    int pivotpos = rand() % (right - left + 1) + left;
    int pivot = L[pivotpos];
    L[pivotpos] = L[left];
    L[left] = pivot;
    // 遍历将L划分为两部分
    while (left < right) {
        // 从高到低找第一个比基准小的键值, 与低位交换
        while (left < right && L[right] >= pivot) right--;
        L[left] = L[right];
        // 从低到高找第一个比基准大的键值, 与高位交换
        while (left < right && L[left] <= pivot) left++;
        L[right] = L[left];
    }
    // 低位高位重合处为基准的正序位置
    L[left] = pivot;
    return left;
}
void qS(int* L, int left, int right) {
    if (left >= right) return;
    int pivotpos = partition(L, left, right);
    qS(L, left, pivotpos - 1);
    qS(L, pivotpos + 1, right);
}
void quickSort(int* L, int n) {
    srand(time(0));
    qS(L, 0, n - 1);
}

void selectSort(int* L, int n) {
    int cur = 0, temp = 0;
    for (int i = 0; i < n - 1; i++) {
        cur = i;
        for (int j = i + 1; j < n; j++) {
            if (L[j] < L[cur]) cur = j; 
        }
        temp = L[i];
        L[i] = L[cur];
        L[cur] = temp;
    }
}

// 调整堆的第k个元素
void heapAdjust(int* L, int k, int n) {
    int temp = L[k - 1];
    for (int i = 2 * k; i <= n; i *= 2) {
        if (i < n && L[i - 1] < L[i]) i++;
        if (temp >= L[i - 1]) break;
        L[k - 1] = L[i - 1];
        k = i;
    }
    L[k - 1] = temp;
}
void heapSort(int* L, int n) {
    // 自底向上建大顶堆
    for (int i = n / 2; i > 0; i--) {
        heapAdjust(L, i, n);
    }
    int temp;
    // 依次将堆顶元素与堆底元素交换, 调整除堆底的剩余堆
    for (int i = n - 1; i > 0; i--) {
        temp = L[i];
        L[i] = L[0];
        L[0] = temp;
        heapAdjust(L, 1, i);
    }
}

void merge(int* L, int* S, int left, int mid, int right) {
    for (int i = left; i <= right; i++) S[i] = L[i];
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (S[i] < S[j]) L[k++] = S[i++];
        else L[k++] = S[j++];
    }
    while (i <= mid) L[k++] = S[i++];
    while (j <= right) L[k++] = S[j++];
}
void mS(int* L, int* S, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mS(L, S, left, mid);
    mS(L, S, mid + 1, right);
    merge(L, S, left, mid, right);
}
void mergeSort(int* L, int n) {
    int* S = malloc(n * sizeof(int));
    mS(L, S, 0, n - 1);
    free(S);
}

typedef struct rSLink {
    int key;
    int data;
    struct rSLink* next;
} rSLink;
void radixSort(int* L, int n) {
    // 将列表转为链表
    rSLink* head = calloc(1, sizeof(rSLink));
    rSLink *front[10] = { 0 }, *rear[10] = { 0 };
    for (int i = 0; i < n; i++) {
        rSLink* node = malloc(sizeof(rSLink));
        node->key = node->data = L[i];
        node->next = head->next;
        head->next = node;
    }
    int k, flag;
    rSLink* p = head->next, *q = NULL;
    while (1) {
        flag = 0;
        // 入队
        while (p) {
            q = p->next;
            p->next = NULL;
            k = p->data % 10;
            if (!front[k]) {
                front[k] = rear[k] = p;
            }
            else {
                rear[k]->next = p;
                rear[k] = p;
            }
            if (p->data) {
                p->data /= 10;
                flag = 1;
            }
            p = q;
        }
        // 各基数遍历完全, 所有元素会按序存在首队列中
        if (!flag) {
            p = front[0];
            for (int i = 0; i < n; i++, p = p->next) {
                L[i] = p->key;
            }
            return;
        }
        // 将各队列中元素首尾相连, 并将队列置空
        int i;
        for (i = 0; i < n; i++) {
            if (front[i]) break;
        }
        p = front[i];
        for (int j = i + 1; j < 10; j++) {
            if (!front[j]) continue;
            rear[i]->next = front[j];
            front[i] = rear[i] = NULL;
            i = j;
        }
        front[i] = rear[i] = NULL;
    }
}
