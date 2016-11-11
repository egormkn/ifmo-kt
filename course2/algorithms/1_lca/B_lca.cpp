#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *fin = fopen("lca.in", "r");
FILE *fout = fopen("lca.out", "w");

unsigned timer, l;

void dfs (int v, int p, vector<vector<int>> &G, vector<int> &tin, vector<int> &tout, vector<vector<int>> &up) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i=1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (size_t i=0; i<G[v].size(); ++i) {
        int to = G[v][i];
        if (to != p)
            dfs (to, v, G, tin, tout, up);
    }
    tout[v] = ++timer;
}

bool upper (int a, int b, vector<int> &tin, vector<int> &tout) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b, vector<int> &tin, vector<int> &tout, vector<vector<int>> &up) {
    if (upper(a, b, tin, tout)) {
        return a;
    }
    if (upper(b, a, tin, tout)) {
        return b;
    }
    for (int i = l; i >= 0; --i) {
        if(!upper(up[a][i], b, tin, tout)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main(int argc, char **argv) {
    unsigned numberOfRequests = 0;
    fscanf(fin, "%d", &numberOfRequests);

    vector<vector<int>> G(1, vector<int>());
    vector<pair<int, int>> queries;

    for (int i = 0; i < numberOfRequests; i++) {
        char cmd[4];
        unsigned x, y;
        fscanf(fin, "%3s %u %u ", &cmd[0], &x, &y);
        x--;
        y--;
        if(strcmp(cmd, "ADD") == 0) {
            if(y > G.size() - 1) {
                G.resize(y + 1);
            }
            G[x].push_back(y);
        } else {
            queries.push_back(make_pair(x, y));
        }
    }

    vector<int> tin(G.size()), tout(G.size());
    vector<vector<int>> up(G.size(), vector<int>());
    l = 1;
    timer = 0;
    while ((1<<l) <= G.size()) {
        l++;
    }
    for (int i = 0; i < G.size(); i++) {
        up[i].resize(l+1);
    }

    dfs(0, 0, G, tin, tout, up);

    for (int i = 0; i < queries.size(); i++) {
        fprintf(fout, "%d\n", lca(queries[i].first, queries[i].second, tin, tout, up) + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}