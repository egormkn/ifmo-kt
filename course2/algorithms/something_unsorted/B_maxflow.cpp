#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("maxflow.in", "r");
FILE *fout = fopen("maxflow.out", "w");

const int INF = 1000000000; // константа-бесконечность

struct edge {
    int a, b, cap, flow;
};

unsigned n, s, t;
vector<edge> e;
vector<vector<int>> g;
vector<int> d, ptr, queue;

bool bfs() {
    int qh = 0, qt = 0;
    queue[qt++] = s;
    d.assign(n, -1);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = queue[qh++];
        for (size_t i = 0; i < g[v].size(); ++i) {
            int id = g[v][i],
                    to = e[id].b;
            if(d[to] == -1 && e[id].flow < e[id].cap) {
                queue[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs(int v, int flow) {
    if(!flow) return 0;
    if(v == t) return flow;
    for (; ptr[v] < (int) g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
                to = e[id].b;
        if(d[to] != d[v] + 1) continue;
        int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if(pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic() {
    int flow = 0;
    for (;;) {
        if(!bfs()) break;
        ptr.assign(n, 0);
        while (int pushed = dfs(s, INF))
            flow += pushed;
    }
    return flow;
}

int main(int argc, char **argv) {
    unsigned m = 0, v1, v2, c;
    fscanf(fin, "%d %d", &n, &m);
    s = 0;
    t = n - 1;

    g.resize(n);

    d.resize(n);
    ptr.resize(n);
    queue.resize(n);

    for (unsigned i = 0; i < m; i++) {
        fscanf(fin, "%d %d %d", &v1, &v2, &c);
        v1--;
        v2--;
        edge e1 = {v1, v2, c, 0};
        edge e2 = {v2, v1, 0, 0};
        g[v1].push_back((int) e.size());
        e.push_back(e1);
        g[v2].push_back((int) e.size());
        e.push_back(e2);
    }

    fprintf(fout, "%d", dinic());

    fclose(fin);
    fclose(fout);
    return 0;
}