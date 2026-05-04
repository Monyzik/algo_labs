#include <gtest/gtest.h>
#include "graph.h"
#include "prim.h"

TEST(Graph, GraphTest) {
    graph *g = nullptr;
    g = initGraph(g, 4);

    ASSERT_NE(g, nullptr);
    ASSERT_EQ(g->n, 4);

    g = addEdge(g, 0, 1, 1);
    g = addEdge(g, 2, 3, -1);

    EXPECT_TRUE(g->exist[0][1]);
    EXPECT_EQ(g->g[0][1], 1);
    EXPECT_TRUE(g->exist[1][0]);
    EXPECT_EQ(g->g[1][0], 1);

    EXPECT_TRUE(g->exist[2][3]);
    EXPECT_EQ(g->g[2][3], -1);

    EXPECT_FALSE(g->exist[1][2]);
}

TEST(Prim, PrimSimpleTriangle) {
    graph *g = nullptr;
    g = initGraph(g, 3);
    g = addEdge(g, 0, 1, 3);
    g = addEdge(g, 1, 2, 2);
    g = addEdge(g, 2, 0, 1);
    int *p = prim(g);
    int ans = 0;
    for (int v = 0; v < g->n; v++) {
        if (p[v] != -1) {
            ans += g->g[v][p[v]];
        }
    }
    EXPECT_EQ(ans, 3);
}

TEST(Prim, PrimSimpleBamboo) {
    graph *g = nullptr;
    g = initGraph(g, 4);
    g = addEdge(g, 0, 1, 1);
    g = addEdge(g, 1, 2, 2);
    g = addEdge(g, 2, 3, 3);
    int *p = prim(g);
    int ans = 0;
    for (int v = 0; v < g->n; v++) {
        if (p[v] != -1) {
            ans += g->g[v][p[v]];
        }
    }
    EXPECT_EQ(ans, 6);
}

TEST(Prim, PrimWithNegativeWeights) {
    graph *g = nullptr;
    g = initGraph(g, 4);
    g = addEdge(g, 0, 1, 2);
    g = addEdge(g, 0, 2, -1);
    g = addEdge(g, 1, 2, 3);
    g = addEdge(g, 1, 3, 4);
    g = addEdge(g, 2, 3, -2);

    int *p = prim(g);

    int ans = 0;
    for (int v = 0; v < g->n; v++) {
        if (p[v] != -1) {
            ans += g->g[v][p[v]];
        }
    }
    ASSERT_EQ(ans, -1);
}

TEST(Prim, PrimWithRandomGraph) {
    graph *g = nullptr;
    g = initGraph(g, 5);
    g = addEdge(g, 0, 1, 2);
    g = addEdge(g, 0, 3, 6);
    g = addEdge(g, 1, 2, 3);
    g = addEdge(g, 1, 3, 8);
    g = addEdge(g, 1, 4, 5);
    g = addEdge(g, 2, 4, 7);
    g = addEdge(g, 3, 4, 9);

    int *p = prim(g);

    int ans = 0;
    for (int v = 0; v < g->n; v++) {
        if (p[v] != -1) {
            ans += g->g[v][p[v]];
        }
    }
    ASSERT_EQ(ans, 16);
}
