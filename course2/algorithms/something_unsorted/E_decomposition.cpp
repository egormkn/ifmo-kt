#include <cstdio>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

FILE *fin = fopen("decomposition.in", "r");
FILE *fout = fopen("decomposition.out", "w");

const int INF = 2000000000;

struct path {
    int flow;
    deque<int> edges;

    path() : flow(0), edges(deque<int>()) {}

    path(int f, deque<int> e) : flow(f), edges(e) {}
};

struct edge {
    int from, to, capacity, flow;

    edge(int from, int to, int capacity, int flow) : from(from), to(to), capacity(capacity), flow(flow) {}
};

unsigned n, m;
vector<vector<int>> g;
vector<edge> e;

vector<int> ptr, d;

bool bfs() {
    queue<int> queue_of_vertexes;
    queue_of_vertexes.push(0);
    d.assign(n, -1);
    d[0] = 0;
    while (!queue_of_vertexes.empty() && d[n - 1] == -1) {
        int v = queue_of_vertexes.front();
        queue_of_vertexes.pop();
        for (size_t i = 0; i < g[v].size(); ++i) {
            int id = g[v][i], to = e[id].to;
            if(d[to] == -1 && e[id].flow < e[id].capacity) {
                queue_of_vertexes.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d[n - 1] != -1;
}

int dfs(int v, int flow) {
    if(!flow) return 0;
    if(v == n - 1) return flow;
    for (; ptr[v] < g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
                to = e[id].to;
        if(d[to] != d[v] + 1) continue;
        int pushed = dfs(to, min(flow, e[id].capacity - e[id].flow));
        if(pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}


path simpleDecomposition(int s) {
    deque<int> edgepath;
    vector<bool> used(n, false);
    int v = s;

    while (!used[v]) {
        if(v == n - 1) {
            break;
        }

        int temp_edge = -1;

        for (int i = 0; i < g[v].size(); i++) {
            int current = g[v][i];
            if(e[current].flow > 0) {
                temp_edge = current;
                break;
            }
        }

        if(temp_edge == -1) {
            return path();
        }

        edgepath.push_back(temp_edge);
        used[v] = true;
        v = e[temp_edge].to;
    }

    if(used[v]) {
        while (e[edgepath[0]].from != v) {
            edgepath.pop_front();
        }
    }

    int f = INF;

    for (int i = 0; i < edgepath.size(); i++) {
        if(e[edgepath[i]].flow < f) {
            f = e[edgepath[i]].flow;
        }
    }

    for (int i = 0; i < edgepath.size(); i++) {
        e[edgepath[i]].flow -= f;
    }

    if(edgepath.size() == 0) {
        return path();
    }

    return path(f, edgepath);
}

vector<path> fullDecomposition() {
    vector<path> decomposition;
    path p = simpleDecomposition(0);
    while (p.flow < INF && p.flow > 0 && p.edges.size() > 0) {
        decomposition.push_back(p);
        p = simpleDecomposition(0);
    }

    for (int v = 1; v < n - 1; v++) { // v = 1; v < n-1; v++
        p = simpleDecomposition(v);
        while (p.flow < INF && p.flow > 0 && p.edges.size() > 0) {
            decomposition.push_back(p);
            p = simpleDecomposition(v);
        }
    }
    return decomposition;
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);

    g.resize(n);

    d.resize(n);
    ptr.resize(n);

    for (int i = 0, v1, v2, c; i < m; i++) {
        fscanf(fin, "%d %d %d", &v1, &v2, &c);
        v1--;
        v2--;
        edge e1 = { v1, v2, c, 0 };
        edge e2 = { v2, v1, 0, 0 };
        g[v1].push_back(e.size());
        e.push_back(e1);
        g[v2].push_back(e.size());
        e.push_back(e2);
    }




    while (true) {
        if(!bfs()) break;
        ptr.assign(n, 0);
        while (dfs(0, INF)) {}
    }


    vector<path> answer = fullDecomposition();
    fprintf(fout, "%d\n", answer.size());
    for (int i = 0; i < answer.size(); i++) {
        fprintf(fout, "%d %d ", answer[i].flow, answer[i].edges.size());
        for (int j = 0; j < answer[i].edges.size(); j++) {
            fprintf(fout, "%d ", answer[i].edges[j] / 2 + 1);
        }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
