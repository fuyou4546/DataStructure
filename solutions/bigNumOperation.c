#include <stdio.h>
#include <string.h>

char* bigAdd(char* num1, char* num2) {
    int len1 = strlen(num1), len2 = strlen(num2);
    int len = len1 > len2 ? len1 : len2;
    char* sum = calloc(len + 2, sizeof(char));
    int cur = 0, cur1 = len1 - 1, cur2 = len2 - 1, up = 0, temp = 0;
    int x = 0, y = 0;
    while (cur1 >= 0 || cur2 >= 0) {
        x = cur1 >= 0 ? num1[cur1--] - '0' : 0;
        y = cur2 >= 0 ? num2[cur2--] - '0' : 0;
        temp = x + y + up;
        sum[cur++] = temp % 10 + '0';
        up = temp / 10;
    }
    if (up) sum[cur++] = up + '0';
    for (int i = 0; i < cur / 2; i++) {
        temp = sum[i];
        sum[i] = sum[cur - i - 1];
        sum[cur - i - 1] = temp;
    }
    return sum;
}
