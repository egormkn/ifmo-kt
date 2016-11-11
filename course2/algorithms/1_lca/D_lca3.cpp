#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

FILE *fin = fopen("lca3.in", "r");
FILE *fout = fopen("lca3.out", "w");

vector<vector<unsigned long>> G, up;
vector<unsigned long> roots, height;
vector<pair<unsigned long, unsigned long>> parent;
vector<bool> isRoot;
unsigned long l = 1;

pair<unsigned long, unsigned long> find_set (unsigned long v) {
    if (v != parent[v].first) {
        unsigned long len = parent[v].second;
        parent[v] = find_set (parent[v].first);
        parent[v].second += len;
    }
    return parent[v];
}

void dfs(unsigned long v, unsigned long p, unsigned long h) {
    height[v] = h;
    if(v != p) {
        up[v][0] = p;
    }
    for (size_t i = 0; i < G[v].size(); ++i) {
        unsigned long to = G[v][i];
        if(to != p)
            dfs(to, v, h + 1);
    }
}

unsigned long getup(unsigned long v, unsigned long i) {
    if (up[v][i] == ULONG_MAX && i > 0) {
        unsigned long up1 = getup(v, i - 1);
        if (up1 != ULONG_MAX) {
            unsigned long up2 = getup(up1, i - 1);
            if (up2 != ULONG_MAX) {
                up[v][i] = up2;
            }
        }
    }
    return up[v][i];
}

unsigned long lca(unsigned long u, unsigned long v, unsigned long du, unsigned long dv) {
    if(du > dv) {
        swap(u, v);
        swap(du, dv);
    }

    unsigned long delta = dv - du;
    for (unsigned long i = 0; delta > 0; i++) {
        if(delta % 2 == 1) {
            v = getup(v, i);
            dv -= 1 << i;
        }
        delta = delta >> 1;
    }
    unsigned long res;
    if(v == u) {
        res = v;
    } else {
        unsigned long x = u, y = v;
        unsigned long k = l;
        while (k >= 0 && k != ULONG_MAX) {
            while (k >= 0 && k != ULONG_MAX) {
                unsigned long p1 = getup(x, k);
                unsigned long p2 = getup(y, k);
                if (p1 == p2 || p1 == ULONG_MAX || p2 == ULONG_MAX) {
                    k--;
                } else {
                    break;
                }
            }
            if(k != ULONG_MAX) {
                x = getup(x, k);
                y = getup(y, k);
            }
        }
        res = getup(x, 0);
    }

    return res;
}

int main(int argc, char **argv) {
    unsigned long k = 0, n = 0;
    fscanf(fin, "%lu", &n);
    while ((1 << l) <= n) {
        ++l;
    }

    G.resize(n);
    up.assign(n, vector<unsigned long>(l + 1, ULONG_MAX));
    height.resize(n);
    parent.resize(n);
    isRoot.assign(n, false);

    for (unsigned long i = 0, p; i < n; i++) {
        fscanf(fin, "%lu", &p);
        isRoot[i] = p == 0;
        if(p == 0) {
            roots.push_back(i);
            parent[i] = make_pair (i, 0);
        } else {
            p--;
            G[p].push_back(i);
            parent[i] = make_pair (p, 1);
        }
    }

    for (unsigned long i = 0; i < roots.size(); i++) {
        dfs(roots[i], roots[i], 0);
    }

    fscanf(fin, "%lu", &k);
    long x, y;
    for (unsigned long i = 0, c, u, v, ans = 0; i < k; i++) {
        fscanf(fin, "%lu %lu %lu", &c, &x, &y);
        u = (x - 1 + ans) % n;
        v = (y - 1 + ans) % n;
        if(c == 0) {

            //printf("u: %lu, v: %lu\n", u, v);
            unsigned long du = 0, dv = 0;
            pair<unsigned long, unsigned long> leader1 = find_set(u);
            pair<unsigned long, unsigned long> leader2 = find_set(v);
            bool sametree = leader1.first == leader2.first;
            du = leader1.second;
            dv = leader2.second;
            //printf("du: %lu, dv:%lu\n", du, dv);
            if(sametree) {
                ans = lca(u, v, du, dv) + 1;
            } else {
                ans = 0;
            }
            fprintf(fout, "%lu\n", ans);
        } else {
            //printf("%lu -> %lu\n", u, v);
            up[u][0] = v;
            // a = find_set (a) .first;
            // b = find_set (b) .first;
            parent[u] = make_pair(v, 1);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}