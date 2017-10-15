#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("cycles.in", "r");
FILE *fout = fopen("cycles.out", "w");

struct element {
    int number, weight;

    element(int n, int w): number(n), weight(w) {}
};

bool comparator(element &a, element &b) {
    return a.weight > b.weight;
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0;
    fscanf(fin, "%d %d", &n, &m);

    vector<bool> dependent((unsigned int) (1 << n), false);

    vector<element> X;
    for (int i = 0, w; i < n; i++) {
        fscanf(fin, "%d", &w);
        X.push_back(element(i, w));
    }

    for (long i = 0, size; i < m; i++) {
        fscanf(fin, "%ld", &size);
        long bitmask = 0;
        for (long j = 0, e; j < size; j++) {
            fscanf(fin, "%ld", &e);
            bitmask |= 1 << --e;
        }
        dependent[bitmask] = true;
        for (int j = bitmask + 1; j < 1 << n; j++) {
            if ((j | bitmask) == j) {
                dependent[j] = true;
            }
        }
    }

    sort(X.begin(), X.end(), comparator);

    long sum = 0, bitmask = 0;
    for (int i = 0; i < X.size(); i++) {
        long bit = 1 << X[i].number;
        if (!dependent[bitmask | bit]) {
            sum += X[i].weight;
            bitmask |= bit;
        }
    }

    fprintf(fout, "%lu", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}