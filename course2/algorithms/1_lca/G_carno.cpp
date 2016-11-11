#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("carno.in", "r");
FILE *fout = fopen("carno.out", "w");

unsigned long find_set(unsigned long v, vector<unsigned long> &parent) {
    if(v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v], parent);
}

int main(int argc, char **argv) {
    unsigned long m = 0, n = 1, l = 1;
    while ((1 << l) <= 200000) {
        ++l;
    }
    fscanf(fin, "%lu", &m);

    vector<vector<unsigned long>> G(n), up(n, vector<unsigned long>(l + 1));
    vector<unsigned long> height(n, 0), parent(n, 0);
    vector<bool> removed(n, false);

    up[0][0] = up[0][1] = 0;

    for (unsigned long q = 0; q < m; q++) {
        char c;
        unsigned long v, u;
        do {
            fscanf(fin, "%c", &c);
        } while (c != '+' && c != '-' && c != '?');
        switch (c) {
            case '+':
                fscanf(fin, "%lu", &v);
                u = n++;
                G[--v].push_back(u);
                G.resize(n);

                up.push_back(vector<unsigned long>(l + 1));
                height.resize(n);
                removed.push_back(false);
                parent.resize(n);

                parent[u] = u;
                height[u] = height[v] + 1;
                up[u][0] = v;
                for (unsigned long i = 1; i <= l; ++i) {
                    up[u][i] = up[up[u][i - 1]][i - 1];
                }

                break;
            case '-':
                fscanf(fin, "%lu", &v);
                removed[--v] = true;
                parent[v] = find_set(up[v][0], parent);
                break;
            case '?':
                fscanf(fin, "%lu %lu", &u, &v);
                --u;
                --v;
                if(height[u] > height[v]) {
                    swap(u, v);
                } // height[v] >= height[u]
                unsigned long delta = height[v] - height[u];
                for (unsigned long i = 0; delta > 0; i++) {
                    if(delta % 2 == 1) {
                        v = up[v][i];
                    }
                    delta = delta >> 1;
                }
                unsigned long res;
                if(v == u) {
                    res = v;
                } else {
                    unsigned long x = u, y = v;
                    long k = l;
                    while (k >= 0) {
                        while (k >= 0 && up[x][k] == up[y][k]) {
                            k--;
                        }
                        if(k != -1) {
                            x = up[x][k];
                            y = up[y][k];
                        }
                    }
                    res = up[x][0];
                }
                if (removed[res]) {
                    res = find_set(res, parent);
                }
                fprintf(fout, "%lu\n", res + 1);
                break;
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}