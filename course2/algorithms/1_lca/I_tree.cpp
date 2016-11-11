#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("tree.in", "r");
FILE *fout = fopen("tree.out", "w");

unsigned long timer = 0, l = 1;
vector<unsigned long> height;

void dfs(unsigned long v, unsigned long p, unsigned long costval, unsigned long h, vector<vector<pair<unsigned long, unsigned long>>> &G, vector<unsigned long> &tin, vector<unsigned long> &tout, vector<vector<unsigned long>> &up, vector<vector<unsigned long>> &cost) {
    tin[v] = ++timer;
    height[v] = h;
    up[v][0] = p;
    cost[v][0] = costval;
    for (unsigned long i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
        cost[v][i] = cost[v][i-1] + cost[up[v][i-1]][i-1];
    }
    for (size_t i=0; i<G[v].size(); ++i) {
        unsigned long to = G[v][i].first;
        if (to != p)
            dfs (to, v, G[v][i].second, h + 1, G, tin, tout, up, cost);
    }
    tout[v] = ++timer;
}

bool upper (unsigned long a, unsigned long b, vector<unsigned long> &tin, vector<unsigned long> &tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

unsigned long costcount(unsigned long bottom, unsigned long top, vector<vector<unsigned long>> &up, vector<vector<unsigned long>> &cost) {
    unsigned long delta = height[bottom] - height[top];
    unsigned long current = bottom;
    unsigned long costval = 0;
    for (unsigned long i = 0; delta > 0; i++) {
        if (delta % 2 == 1) {
            costval = costval + cost[current][i];
            current = up[current][i];
        }
        delta = delta >> 1;
    }
    return costval;
}

unsigned long minlca(unsigned long a, unsigned long b, vector<unsigned long> &tin, vector<unsigned long> &tout, vector<vector<unsigned long>> &up, vector<vector<unsigned long>> &cost) {
    if (a == b) {
        return 0;
    }
    if (upper(a, b, tin, tout)) {
        // up from b to a
        return costcount(b, a, up, cost);
    }
    if (upper(b, a, tin, tout)) {
        // up from a to b
        return costcount(a, b, up, cost);
    }
    unsigned long ta = a;
    for (unsigned long i = l; i >= 0; --i) {
        if(!upper(up[a][i], b, tin, tout)) {
            a = up[a][i];
        }
        if (i == 0) {break;}
    }
    return costcount(ta, up[a][0], up, cost) + costcount(b, up[a][0], up, cost);
}

int main(int argc, char **argv) {
    unsigned long n = 0, m = 0;
    fscanf(fin, "%lu", &n);
    vector<vector<pair<unsigned long, unsigned long>>> G(n, vector<pair<unsigned long, unsigned long>>());

    for (unsigned long i = 1; i < n; i++) {
        unsigned long u, v, w;
        fscanf(fin, "%lu %lu %lu", &u, &v, &w);
        G[v].push_back(make_pair(u, w));
        G[u].push_back(make_pair(v, w));
    }

    while ((1<<l) <= n) {
        ++l;
    }
    vector<unsigned long> tin(n), tout(n);
    vector<vector<unsigned long>> up(n, vector<unsigned long>(l+1));
    vector<vector<unsigned long>> cost(n, vector<unsigned long>(l+1));
    height.resize(n);
    dfs(0, 0, 0, 0, G, tin, tout, up, cost);

    fscanf(fin, "%lu", &m);
    for (unsigned long i = 0; i < m; i++) {
        unsigned long x, y;
        fscanf(fin, "%lu %lu", &x, &y);
        //printf("Request: %lu %lu\n", x, y);
        unsigned long res = minlca(x, y, tin, tout, up, cost);
        fprintf(fout, "%lu\n", res);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}