#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdlib>
#include <deque>

using namespace std;

FILE *fin = fopen("rainbow.in", "r");
FILE *fout = fopen("rainbow.out", "w");

const int NUM_OF_COLORS = 100;

struct edge {
    int from, to, color;

    edge(int a, int b, int c) : from(a), to(b), color(c) {}
};

vector<edge> edges;

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

set<int> BFS(vector<vector<int>> &g, int m, vector<bool> &X2) {
    deque<int> q;
    q.push_back(m);
    vector<bool> used(g.size());
    vector<int> p(g.size());
    used[m] = true;
    p[m] = -1;
    int result = -1;
    bool found = false;
    while (!q.empty() && !found) {
        int v = q.front();
        q.pop_front();
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if(!used[to]) {
                used[to] = true;
                q.push_back(to);
                p[to] = v;
            }
            if (X2[to]) {
                found = true;
                result = to;
                break;
            }
        }
    }

    set<int> path;
    for (int v=result; v!=-1; v=p[v])
        path.insert(v);
    return path;
}

int main(int argc, char **argv) {
    unsigned n = 0, m = 0;
    fscanf(fin, "%d %d", &n, &m);

    for (int i = 0, a, b, c; i < m; i++) {
        fscanf(fin, "%d %d %d", &a, &b, &c);
        edges.push_back(edge(--a, --b, --c));
    }

    vector<int> base_parent(n);
    for (int i = 0; i < n; i++) {
        base_parent[i] = i;
    }

    // I1 - multicolored, I2 - spanning forest

    set<int> J;
    J.insert(0); // Start with one edge
    while (true) {
        //printf("===== New iteration =====\n");
        vector<int> left, right; // Left == I, right == S\I
        vector<bool> used_colors(NUM_OF_COLORS, false);

        // FIXME

        set<int>::iterator it = J.begin();
        for (int i = 0; i < m; i++) { // fill used_colors, left and right
            if(it != J.end() && i == *it) {
                left.push_back(i);
                used_colors[edges[i].color] = true;
                it++;
            } else {
                right.push_back(i);
            }
        }

        //printf("LEFT: ");
        for (int i = 0; i < left.size(); i++) {
            //printf("%d ", left[i] + 1);
        }
        //printf("\nRIGHT: ");
        for (int i = 0; i < right.size(); i++) {
            //printf("%d ", right[i] + 1);
        }
        //printf("\n");

        vector<vector<int>> g(m + 1); // exchange graph with one additional vertex
        vector<bool> X2(m, false);

        for (int i = 0; i < right.size(); i++) {
            int z = right[i];
            if(!used_colors[edges[z].color]) {
                g[m].push_back(z); // add edge from additional vertex to X1
            }
            for (int j = 0; j < left.size(); j++) {
                int y = left[j];
                if(edges[y].color == edges[z].color || !used_colors[edges[z].color]) {
                    g[y].push_back(z);
                }
            }
        }

        //printf("\nX1: ");
        for (int i = 0; i < g[m].size(); i++) {
            //printf("%d ", g[m][i] + 1);
        }
        //printf("\n");
        {
            for (int i = 0; i < left.size(); i++) {
                int y = left[i];
                vector<int> p = vector<int>(base_parent.cbegin(), base_parent.cend());

                for (int j = 0; j < left.size(); j++) {
                    int noty = left[j];
                    if(noty != y) {
                        dsu_unite(edges[noty].to, edges[noty].from, p);
                    }
                } // p contains I \ y DSU

                for (int j = 0; j < right.size(); j++) {
                    int z = right[j];
                    if(dsu_get(edges[z].to, p) != dsu_get(edges[z].from, p)) {
                        g[z].push_back(y);
                    }
                }

                dsu_unite(edges[y].to, edges[y].from, p);

                for (int j = 0; j < right.size(); j++) {
                    int z = right[j];
                    if(dsu_get(edges[z].to, p) != dsu_get(edges[z].from, p)) {
                        X2[z] = true;
                    }
                }
            }
        }
        //printf("X2: ");
        for (int i = 0; i < X2.size(); i++) {
            if (X2[i]) {
                //printf("%d ", i + 1);
            }
        }
        //printf("\n");

        for (int i = 0; i < g.size(); i++) {
            //printf("%d: ", i + 1);
            for (int j = 0; j < g[i].size(); j++) {
                //printf("%d ", g[i][j] + 1);
            }
            //printf("\n");
        }

        set<int> P = BFS(g, m, X2); // find shortest path
        P.erase(m);
        // /TODO

        //printf("%d\n", P.size());

        if(P.size() > 0) {
            vector<int> J2(J.size() + P.size());
            vector<int>::iterator it = set_symmetric_difference(J.begin(), J.end(), P.begin(), P.end(), J2.begin());
            J = set<int>(J2.begin(), it);
            //printf("\nJ:\n");
            for (set<int>::iterator it2 = J.begin(); it2 != J.end(); it2++) {
                //printf("%d ", *it2 + 1);
            }
            //printf("\n\n");
        } else {
            break;
        }
    }

    fprintf(fout, "%d\n", J.size());
    for (set<int>::iterator it = J.begin(); it != J.end(); it++) {
        fprintf(fout, "%d ", *it + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}