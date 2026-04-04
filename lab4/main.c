#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

signed main(int argc, char *argv[]) {
    bool ok = false;
    if (argc == 3) {
        ok = true;
        if (!freopen(argv[1], "r", stdin)) {
            printf("Не удалось открыть файл %s", argv[1]);
            return 0;
        }

        if (!freopen(argv[2], "w", stdout)) {
            printf("Не удалось открыть файл %s", argv[2]);
            return 0;
        }
    }

    node *t = NULL;
    char *line = NULL, *error = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        // printf("Доступные команды:\n");
        // printf("1. Добавление значение по ключу\n");
        // printf("2. Удаление узла по ключу\n");
        // printf("3. Выведение дерева\n");
        // printf("4. Нахождение значения по ключу\n");
        // printf("Ввод: ");

        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        if (ok) printf("%s\n", line);

        if (strcmp(line, "-1") == 0) break;
        if (line[0] == '\0') continue;


        char *token = strtok(line, " ");
        if (!token) {
            continue;
        }
        int operation = strtol(token, &error, 10);
        if (*error) {
            printf("Не получилось преобразовать в число %s\n", error);
            continue;
        }
        char *key;
        float value;
        if (operation == 1) {
            key = strtok(NULL, " ");
            if (!key) {
                printf("Неправильная команда\n");
                continue;
            }
            token = strtok(NULL, " ");
            if (!token) {
                printf("Неправильная команда\n");
                continue;
            }
            value = strtof(token, &error);
            if (*error) {
                printf("Не получилось преобразовать в число %s\n", error);
                continue;
            }
            t = insert(t, key, value);
        } else if (operation == 2) {
            key = strtok(NULL, " ");
            t = erase(t, key);
        } else if (operation == 3) {
            print(t, 0);
        } else if (operation == 4) {
            key = strtok(NULL, " ");
            float *finded = find(t, key);
            if (finded == NULL) {
                printf("Значение не найдено\n");
                continue;
            }
            printf("Значение: %.4f\n", *finded);
        }
    }

    free(line);
    clearTree(t);
    return 0;
}
