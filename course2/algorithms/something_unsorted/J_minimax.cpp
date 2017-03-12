#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("minimax.in", "r");
FILE *fout = fopen("minimax.out", "w");

vector<vector<int>> g;
vector<int> mt;
vector<char> used;

vector<vector<int>> cost;

bool try_kuhn(int v, max) {
    if (used[v]) return false;
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn (mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    int n = 0, c;
    fscanf(fin, "%d", &n);

    cost.resize(n);
    g.resize(n); // LEFT -> RIGHT edges
    int max = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fin, "%d ", &c);
            cost[i].push_back(c);
        }
    }


    mt.assign(n*n, -1); // RIGHT -> LEFT matching
    for (unsigned v = 0; v < n; ++v) {
        used.assign(n, false);
        if (try_kuhn(v)) {
            count++;
        }
    }

    fprintf(fout, "%d", count);

    fclose(fin);
    fclose(fout);
    return 0;
}