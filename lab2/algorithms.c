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
    int *_keyes = *keys;
    char **_strings = *strings;
    int l = 0, r = n - 1;
    while (l < r) {
        for (int i = l; i < r; i++) {
            if (_keyes[i] > _keyes[i + 1]) {
                swapKeys(&_keyes[i], &_keyes[i + 1]);
                swapStrings(&_strings[i], &_strings[i + 1]);
            }
        }
        r--;
        for (int i = r; i > l; i--) {
            if (_keyes[i - 1] > _keyes[i]) {
                swapKeys(&_keyes[i - 1], &_keyes[i]);
                swapStrings(&_strings[i - 1], &_strings[i]);
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
