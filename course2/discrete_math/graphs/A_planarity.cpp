#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

struct edge {
    int from, to, color = 0;

    edge(int a, int b) : from(a), to(b) {}

    edge(const edge &a) : from(a.from), to(a.to) {}

    void swap() {
        int t = to;
        to = from;
        from = t;
    }

    static void swap(edge &a, edge &b) {
        edge t(a);
        a = edge(b);
        b = edge(t);
    }
};

bool crossing(edge a, edge b, vector<unsigned> &cycle) {
    if(cycle[a.from] > cycle[b.from]) {
        edge::swap(a, b); // A.from should go before B.from
    } // Returns true, if a.from < b.from < a.to < b.to
    return (cycle[a.from] < cycle[b.from] && cycle[b.from] < cycle[a.to] && cycle[a.to] < cycle[b.to]);
}

bool dfs(unsigned v, int color, vector<edge> &edges, vector<unsigned> &cycle) {
    edges[v].color = color;
    for (unsigned i = 0; i < edges.size(); i++) {
        if(crossing(edges[v], edges[i], cycle)) {
            if(edges[i].color == 0) {
                bool result = dfs(i, -color, edges, cycle);
                if (!result) {
                    return false;
                }
            } else if(edges[i].color == edges[v].color) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    unsigned n, m;
    scanf("%u %u", &n, &m);

    vector<edge> edges;
    for (unsigned i = 0, from, to; i < m; i++) {
        scanf("%u %u", &from, &to);
        edges.push_back(edge(--from, --to));
    }

    vector<unsigned> cycle(n);
    for (unsigned i = 0, v; i < n; i++) {
        scanf("%u", &v);
        cycle[--v] = i;
    }

    for (unsigned i = 0; i < m; i++) {
        if(cycle[edges[i].to] < cycle[edges[i].from]) {
            edges[i].swap();
        }
    }

    for (unsigned i = 0; i < m; i++) {
        if(edges[i].color == 0) {
            bool result = dfs(i, 1, edges, cycle);
            if (!result) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%u 0 ", cycle[i]);
    }
    printf("\n");

    for (unsigned i = 0; i < m; i++) {
        double a = (double) (cycle[edges[i].from] + cycle[edges[i].to]) / 2;
        double b = abs(cycle[edges[i].to] - cycle[edges[i].from]) / 2;
        printf("%lf %lf\n", a, edges[i].color * b);
    }

    return 0;
}