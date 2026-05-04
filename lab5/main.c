#include <stdio.h>

#include "graph.h"
#include "prim.h"

signed main(int argc, char *argv[]) {
    bool interactive = true;
    if (argc >= 2) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            printf("Не удалось считать из файла %s", argv[1]);
            return 1;
        }
        interactive = false;
    }

    if (argc >= 3) {
        if (freopen(argv[2], "w", stdout) == NULL) {
            printf("Не удалось вывести результат в файл %s", argv[2]);
            return 1;
        }
    }

    int n, m;
    if (interactive) {
        printf("Количество вершин и ребер: ");
    }
    scanf("%d %d", &n, &m);
    graph *g = NULL;
    g = initGraph(g, n);
    if (interactive) {
        printf("Введите ребра (v u w):\n");
    }
    for (int i = 0; i < m; i++) {
        int v, u, w;
        scanf("%d %d %d", &v, &u, &w);
        v--;
        u--;
        g = addEdge(g, v, u, w);
    }

    printf("Матрица смежности для графа\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g->exist[i][j]) {
                printf("%d ", g->g[i][j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    int *p = prim(g);
    if (p == NULL) {
        printf("Ошибка при построении минимального остовного дерева\n");
        return 1;
    }


    printf("Минимальное остовное дерево:\n");
    int ans = 0;
    for (int u = 0; u < n; u++) {
        if (p[u] != -1) {
            int v = p[u];
            printf("%d <--> %d (w = %d)\n", v + 1, u + 1, g->g[v][u]);
            ans += g->g[v][u];
        }
    }
    printf("Общий вес: %d\n", ans);
}
