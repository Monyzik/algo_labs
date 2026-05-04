#ifndef ALGO_LABS_GRAPH_H
#define ALGO_LABS_GRAPH_H

#ifdef __cplusplus
extern "C" {

#endif

#include <stdbool.h>

typedef struct graph {
    int n;
    int **g;
    bool **exist;
} graph;

graph *initGraph(graph *g, int n);

graph *addEdge(graph *g, int v, int u, int w);

#ifdef __cplusplus
}
#endif

#endif
