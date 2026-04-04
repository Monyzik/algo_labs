#include <benchmark/benchmark.h>
#include <bits/stdc++.h>

// #define map unordered_map

#include "tree.h"

using namespace std;

random_device rd;
mt19937 rng(rd());

vector<string> generateKeys(int cnt) {
    uniform_int_distribution<char> dist('a', 'z');
    vector<string> keys(cnt);
    for (int i = 0; i < cnt; i++) {
        string key(8, ' ');
        for (char &c: key) {
            c = dist(rng);
        }
        keys[i] = key;
    }
    return keys;
}

int generateInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void AVLInsertBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    node *t = nullptr;
    for (int i = 0; i < sz - 1; i++) {
        t = insert(t, keys[i].c_str(), 1.0f);
    }

    vector<string> insertKeys = generateKeys(sz);

    for (auto _: state) {
        t = insert(t, insertKeys[generateInt(0, sz - 1)].c_str(), 1.0f);
        benchmark::DoNotOptimize(t);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(AVLInsertBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

void StdMapInsertBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    map<string, float> t;
    for (int i = 0; i < sz - 1; i++) {
        t[keys[i]] = 1.0f;
    }

    for (auto _: state) {
        t[keys[sz - 1]] = 1.0f;
        benchmark::DoNotOptimize(t[keys[sz - 1]]);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(StdMapInsertBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

void AVLFindBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    node *t = nullptr;
    for (string &key: keys) {
        t = insert(t, key.c_str(), 1.0f);
    }
    for (auto _: state) {
        float *val = find(t, keys[generateInt(0, sz - 1)].c_str());
        benchmark::DoNotOptimize(val);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(AVLFindBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

void StdMapFindBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    map<string, float> t;
    for (string &key: keys) {
        t[key] = 1.0f;
    }

    for (auto _: state) {
        bool ok = t.contains(keys[generateInt(0, sz - 1)]);
        benchmark::DoNotOptimize(ok);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(StdMapFindBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

void AVLEraseBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    node *t = nullptr;
    for (string &key: keys) {
        t = insert(t, key.c_str(), 1.0f);
    }
    for (auto _: state) {
        t = erase(t, keys[generateInt(0, sz - 1)].c_str());
        benchmark::DoNotOptimize(t);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(AVLEraseBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

void StdMapEraseBenchmark(benchmark::State &state) {
    int sz = state.range(0);
    vector<string> keys = generateKeys(sz);
    map<string, float> t;
    for (string &key: keys) {
        t[key] = 1.0f;
    }

    for (auto _: state) {
        t.erase(keys[generateInt(0, sz - 1)]);
        benchmark::DoNotOptimize(t);
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(StdMapEraseBenchmark)->RangeMultiplier(10)->Range(1000, 100000)->Complexity();

BENCHMARK_MAIN();
