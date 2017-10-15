#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

FILE *fin = fopen("multispan.in", "r");
FILE *fout = fopen("multispan.out", "w");

const int MARKER = -100;

struct edge {
    int from, to;

    edge(int a, int b) : from(a), to(b) {}
};

vector<edge> edges;

void dsu_make(vector<int> &p) {
    for (int i = 0; i < p.size(); i++) {
        p[i] = i;
    }
}

int dsu_get(int a, vector<int> &p) {
    return (a == p[a]) ? a : (p[a] = dsu_get(p[a], p));
}

void dsu_unite(int a, int b, vector<int> &p) {
    a = dsu_get(a, p);
    b = dsu_get(b, p);
    if(rand() & 1)
        swap(a, b);
    if(a != b)
        p[a] = b;
}

bool adds_cycle(int i, vector<int> &parent) {
    return dsu_get(edges[i].from, parent) == dsu_get(edges[i].to, parent);
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0;
    fscanf(fin, "%d %d", &n, &m);

    for (int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d", &a, &b);
        edges.push_back(edge(--a, --b));
    }

    vector<vector<int>> I_minus_edge(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        dsu_make(I_minus_edge[i]);
    }

    vector<set<int>> B(1, set<int>());
    vector<int> queue, last(m, -1);
    vector<bool> ready(m);
    vector<vector<int>> g(m, vector<int>());

    while (true) {
        int index = B.size() - 1;

        int next_edge = -1;
        int queue_start = 0;
        vector<int> I(n);
        dsu_make(I);
        for (set<int>::iterator it = B[index].begin(); it != B[index].end(); it++) {
            dsu_unite(edges[*it].from, edges[*it].to, I);
        }

        vector<int> parent(m, -1);
        for (int i = 0; i < m; i++) {
            if(adds_cycle(i, I)) continue;
            queue.push_back(i);
            parent[i] = MARKER;
            if(last[i] == -1) {
                next_edge = i;
                break;
            }
        }

        while (queue_start < queue.size() && next_edge == -1) { // BFS
            int v = queue[queue_start++];

            if(last[v] == -1) {
                next_edge = v;
                break;
            }
            if(!ready[v]) {
                g[v].clear();
                for (int to = 0; to < m; to++) {
                    if(to != v && !adds_cycle(to, I_minus_edge[v])) {
                        g[v].push_back(to);
                    }
                }
                ready[v] = true;
            }

            // BFS next step
            for (int i = 0; i < g[v].size(); i++) {
                int to = g[v][i];
                if(parent[to] == -1) {
                    parent[to] = v;
                    queue.push_back(to);
                    if(last[to] == -1) {
                        queue_start = queue.size();
                        next_edge = to;
                        break;
                    }
                }
            }
        }

        int next_temp = next_edge;
        if(next_temp == -1) break;
        while (parent[next_temp] != MARKER) {
            next_temp = parent[next_temp];
        }

        vector<bool> B_updated(n, false);
        int c = next_edge;
        for (int i = parent[next_edge]; i != MARKER; i = parent[i]) {
            B[last[i]].insert(c);
            B[last[i]].erase(i);
            last[c] = last[i];
            c = i;
            B_updated[last[i]] = true;
        }

        last[next_temp] = index;
        B[index].insert(next_temp);
        B_updated[index] = true;

        for (int i = 0; i <= index; i++) {
            if(!B_updated[i]) continue;
            for (set<int>::iterator it = B[i].begin(); it != B[i].end(); it++) {
                int new_edge = *it;
                dsu_make(I_minus_edge[new_edge]);
                for (set<int>::iterator it2 = B[i].begin(); it2 != B[i].end(); it2++) {
                    if(*it2 != new_edge) dsu_unite(edges[*it2].from, edges[*it2].to, I_minus_edge[new_edge]);
                }
                ready[new_edge] = false;
            }
        }

        if(B[index].size() + 1 == n) { // If base is full
            B.resize(B.size() + 1);
        }
    }


    fprintf(fout, "%d\n", B.size() - 1);
    for (int i = 0; i < B.size() - 1; i++) {
        for (set<int>::iterator it = B[i].begin(); it != B[i].end(); it++) {
            fprintf(fout, "%d ", *it + 1);
        }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}