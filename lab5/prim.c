#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree.h"
#include "graph.h"

#define INF (INT_MAX / 2)

int *prim(graph *g) {
    int n = g->n;
    bool used[n];
    int keys[n];
    int *p = malloc(sizeof(int) * n);
    node *t = NULL;
    for (int v = 0; v < n; v++) {
        keys[v] = INF;
        used[v] = false;
        p[v] = -1;
    }

    keys[0] = 0;
    t = insert(t, 0, 0);
    int cnt = 0;
    while (t && cnt < n) {
        node *minNode = findMin(t);
        if (minNode == NULL) break;
        int u = minNode->value;
        t = erase(t, minNode->key);
        if (used[u]) continue;
        used[u] = true;
        cnt++;

        for (int v = 0; v < n; v++) {
            int w = g->g[u][v];
            if (g->exist[v][u] && !used[v] && w < keys[v]) {
                if (keys[v] != INF) {
                    t = erase(t, keys[v]);
                }
                keys[v] = w;
                p[v] = u;
                t = insert(t, w, v);
            }
        }
    }
    return p;
}
