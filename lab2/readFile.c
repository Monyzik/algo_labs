#include <stdlib.h>
#include <stdio.h>

typedef int keyType;

char *readLine(FILE *file) {
    int capacity = 32, length = 0;
    char *str = malloc(capacity * sizeof(char));
    if (!str) {
        printf("Ошибка выделения памяти\n");
        free(str);
        return NULL;
    }
    char c;

    while ((c = fgetc(file)) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            capacity = capacity * 2;
            char *newStr = realloc(str, capacity * sizeof(char));
            if (!newStr) {
                printf("Ошибка выделения памяти\n");
                free(str);
                return NULL;
            }
            str = newStr;
        }

        str[length++] = c;
    }

    if (length + 1 >= capacity) {
        char *newStr = realloc(str, (length + 1) * sizeof(char));
        if (!newStr) {
            free(str);
            return NULL;
        }
        str = newStr;
    }
    str[length] = '\0';


    return str;
}

void freeMemory(int n, keyType *keys, char **strings) {
    if (strings)
        for (int i = 0; i < n; i++) {
            free(strings[i]);
        }
    free(strings);
    free(keys);
}

void initTable(int n, int **keys, char ***strings) {
    *keys = malloc(n * sizeof(keyType));
    *strings = malloc(n * sizeof(char *));
    if (*keys == NULL || *strings == NULL) {
        printf("Ошибка выделения памяти\n");
        freeMemory(n, *keys, *strings);
        exit(0);
    }
}

void readFile(const char *fileName, int *n, keyType **keys, char ***strings) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Не удалось открыть файл\n");
        exit(0);
    }
    fscanf(file, "%d", n);


    initTable(*n, keys, strings);

    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%d ", &(*keys)[i]) != 1) {
            printf("Ошибка чтения из файла ключа");
            fclose(file);
            return;
        }


        (*strings)[i] = readLine(file);
        if ((*strings)[i] == NULL) {
            printf("Ошибка выделения памяти\n");
            freeMemory(*n, *keys, *strings);
            exit(0);
        }
    }
    fclose(file);
}
