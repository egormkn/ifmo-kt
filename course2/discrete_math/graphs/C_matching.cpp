#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("matching.in", "r");
FILE *fout = fopen("matching.out", "w");

struct vertex {
    int id, weight;

    vertex(int i, int w): id(i), weight(w) {}
};

vector<vector<int>> g;
vector<int> mt;
vector<vertex> order;
vector<bool> used;

bool comparator(vertex a, vertex b) {
    return a.weight > b.weight;
}

bool try_kuhn(int v) {
    if(used[v]) return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if(mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    unsigned n = 0;
    fscanf(fin, "%d", &n); // k - edges

    g.resize(n); // LEFT -> RIGHT edges
    mt.assign(n, -1); // RIGHT -> LEFT matching

    for (unsigned i = 0, w; i < n; i++) {
        fscanf(fin, "%d", &w);
        order.push_back(vertex(i, w));
    }
    sort(order.begin(), order.end(), comparator);

    for (unsigned i = 0, m; i < n; i++) {
        fscanf(fin, "%d", &m);
        for (unsigned j = 0, v; j < m; j++) {
            fscanf(fin, "%d", &v);
            g[i].push_back(--v);
        }
    }

    for (int i = 0; i < n; i++) {
        int v = order[i].id;
        used.assign(n, false);
        if (try_kuhn(v)) {
            printf("VERTEX\n");
        }
    }

    vector<int> matching(mt.size(), -1);

    for (int i = 0; i < mt.size(); i++) {
        if (mt[i] > -1) {
            matching[mt[i]] = i;
        }
    }

    for (int i = 0; i < matching.size(); i++) {
        fprintf(fout, "%d ", matching[i] + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}