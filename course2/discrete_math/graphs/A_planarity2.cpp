#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

struct edge {
    int from, to;

    edge(int a, int b) : from(a), to(b) {}

    edge(const edge &a) : from(a.from), to(a.to) {}

    void swap() {
        int t = to;
        to = from;
        from = t;
    }

    static void swap(edge &a, edge &b) {
        edge t(a.from, a.to);
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

void dfs(unsigned v, unsigned color, vector<edge> &edges, vector<unsigned> &cycle, vector<unsigned> &colors) {
    colors[v] = color;
    for (int i = 0; i < edges.size(); i++) {
        if(crossing(edges[v], edges[i], cycle)) {
            if(colors[i] == 0) {
                dfs(i, 3 - color, edges, cycle, colors);
            } else {
                if(colors[i] == colors[v]) {
                    printf("NO\n");
                    exit(0);
                }
            }
        }
    }
}


int main() {
    unsigned n, m;
    scanf("%u %u", &n, &m);

    vector<edge> edges;
    for (unsigned i = 0, from, to; i < m; i++) {
        scanf("%u %u", &from, &to);
        edges.push_back(edge(--from, --to));
    }

    vector<unsigned> cycle(n), colors(n, 0);
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
        if(colors[i] == 0) {
            dfs(i, 1, edges, cycle, colors);
        }
    }

    printf("YES\n");
    for (unsigned i = 0; i < n; i++) {
        printf("%u 0 ", cycle[i]);
    }
    printf("\n");

    for (unsigned i = 0; i < m; i++) {
        double a = (double) (cycle[edges[i].from] + cycle[edges[i].to]) / 2;
        double b = abs((double) (cycle[edges[i].to] - cycle[edges[i].from])) / 2;
        printf("%lf %lf\n", a, colors[i] == 1 ? b : -b);
    }

    return 0;
}