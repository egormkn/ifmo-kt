//
// Created by Vlad on 01.12.2016.
//
#include <stdio.h>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

FILE *in = fopen("decomposition.in", "r");
FILE *out = fopen("decomposition.out", "w");

struct edge {
    int a, b, capacity, flow;

    edge(int a, int b, int capacity, int flow) : a(a), b(b), capacity(capacity), flow(flow) {}
};

struct decomposition {
    bool OK;
    vector<int> vertexes;
    int flow;

    decomposition(bool wrong) : OK(wrong) {}

    decomposition(vector<int> vertexes, int flow) : vertexes(vertexes), flow(flow) {
        OK = true;
    }
};

int n, m;
int MAX_FLOW = 1E9;
vector<edge> edges;
vector<int> ptr;
int *depth;
vector<vector<int>> vector_of_edges;
vector <decomposition> answer;

bool bfs() {
    queue<int> queue_of_vertexes;
    queue_of_vertexes.push(0);
    for (int i = 0; i < n; ++i) {
        depth[i] = -1;
    }
    depth[0] = 0;
    while (!queue_of_vertexes.empty() && depth[n - 1] == -1) {
        int v = queue_of_vertexes.front();
        queue_of_vertexes.pop();
        for (int edge_id : vector_of_edges[v]) {
            int to = edges[edge_id].b;
            if (depth[to] == -1 && edges[edge_id].flow < edges[edge_id].capacity) {
                queue_of_vertexes.push(to);
                depth[to] = depth[v] + 1;
            }
        }
    }
    return depth[n - 1] != -1;
}

int dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == n - 1) return flow;
    for (; ptr[v] < vector_of_edges[v].size(); ++ptr[v]) {
        int edge_id = vector_of_edges[v][ptr[v]];
        int to = edges[edge_id].b;
        if (depth[to] != depth[v] + 1) continue;
        int pushed = dfs(to, min(flow, edges[edge_id].capacity - edges[edge_id].flow));
        if (pushed) {
            edges[edge_id].flow += pushed;
            edges[edge_id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

decomposition simpleDecomposition(int start) {
    vector<int> edges_list;
    vector<bool> used;
    used.resize(n);
    used.assign(n, false);
    int v = start;
    while (!used[v]) {
        if (v == n - 1) {
            break;
        }
        int e = -1;
        for (int edge_id : vector_of_edges[v]) {
            if (edges[edge_id].flow > 0) {
                e = edge_id;
                break;
            }
        }
        if (e == -1) return decomposition(false);
        edges_list.push_back(e);
        used[v] = true;
        v = edges[e].b;
        if (used[v]) {
            while (edges_list.front() != v) {
                edges_list.erase(edges_list.begin() + 1);
            }
            break;
        }
    }
    int min = MAX_FLOW;
    for (int edge_id : edges_list) {
        if (edges[edge_id].flow < min) min = edges[edge_id].flow;
    }
    for (int edge_id : edges_list) {
        edges[edge_id].flow -= min;
    }
    if (edges_list.size() == 0) return decomposition(false);
    return decomposition(edges_list, min);
}

void fullDecomposition() {
    decomposition p = simpleDecomposition(0);
    while (p.OK) {
        answer.push_back(p);
        p = simpleDecomposition(0);
    }
    for (int i = 1; i < n - 1; ++i) {
        p = simpleDecomposition(i);
        while (p.OK) {
            answer.push_back(p);
            p = simpleDecomposition(i);
        }
    }
}

int main(int argc, char *args[]) {
    fscanf(in, "%d %d\n", &n, &m);
    vector_of_edges.resize(n);
    depth = new int[n];
    ptr.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b, capacity;
        fscanf(in, "%d %d %d", &a, &b, &capacity);
        --a;
        --b;
        edge e1(a, b, capacity, 0);
        edge e2(b, a, 0, 0);
        vector_of_edges[a].push_back(edges.size());
        edges.push_back(e1);
        vector_of_edges[b].push_back(edges.size());
        edges.push_back(e2);
    }




    while (true) {
        if (!bfs()) break;
        ptr.assign(n, 0);
        while (dfs(0, MAX_FLOW)) {}
    }
    fullDecomposition();
    fprintf(out, "%d\n", answer.size());
    for (vector<decomposition>::const_iterator d = answer.begin(); d != answer.end(); ++d) {
        fprintf(out, "%d %d ", d->flow, d->vertexes.size());
        vector<int> my_list = d->vertexes;
        for (vector<int>::const_iterator v = my_list.begin(); v != my_list.end(); ++v) {
            fprintf(out, "%d ", *v / 2 + 1);
        }
        fprintf(out, "\n");
    }
}
