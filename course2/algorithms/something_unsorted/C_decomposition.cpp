#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

FILE *fin = fopen("decomposition.in", "r");
FILE *fout = fopen("decomposition.out", "w");

vector<vector<int>> T;
vector<int> D, used, size;

vector<bool> visited;

void dfs(int v, int p, vector<int> &size) {
    size[v] = 1;
    for (int i = 0; i < T[v].size(); i++) {
        int to = T[v][i];
        if (to == p) continue;
        dfs(to, v, size);
        size[v] += size[to];
    }
}

int findCentroid(int start, vector<int> &size) {
    for (int i = 0; i < T[start].size(); i++) {
        int to = T[start][i];
        if (!used[to] && size[to] > size[start] / 2) {
            int temp = size[to];
            size[to] = size[start];
            size[start] -= temp;
            return findCentroid(to, size);
        }
    }
    return start;
}

void buildDecomposition(int start, int centroid_root) {
    int centroid = findCentroid(start, size);
    //printf("Centroid: %d (%d)\n", centroid + 1, size[centroid]);
    D[centroid] = centroid_root;
    used[centroid] = true;
    for (int i = 0; i < T[centroid].size(); i++) {
        int to = T[centroid][i];
        if (to != centroid_root && !used[to]) {
            buildDecomposition(to, centroid);
        }
    }
}

int main(int argc, char **argv) {
    unsigned n = 0;
    fscanf(fin, "%u", &n);

    T.resize(n);
    for (int i = 0, v1, v2; i < n - 1; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--;
        v2--;
        T[v1].push_back(v2);
        T[v2].push_back(v1);
    }

    D.resize(n);
    used.assign(n, false);
    size.assign(n, 0);
    visited.assign(n, false);
    int start = rand() % n;
    dfs(start, -1, size);
    buildDecomposition(start, -1);

    for (unsigned i = 0; i < n; i++) {
        fprintf(fout, "%d ", D[i] + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}