#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("lca.in", "r");
FILE *fout = fopen("lca.out", "w");

void DFS(int v, int d, const vector<vector<int>> &G, vector<int> &tour, vector<int> &depth, vector<int> &position) {
    position[v] = tour.size();
    tour.push_back(v);
    depth.push_back(d);
    for (int i = 0; i < G[v].size(); i++) {
        DFS(G[v][i], d + 1, G, tour, depth, position);
        tour.push_back(v);
        depth.push_back(d);
    }
}

vector<int> findEulerTour(const vector<vector<int>> &G, vector<int> &depth, vector<int> &position) {
    vector<int> tour;
    DFS(0, 0, G, tour, depth, position);
    return tour;
}

vector<vector<int>> sparseTable(vector<int> &array, vector<unsigned> &log) {
    log.resize(array.size() + 1); // {0, 0, 1, 1, 2, 2, 2, 2, 3, 3...}
    log[1] =  0;
    for (int i = 2; i < log.size(); i++) {
        log[i] = log[i / 2] + 1;
    }
    vector<vector<int>> ST(log[array.size()] + 1); // ST[i][j] = min [ A[j], A[j+2^i] )
    for (int i = 0; i < ST.size(); i++) {
        for (int j = 0; j + (1 << i) - 1 < array.size(); j++) {
            if (i == 0) {
                ST[i].push_back(j);
            } else {
                int left = ST[i-1][j], right = ST[i-1][j+(1<<(i-1))];
                ST[i].push_back(array[left] <= array[right] ? left : right);
            }
        }
    }
    return ST;
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0;
    fscanf(fin, "%d", &n);

    vector<vector<int>> G(n, vector<int>());
    vector<int> depth, position(n);

    for (int i = 1; i < n; i++) {
        int f;
        fscanf(fin, "%d", &f);
        G[f - 1].push_back(i);
    }

    // Vector representing Euler tour
    vector<int> eulerTour = findEulerTour(G, depth, position);
    vector<unsigned> log;
    vector<vector<int>> ST = sparseTable(depth, log);

    fscanf(fin, "%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(fin, "%d %d", &x, &y);
        x = position[--x];
        y = position[--y];
        if (x > y) {
            swap(x, y);
        }
        int size = log[y - x + 1];
        int left = ST[size][x], right = ST[size][y - (1 << size) + 1];
        fprintf(fout, "%d\n", eulerTour[depth[left] < depth[right] ? left : right] + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}