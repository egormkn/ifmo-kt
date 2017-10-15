#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib>
#include <utility>

using namespace std;

FILE *fin = fopen("destroy.in", "r");
FILE *fout = fopen("destroy.out", "w");

struct edge {
    unsigned id, from, to;
    unsigned long long cost;

    edge(unsigned i, unsigned a, unsigned b, unsigned long long c): id(i), from(a), to(b), cost(c) {}
};

bool comparator(edge a, edge b) {
    return a.cost < b.cost;
}

vector<unsigned> dsu_parent;

unsigned dsu_get(unsigned v) {
    return (v == dsu_parent[v]) ? v : (dsu_parent[v] = dsu_get(dsu_parent[v]));
}

void dsu_unite(unsigned a, unsigned b) {
    a = dsu_get(a);
    b = dsu_get(b);

    if(rand() & 1) {
        swap(a, b);
    }

    if(a != b) {
        dsu_parent[a] = b;
    }
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0, a, b;
    unsigned long long s = 0, c;
    fscanf(fin, "%u %u %llu", &n, &m, &s);

    vector<edge> edges;
    vector<unsigned> answer;
    vector<bool> used(m, false);

    for(unsigned i = 0; i < m; i++) {
        fscanf(fin, "%u %u %llu", &a, &b, &c);
        a--;
        b--;
        edges.push_back(edge(i, a, b, c));
    }

    sort(edges.begin(), edges.end(), comparator);
    dsu_parent.resize(n);

    for(unsigned i = 0; i < n; i++) {
        dsu_parent[i] = i;
    }

    for(int i = m - 1; i >= 0; i--) {
        a = edges[i].from;
        b = edges[i].to;
        if(dsu_get(a) != dsu_get(b)) {
            dsu_unite(a, b);
            used[i] = true;
        }
    }

    for(int i = 0; i < m; i++) {
        if (!used[i] && s >= edges[i].cost) {
            s -= edges[i].cost;
            answer.push_back(edges[i].id);
        }
    }

    sort(answer.begin(), answer.end());

    fprintf(fout, "%u\n", answer.size());
    for (int i = 0; i < answer.size(); i++) {
        fprintf(fout, "%u ", answer[i] + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}