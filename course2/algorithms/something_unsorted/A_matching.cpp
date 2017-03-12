#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("matching.in", "r");
FILE *fout = fopen("matching.out", "w");

vector<vector<int>> g;
vector<int> mt;
vector<char> used;

bool try_kuhn(int v) {
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
    unsigned n = 0, m = 0, k = 0, v1, v2, count = 0;
    fscanf(fin, "%d %d %d", &n, &m, &k);

    g.resize(n); // LEFT -> RIGHT edges
    mt.assign(m, -1); // RIGHT -> LEFT matching

    for (unsigned i = 0; i < k; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--;
        v2--;
        g[v1].push_back(v2);
    }

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