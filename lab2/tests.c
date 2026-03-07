#include "readFile.c"
#include "algorithms.c"
#include <assert.h>
#include <string.h>


void testSortOfRandomTable() {
    int n;
    keyType *keys;
    char **strings;
    readFile("random.txt", &n, &keys, &strings);
    shakerSort(n, &keys, &strings);
    for (int i = 0; i < n - 1; i++) {
        assert(keys[i] <= keys[i + 1]);
    }
    printf("OK\n");
    freeMemory(n, keys, strings);
}

void testSortOfReverseSortedTable() {
    int n;
    keyType *keys;
    char **strings;
    readFile("reverse_sorted.txt", &n, &keys, &strings);
    shakerSort(n, &keys, &strings);
    for (int i = 0; i < n - 1; i++) {
        assert(keys[i] <= keys[i + 1]);
    }
    printf("OK\n");
    freeMemory(n, keys, strings);
}

void testSortOfSortedTable() {
    int n;
    keyType *keys;
    char **strings;
    readFile("sorted.txt", &n, &keys, &strings);
    shakerSort(n, &keys, &strings);
    for (int i = 0; i < n - 1; i++) {
        assert(keys[i] <= keys[i + 1]);
    }
    printf("OK\n");
    freeMemory(n, keys, strings);
}


void testBinarySearch() {
    int n;
    keyType *keys;
    char **strings;
    readFile("sorted.txt", &n, &keys, &strings);
    for (int i = 0; i < n; i++) {
        assert(strcmp(binarySearch(n, keys, strings, keys[i]), strings[i]) == 0);
    }
    assert(binarySearch(n, keys, strings, 1000000000) == NULL);
    printf("OK\n");
}

void testCombinedFunctions() {
    int n;
    keyType *keys;
    char **strings;
    readFile("random.txt", &n, &keys, &strings);
    for (int i = 0; i < 10; i++) {
        int j = rand() % n, k = rand() % n;
        swapKeys(&keys[j], &keys[k]);
        swapStrings(&strings[j], &strings[k]);
    }
    shakerSort(n, &keys, &strings);
    for (int i = 0; i < n - 1; i++) {
        assert(keys[i] <= keys[i + 1]);
        assert(strcmp(binarySearch(n, keys, strings, keys[i]), strings[i]) == 0);
    }
    printf("OK\n");
    freeMemory(n, keys, strings);
}

signed main() {
    printf("Тестирование сортировки рандомной таблицы:\n");
    testSortOfRandomTable();
    printf("Тестирование сортировки обратной таблицы:\n");
    testSortOfReverseSortedTable();
    printf("Тестирование сортировки отсортированной таблицы:\n");
    testSortOfSortedTable();
    printf("Тестирование бинарного поиска:\n");
    testBinarySearch();
    printf("Тестирование сортировки с бинарным поиском:\n");
    testCombinedFunctions();
}
