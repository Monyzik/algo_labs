#include "algorithms.c"
#include "readFile.c"


typedef int keyType;


signed main() {
    int n;
    keyType *keys;
    char **strings;

    readFile("random.txt", &n, &keys, &strings);

    printf("Исходная таблица:\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %s\n", keys[i], strings[i]);
    }
    printf("\n");
    shakerSort(n, &keys, &strings);
    printf("Отсортированная таблица:\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %s\n", keys[i], strings[i]);
    }
    printf("\n");


    int choice;

    do {
        printf("1. Поиск элемента в таблице по ключу\n");
        printf("0. Выход\n");
        printf("Действие: ");
        if (scanf("%d", &choice) != 1) {
            printf("Неправильный формат ввода\n");
            // while (getchar() != '\n') {}
            return 0;
        }
        keyType x;
        switch (choice) {
            case 1:
                printf("Введите ключ: ");
                if (scanf("%d", &x) != 1) {
                    printf("Неправильный формат ввода\n");
                    continue;
                }
                char *finded = binarySearch(n, keys, strings, x);
                if (finded == NULL) {
                    printf("Данный элемент не найден.\n");
                } else {
                    printf("%s\n", finded);
                }
                break;
            case 0:
                break;
            default:
                printf("Неизвестная команда.\n");
                break;
        }
    } while (choice);

    freeMemory(n, keys, strings);
    return 0;
}
