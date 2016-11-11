#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *fin = fopen("ancestor.in", "r");
FILE *fout = fopen("ancestor.out", "w");

unsigned timer = 0;

void dfs (int v, vector<vector<int>> &G, vector<int> &tin, vector<int> &tout) {
    tin[v] = ++timer;
    for (size_t i = 0; i < G[v].size(); ++i) {
        int to = G[v][i];
        dfs(to, G, tin, tout);
    }
    tout[v] = ++timer;
}

bool upper (int a, int b, vector<int> &tin, vector<int> &tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0;
    fscanf(fin, "%d", &n);

    int root = 0;
    vector<vector<int>> G(n, vector<int>());
    for (int i = 0; i < n; i++) {
        unsigned f;
        fscanf(fin, "%u", &f);
        if (f == 0) {
            root = i;
        } else {
            G[--f].push_back(i);
        }
    }

    vector<int> tin(n), tout(n);
    dfs(root, G, tin, tout);

    fscanf(fin, "%u", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        fscanf(fin, "%d %d", &a, &b);
        if (upper(--a, --b, tin, tout)) {
            fprintf(fout, "1\n");
        } else {
            fprintf(fout, "0\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}