#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("lca_rmq.in", "r");
FILE *fout = fopen("lca_rmq.out", "w");

void DFS(unsigned long v, unsigned long d, const vector<vector<unsigned long>> &G, vector<unsigned long> &tour, vector<unsigned long> &depth, vector<unsigned long> &position) {
    position[v] = tour.size();
    tour.push_back(v);
    depth.push_back(d);
    for (unsigned long i = 0; i < G[v].size(); i++) {
        DFS(G[v][i], d + 1, G, tour, depth, position);
        tour.push_back(v);
        depth.push_back(d);
    }
}

vector<unsigned long> findEulerTour(const vector<vector<unsigned long>> &G, vector<unsigned long> &depth, vector<unsigned long> &position) {
    vector<unsigned long> tour;
    DFS(0, 0, G, tour, depth, position);
    return tour;
}

vector<vector<unsigned long>> sparseTable(vector<unsigned long> &array, vector<unsigned long> &log) {
    log.resize(array.size() + 1); // {0, 0, 1, 1, 2, 2, 2, 2, 3, 3...}
    log[1] = 0;
    for (unsigned long i = 2; i < log.size(); i++) {
        log[i] = log[i / 2] + 1;
    }
    vector<vector<unsigned long>> ST(log[array.size()] + 1); // ST[i][j] = min [ A[j], A[j+2^i] )
    for (unsigned long i = 0; i < ST.size(); i++) {
        for (unsigned long j = 0; j + (1 << i) - 1 < array.size(); j++) {
            if (i == 0) {
                ST[i].push_back(j);
            } else {
                unsigned long left = ST[i-1][j], right = ST[i-1][j+(1<<(i-1))];
                ST[i].push_back(array[left] <= array[right] ? left : right);
            }
        }
    }
    return ST;
}

int main(int argc, char **argv) {
    unsigned long n = 0;
    unsigned long long m = 0;
    fscanf(fin, "%lu %llu", &n, &m);

    vector<vector<unsigned long>> G(n, vector<unsigned long>());
    vector<unsigned long> depth, position(n);

    for (unsigned long i = 1; i < n; i++) {
        unsigned long f;
        fscanf(fin, "%lu", &f);
        G[f].push_back(i);
    }

    // Vector representing Euler tour
    vector<unsigned long> eulerTour = findEulerTour(G, depth, position);
    vector<unsigned long> log;
    vector<vector<unsigned long>> ST = sparseTable(depth, log);

    unsigned long long sum = 0;
    unsigned long long a1, a2, x, y, z;
    fscanf(fin, "%llu %llu %llu %llu %llu", &a1, &a2, &x, &y, &z);

    unsigned long v1 = (unsigned long) a1, v2 = (unsigned long) a2;

    for (unsigned long long i = 1; i <= m; i++) {
        //printf("Query: %lu %lu\n", v1, v2);
        v1 = position[v1];
        v2 = position[v2];
        if (v1 > v2) {
            swap(v1, v2);
        }
        unsigned long size = log[v2 - v1 + 1];
        unsigned long left = ST[size][v1], right = ST[size][v2 - (1 << size) + 1];
        unsigned long result = eulerTour[depth[left] < depth[right] ? left : right];
        sum += result;
        //printf("Answer: %lu\n\n", result);
        a1 = (((x * a1) % n + (y * a2) % n + z % n) % n);
        a2 = (((x * a2) % n + (y * a1) % n + z % n) % n);
        v1 = (unsigned long) ((a1 + result) % n);
        v2 = (unsigned long) a2;
    }

    fprintf(fout, "%llu", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}