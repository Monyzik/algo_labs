#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


graph *initGraph(graph *g, const int n) {
    g = malloc(sizeof(graph));
    g->n = n;
    g->g = malloc(sizeof(int *) * n);
    g->exist = malloc(sizeof(int *) * n);
    if (g->g == NULL || g->exist == NULL) {
        printf("Не удалось выделить память\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        g->exist[i] = malloc(sizeof(int) * n);
        g->g[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            g->exist[i][j] = false;
        }
    }
    return g;
}

graph *addEdge(graph *g, const int v, const int u, const int w) {
    g->exist[u][v] = true;
    g->exist[v][u] = true;
    g->g[u][v] = w;
    g->g[v][u] = w;
    return g;
}

void freeGraph(graph *g) {
    for (int i = 0; i < g->n; i++) {
        free(g->g[i]);
    }
    free(g->g);
    g->g = NULL;
    g->n = 0;
}
