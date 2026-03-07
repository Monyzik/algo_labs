#include <stdio.h>

typedef int keyType;

void swapKeys(keyType *a, keyType *b) {
    keyType tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapStrings(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void shakerSort(int n, int **keys, char ***strings) {
    int l = 0, r = n - 1;
    while (l < r) {
        for (int i = l; i < r; i++) {
            if ((*keys)[i] > (*keys)[i + 1]) {
                swapKeys(&(*keys)[i], &(*keys)[i + 1]);
                swapStrings(&(*strings)[i], &(*strings)[i + 1]);
            }
        }
        r--;
        for (int i = r; i > l; i--) {
            if ((*keys)[i - 1] > (*keys)[i]) {
                swapKeys(&(*keys)[i - 1], &(*keys)[i]);
                swapStrings(&(*strings)[i - 1], &(*strings)[i]);
            }
        }
        l++;
    }
}


char *binarySearch(int n, keyType *keys, char **strings, keyType x) {
    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (x < keys[m]) {
            r = m;
        } else {
            l = m;
        }
    }
    if (keys[l] != x) {
        return NULL;
    }
    return strings[l];
}
