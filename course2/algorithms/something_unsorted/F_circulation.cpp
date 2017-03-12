#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("circulation.in", "r");
FILE *fout = fopen("circulation.out", "w");

const int INF = 1000000000; // константа-бесконечность

struct edge {
    int a, b, cap, flow;
};

unsigned n, m, s, t;
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

void add_edge(int v1, int v2, int c) {
    edge e1 = {v1, v2, c, 0};
    edge e2 = {v2, v1, 0, 0};
    g[v1].push_back((int) e.size());
    e.push_back(e1);
    g[v2].push_back((int) e.size());
    e.push_back(e2);
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);

    n += 2;
    s = 0;
    t = n - 1;

    g.resize(n);

    d.resize(n);
    ptr.resize(n);
    queue.resize(n);

    unsigned v1, v2, cmin, cmax;
    for (unsigned i = 0; i < m; i++) {
        fscanf(fin, "%d %d %d %d", &v1, &v2, &cmin, &cmax);
        add_edge(v1, v2, cmax - cmin);
        add_edge(s, v2, cmin);
        add_edge(v1, t, cmin);
    }

    for (;;) {
        if(!bfs()) break;
        ptr.assign(n, 0);
        while (dfs(s, INF)) {}
    }

    bool found = true;
    for (int i = 0; i < g[s].size(); i++) {
        if(e[g[s][i]].flow != e[g[s][i]].cap) {
            found = false;
        }
    }

    if(found) {
        fprintf(fout, "YES\n");
        for (int i = 0; i < e.size(); i += 6) {
            fprintf(fout, "%d\n", e[i].flow + e[i + 2].flow);
        }
    } else {
        fprintf(fout, "NO\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}