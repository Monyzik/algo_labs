#include "tree.c"

signed main() {
    node *tree = NULL;

    int choice, value;

    printf("1. Добавить узел\n");
    printf("2. Удалить узел\n");
    printf("3. Вывести дерево\n");
    printf("4. Проверить, все ли листья на одном уровне\n");
    printf("0. Выход\n");
    printf("Выбор: ");
    scanf("%d", &choice);

    while (choice != 0) {
        switch (choice) {
            case 1:
                printf("Введите значение:\n");
                scanf("%d", &value);
                tree = insert(tree, value);
                break;
            case 2:
                printf("Введите значение:\n");
                scanf("%d", &value);
                tree = erase(tree, value);
                break;
            case 3:
                print(tree, 0);
                break;
            case 4:
                printf("%d\n", query(tree, 1, depth(tree)));
                break;
        }
        printf("Выбор: ");
        scanf("%d", &choice);
    }
}
