#include <iostream>
#include <vector>

using namespace std;

FILE *fin = fopen("dynamic.in", "r");
FILE *fout = fopen("dynamic.out", "w");

unsigned long timer = 0, l = 1;
vector<unsigned long> tin, tout, height;
vector<vector<unsigned long>> G, up;

void dfs(unsigned long v, unsigned long p, unsigned long h) {
    tin[v] = ++timer;
    height[v] = h;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (size_t i = 0; i < G[v].size(); ++i) {
        unsigned long to = G[v][i];
        if(to != p)
            dfs(to, v, h + 1);
    }
    tout[v] = ++timer;
}

bool upper(unsigned long a, unsigned long b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

unsigned long lca(unsigned long a, unsigned long b) {
    if(a == b) {
        return a;
    }
    if(upper(a, b)) {
        return a;
    }
    if(upper(b, a)) {
        return b;
    }
    for (unsigned long i = l; i >= 0; --i) {
        if(!upper(up[a][i], b)) {
            a = up[a][i];
        }
        if(i == 0) { break; }
    }
    return up[a][0];
}

int main(int argc, const char **argv) {
    unsigned long n = 0, m = 0, root = 0, v, u;
    fscanf(fin, "%lu", &n);

    while (n != 0) {
        root = 0;
        timer = 0;
        l = 1;
        while ((1 << l) <= n) {
            ++l;
        }
        G.resize(n);
        up.resize(n);
        for (unsigned long i = 0; i < n; i++) {
            G[i].clear();
            up[i].resize(l + 1);
        }

        for (int i = 1; i < n; i++) {
            fscanf(fin, "%lu %lu", &v, &u);
            --v;
            --u;
            G[v].push_back(u);
            G[u].push_back(v);
        }

        tin.resize(n);
        tout.resize(n);
        height.resize(n);

        dfs(0, 0, 0);

        fscanf(fin, "%lu", &m);
        for (unsigned long i = 0, res; i < m; i++) {
            char c;
            do {
                fscanf(fin, "%c", &c);
            } while (c != '?' && c != '!');

            switch (c) {
                case '!':
                    fscanf(fin, "%lu", &root);
                    root--;
                    break;
                case '?':
                    fscanf(fin, "%lu %lu", &v, &u);
                    --v;
                    --u;
                    res = lca(u, v);
                    u = lca(u, root);
                    v = lca(root, v);
                    if(height[u] > height[res]) {
                        res = u;
                    }
                    if(height[v] > height[res]) {
                        res = v;
                    }
                    fprintf(fout, "%lu\n", ++res);
                    break;
                default:
                    break;
            }
        }

        fscanf(fin, "%d", &n);
    }

    return 0;
}