#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

FILE *fin = fopen("mincost.in", "r");
FILE *fout = fopen("mincost.out", "w");

const int INF = 1000000000; // константа-бесконечность

struct edge {
    int a, b, cap, flow, cost;
};

unsigned n, m, s, t;
vector<edge> e;

void add_edge(int v1, int v2, int c, int cost) {
    edge e1 = {v1, v2, c, 0, cost};
    edge e2 = {v2, v1, 0, 0, -cost};
    e.push_back(e1);
    e.push_back(e2);
}

bool solve() {
    vector<long long> d(n, LLONG_MAX);
    d[s] = 0;
    vector<int> p(n, -1);
    for (;;) {
        bool any = false;
        for (int j = 0; j < e.size(); ++j)
            if(d[e[j].a] < LLONG_MAX)
                if(d[e[j].b] > d[e[j].a] + e[j].cost && e[j].flow < e[j].cap) {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = j;
                    any = true;
                }
        if(!any) break;
    }

    int min_flow = INF;


    if(d[t] == LLONG_MAX)
        min_flow = 0;
    else {
        for (int cur = p[t]; cur != -1; cur = p[e[cur].a])
            min_flow = min(min_flow, e[cur].cap - e[cur].flow);

        for (int cur = p[t]; cur != -1; cur = p[e[cur].a]) {
            e[cur].flow += min_flow;
            e[cur ^ 1].flow -= min_flow;
        }
    }

    return min_flow != 0;
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);

    s = 0;
    t = n - 1;

    unsigned v1, v2, c, cost;
    for (unsigned i = 0; i < m; i++) {
        fscanf(fin, "%d %d %d %d", &v1, &v2, &c, &cost);
        v1--;
        v2--;
        add_edge(v1, v2, c, cost);
    }

    while (solve()) {}

    long long sum = 0;

    for (int i = 0; i < e.size(); i += 2) {
        sum += (long long) e[i].cost * (long long) e[i].flow;
    }

    fprintf(fout, "%lld", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}