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
    int incr = 1, temp, j;
    while (incr < n) incr = (incr << 1) + 1;
    while (incr >>= 1) {
        for (int i = incr; i < n; i++) {
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
void qSort(int* L, int left, int right) {
    if (left >= right) return;
    int pivotpos = partition(L, left, right);
    qSort(L, left, pivotpos - 1);
    qSort(L, pivotpos + 1, right);
}
void quickSort(int* L, int n) {
    srand(time(0));
    qSort(L, 0, n - 1);
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
    L[0] = L[k];
    for (int i = 2 * k; i <= n; i *= 2) {
        if (i < n && L[i] < L[i + 1]) i++;
        if (L[0] >= L[i]) break;
        L[k] = L[i];
        k = i;
    }
    L[k] = L[0];
}
void heapBuild(int* L, int n) {
    for (int i = n / 2; i > 0; i--) {
        heapAdjust(L, i, n);
    }
}
void heapSort(int* L, int n) {
    // 自底向上建大顶堆
    heapBuild(L, n);
    // 依次将堆顶元素与堆底元素交换, 调整除堆底的剩余堆
    for (int i = n; i > 1; i--) {
        L[0] = L[i];
        L[i] = L[1];
        L[1] = L[0];
        heapAdjust(L, 1, i - 1);
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
void radixSortUseLink(int* L, int n) {
    int radix = 1000;
    // 将列表转为链表
    rSLink* head = calloc(1, sizeof(rSLink));
    rSLink* front[1000] = { 0 }, *rear[1000] = { 0 };
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
            k = p->data % radix;
            if (!front[k]) {
                front[k] = rear[k] = p;
            }
            else {
                rear[k]->next = p;
                rear[k] = p;
            }
            if (p->data) {
                p->data /= radix;
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
        for (int j = i + 1; j < radix; j++) {
            if (!front[j]) continue;
            rear[i]->next = front[j];
            front[i] = rear[i] = NULL;
            i = j;
        }
        front[i] = rear[i] = NULL;
    }
}

void radixSortUseArray(int* L, int n) {
    int radix = 1000;
    // 获取最多趟数
    int maxKey = INT_MIN, d = 1;
    for (int i = 0; i < n; i++) {
        if (L[i] > maxKey) maxKey = L[i];
    }
    while (maxKey /= radix) d++;
    // count统计一趟分配后各桶中键值数
    int* count = malloc(radix * sizeof(int));
    // temp暂存一趟收集后的序列
    int* temp = malloc(n * sizeof(int));
    // base
    int base = 1, k = 0;
    for (int i = 0; i < d; i++) {
        // 初始化count为0
        memset(count, 0, radix * sizeof(int));
        // 分配
        for (int j = 0; j < n; j++) {
            k = (L[j] / base) % radix;
            count[k]++;
        }
        // 累加以确定各桶在temp中的末位置
        for (int j = 1; j < radix; j++) {
            count[j] += count[j - 1]; 
        }
        // 收集
        for (int j = n - 1; j >= 0; j--) {
            k = (L[j] / base) % radix;
            temp[count[k] - 1] = L[j];
            count[k]--;
        }
        memcpy(L, temp, n * sizeof(int));
        base *= radix;
    }
    free(count);
    free(temp);
}

void radixSortUseArrayOptimized(int* L, int n) {
    int radix = 2 << 8;
    // p[i]表示右移的位数
    int p[] = {0, 8, 16, 24};
    // 最多4躺, 因INT_MAX实际最多31位, 一趟移8位
    int d = 4;
    int* count = malloc(radix * sizeof(int));
    int* temp = malloc(n * sizeof(int));
    int k = 0;
    for (int i = 0; i < d; i++) {
        memset(count, 0, radix * sizeof(int));
        for (int j = 0; j < n; j++) {
            // 
            k = L[j] >> p[i] & (radix - 1);
            count[k]++;
        }
        for (int j = 1; j < radix; j++) {
            count[j] += count[j - 1]; 
        }
        for (int j = n - 1; j >= 0; j--) {
            k = L[j] >> p[i] & (radix - 1);
            temp[count[k] - 1] = L[j];
            count[k]--;
        }
        memcpy(L, temp, n * sizeof(int));
    }
    free(count);
    free(temp);
}

void bidiBubbleSort(int* L, int n) {
    int left = 0, right = n - 1, flag = 0, temp;
    while (left < right) {
        for (int i = left; i < right; i++) {
            if (L[i] > L[i + 1]) {
                temp = L[i];
                L[i] = L[i + 1];
                L[i + 1] = temp;
                flag = 1;
            }
        }
        if (!flag) return;
        flag = 0;
        right--;
        for (int i = right; i > left; i--) {
            if (L[i] < L[i - 1]) {
                temp = L[i];
                L[i] = L[i - 1];
                L[i - 1] = temp;
                flag = 1;
            }
        }
        if (!flag) return;
        flag = 0;
        left++;
    }
}

void moveOddBeforeEven(int* L, int n) {
    int i = 0, j = n - 1, temp;
    while (i < j) {
        while (i < j && L[i] & 1) i++;
        while (i < j && !(L[j] & 1)) j--;
        if (i < j) {
            temp = L[i];
            L[i] = L[j];
            L[j] = temp;
            i++;
            j--;
        }
    }
}

int qSelect(int* L, int left, int right, int k) {
    if (left >= right) return left;
    int pos = partition(L, left, right);
    if (pos == k) return L[k];
    if (pos > k) return qSelect(L, left, pos - 1, k);
    return qSelect(L, pos + 1, right, k);
}
int quickSelect(int* L, int n, int k) {
    srand(time(0));
    return qSelect(L, 0, n - 1, k);
}

void colorPartition(int* L, int n) {
    // left左侧全1, right右侧全3
    int left = 0, cur = 0, right = n - 1, temp;
    // 此处要包含等于, 因为right处可能是1
    while (cur <= right) {
        // 此处直接增加cur, 因为不可能将
        if (L[cur] == 1) {
            temp = L[cur];
            L[cur] = L[left];
            L[left] = temp;
            left++;
            cur++;
        }
        else if (L[cur] == 2) {
            cur++;
        }
        // 此处不增加cur, 因为可能会将3交换过来
        else {
            temp = L[cur];
            L[cur] = L[right];
            L[right] = temp;
            right--;
        }
    }
}

void setP(int* L, int mid, int left, int right) {
    if (left >= right) return;
    int pos = partition(L, left, right);
    if (pos == mid) return;
    if (pos > mid) setP(L, mid, left, pos - 1);
    setP(L, mid, pos + 1, right);
}
int setPartition(int* L, int n) {
    int mid = n / 2, res = 0;
    setP(L, mid, 0, n - 1);
    for (int i = n - 1; i >= mid; i--) res += L[i];
    for (int i = 0; i < mid; i++) res -= L[i];
    return res;
}

int setPartition2(int* L, int n) {
    int left = 0, right = n - 1, pivotpos = 0, mid = n / 2, res = 0;
    while (1) {
        pivotpos = partition(L, left, right);
        if (pivotpos == mid) break;
        if (pivotpos > mid) {
            right = pivotpos - 1;
        }
        else {
            left = pivotpos + 1;
        }
    }
    for (int i = n - 1; i >= mid; i--) res += L[i];
    for (int i = 0; i < mid; i++) res -= L[i];
    return res;
}

void selectSortLinkList(LinkList* L) {
    Link* head = L->head;
    Link* p, *pre, *mark, *mpre, *tail = head;
    while (tail->next) {
        p = mark = tail->next;
        pre = mpre = tail;
        while (p) {
            if (p->key < mark->key) {
                mark = p;
                mpre = pre;
            }
            pre = p;
            p = p->next;
        }
        mpre->next = mark->next;
        mark->next = tail->next;
        tail->next = mark;
        tail = mark;
    }
}

int isHeap(int* L, int n) {
    int k = 0;
    for (int i = 1; i <= n / 2; i++) {
        k = i << 1;
        if (k <= n && L[i - 1] < L[k - 1] ||
                k + 1 <= n && L[i - 1] < L[k]) {
            return 0;
        }    
    }
    return 1;
}

void countSort(int* L, int n) {
    int* S = malloc(n * sizeof(int));
    int count = 0;
    for (int i = 0; i < n; i++) {
        count = 0;
        for (int j = 0; j < n; j++) {
            if (L[j] < L[i]) count++;
        }
        S[count] = L[i];
    }
    for (int i = 0; i < n; i++) L[i] = S[i];
    free(S);
}

void loserTreeAdjust(int* leaf, int* loser, int k, int n) {
    int temp;
    // k一直是胜者的位置
    for (int i = (k + n) / 2; i > 0; i /= 2) {
        // 如果插入导致败者变化, 更新败者, k为新胜者位置
        if (leaf[k] > leaf[loser[i]]) {
            temp = k;
            k = loser[i];
            loser[i] = temp;
        }
    }
    loser[0] = k;
}
void loserTreeBuild(int** L, int n, int* leaf, int* loser) {
    // 设置虚拟最小值
    leaf[n] = INT_MIN;
    // 败者初始化为虚拟最小值坐标, 叶结点取各表首元
    for (int i = 0; i < n; i++) {
        loser[i] = n;
        leaf[i] = L[i][0];
    }
    // 自底向上调整
    for (int i = n - 1; i >= 0; i--) {
        loserTreeAdjust(leaf, loser, i, n);
    }
}
void kMergeSort(int** L, int* len, int r, int total, int* res) {
    int* cur = calloc(r, sizeof(int));
    int* loser = malloc(r * sizeof(int));
    int* leaf = malloc((r + 1) * sizeof(int));
    loserTreeBuild(L, r, leaf, loser);
    int index = 0, count = 0;
    // 依次将每轮胜者所在表的游标后移, 在原胜者位置插入该表新首元, 再调整该位置
    while (count < total) {
        index = loser[0];
        res[count++] = L[index][cur[index]++];
        if (cur[index] < len[index]) {
            leaf[index] = L[index][cur[index]];
        }
        else leaf[index] = INT_MAX;
        loserTreeAdjust(leaf, loser, index, r);
    }
    free(cur);
    free(loser);
    free(leaf);
}


void loserTreeAdjustWithSeg(int* leaf, int* loser, int k, int w, int* seg) {
    int temp;
    for (int i = (k + w) / 2, j = loser[i]; i > 0; i /= 2, j = loser[i]) {
        // 段号小者或段号相同键值小者为胜
        if (seg[k] > seg[j] || seg[k] == seg[j] && leaf[k] > leaf[j]) {
            temp = k;
            k = j;
            loser[i] = temp;
        }
    }
    loser[0] = k;
}
void replaceSelectSort(int* L, int n, int w, int** res, int* len, int* r) {
    int* loser = malloc(w * sizeof(int));
    int* leaf = malloc((w + 1) * sizeof(int));
    int* seg = calloc(w, sizeof(int));
    leaf[w] = INT_MIN;
    int cur = 0;
    for (cur; cur < w; cur++) {
        loser[cur] = w;
        leaf[cur] = L[cur];
    }
    int minimax = INT_MIN;
    for (int i = w - 1; i >= 0; i--) {
        loserTreeAdjustWithSeg(leaf, loser, i, w, seg);
    }
    int index = 0, count = 0;
    while (count < n) {
        index = loser[0];
        minimax = leaf[index];
        // 按段分配
        res[seg[index]][len[seg[index]]++] = minimax;
        // 若新加入败者树的键值小于minimax, 将其划分到下一段
        if (L[cur] < minimax) {
            seg[index]++;
            if (seg[index] > *r) *r = seg[index];
        }
        count++;
        if (cur < n) leaf[index] = L[cur++];
        else leaf[index] = INT_MAX;
        loserTreeAdjustWithSeg(leaf, loser, index, w, seg);
    }
}
