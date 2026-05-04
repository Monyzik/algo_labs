#include <benchmark/benchmark.h>
#include <bits/stdc++.h>

#include "prim.h"

using namespace std;

random_device rd;
mt19937 rng(rd());

int generateInt(int l, int r) {
    return uniform_int_distribution(l, r)(rng);
}

vector<vector<int> > generateGraph(int n, int m) {
    int totalPossible = n * (n - 1) / 2;
    if (m > totalPossible) m = totalPossible;
    vector g(n, vector<int>(n, 0));
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), rng);
    for (int i = 1; i < n; ++i) {
        int u = order[i - 1], v = order[i];
        int w = generateInt(1, 100);
        g[u][v] = g[v][u] = w;
    }
    int added = n - 1;
    vector<pair<int, int> > candidates;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (g[i][j] == 0)
                candidates.emplace_back(i, j);
    shuffle(candidates.begin(), candidates.end(), rng);
    int need = m - added;
    need = min(need, (int) candidates.size());
    for (int k = 0; k < need; ++k) {
        auto [u,v] = candidates[k];
        g[u][v] = g[v][u] = generateInt(1, 100);
    }
    return g;
}

void MyPrimeBenchmark(benchmark::State &state) {
    int n = state.range(0);
    int m = n * 4;

    auto ng = generateGraph(n, m);
    graph *g = nullptr;
    g = initGraph(g, n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            g = addEdge(g, i, j, ng[i][j]);
        }
    }

    for (auto _: state) {
        int *p = prim(g);
        benchmark::DoNotOptimize(p);
    }
    state.SetComplexityN(m);
}

BENCHMARK(MyPrimeBenchmark)->RangeMultiplier(10)->Range(100, 10000)->Complexity();

void PrimeWithPQBenchmark(benchmark::State &state) {
    int n = state.range(0);
    int m = n * 4;

    auto ng = generateGraph(n, m);
    vector<vector<pair<int, int> > > g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ng[i][j] != 0) {
                g[i].emplace_back(j, ng[i][j]);
                g[j].emplace_back(i, ng[i][j]);
            }
        }
    }

    auto prim = [&]() {
        priority_queue<array<int, 2> > pq;

        vector<bool> used(n, false);
        vector<int> mn(n, 1e9);
        int ans = 0;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [w, v] = pq.top();
            pq.pop();
            if (used[v]) continue;
            used[v] = true;
            ans += w;
            for (auto [u, nw]: g[v]) {
                if (!used[u] and nw < mn[u]) {
                    mn[u] = nw;
                    pq.push({nw, u});
                }
            }
        }
        return ans;
    };

    for (auto _: state) {
        int ans = prim();
        benchmark::DoNotOptimize(ans);
    }
    state.SetComplexityN(m);
}

BENCHMARK(PrimeWithPQBenchmark)->RangeMultiplier(10)->Range(100, 10000)->Complexity();

BENCHMARK_MAIN();
