//
#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

FILE *in = fopen("mincost.in", "r");
FILE *out = fopen("mincost.out", "w");
 
struct edge {
    int a, b, capacity, flow, cost;

    edge(int a, int b, int capacity, int flow, int cost) : a(a), b(b), capacity(capacity), flow(flow), cost(cost) {}
};

int INF = 1E6;
int n, m;
vector<edge> edges;

void add_edge(int a, int b, int cap, int cost) {
    edge e1(a, b, cap, 0, cost);
    edge e2(b, a, 0, 0, -cost);
    edges.push_back(e1);
    edges.push_back(e2);
}

void getInputInformation() {
    fscanf(in, "%d %d\n", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, capacity, cost;
        fscanf(in, "%d %d %d %d", &a, &b, &capacity, &cost);
        add_edge(a - 1, b - 1, capacity, cost);
    }
}

int ford_bellman() {
    vector<long long> depth(n, LLONG_MAX);
    depth[0] = 0;
    vector<int> p(n, -1);
    for (;;) {
        bool any = false;
        for (int j = 0; j < edges.size(); ++j) {
            if (depth[edges[j].a] < LLONG_MAX) {
                if (edges[j].flow < edges[j].capacity && depth[edges[j].b] > depth[edges[j].a] + edges[j].cost) {
                    depth[edges[j].b] = depth[edges[j].a] + edges[j].cost;
                    p[edges[j].b] = j;
                    any = true;
                }
            }
        }
        if (!any) break;
    }
    int min_flow = INF;
    if (depth[n - 1] != LLONG_MAX) {
        int e = p[n - 1];
        while (e != -1) {
            min_flow = min(min_flow, (edges[e].capacity - edges[e].flow));
            e = p[edges[e].a];
        }
        e = p[n - 1];
        while (e != -1) {
            edges[e].flow += min_flow;
            edges[e ^ 1].flow -= min_flow;
            e = p[edges[e].a];
        }
    } else {
        min_flow = 0;
    }
    return min_flow;
}

int main(int argc, char *args[]) {
    getInputInformation();
    while (ford_bellman());
    long long final_cost = 0;
    for (int i = 0; i < edges.size(); i += 2) {
        final_cost += ((long long) edges[i].cost) * edges[i].flow;
    }
    fprintf(out, "%lld", final_cost);
    fclose(in);
    fclose(out);
}