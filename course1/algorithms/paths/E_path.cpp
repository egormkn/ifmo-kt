#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

FILE *fin = fopen("path.in", "r");
FILE *fout = fopen("path.out", "w");

struct edge {
	int a, b;
	long long cost;
};

int n, m, s;
vector<edge> e;
vector<vector<int>> g;
vector<bool> infmin;
const long long INF = LLONG_MAX / 2;

void dfs(int v) {
    if (infmin[v]) {
        return;
    }
    infmin[v] = true;
    for(size_t i = 0; i < g[v].size(); i++) {
        dfs(g[v][i]);
    }
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d %d", &n, &m, &s);
    s--;
    g.resize(n);
    long long w;
    for(int i = 0, a, b; i < m; i++) {
		fscanf(fin, "%d %d %I64d", &a, &b, &w);
		edge t;
		t.a = --a;
		t.b = --b;
		t.cost = w;
		e.push_back(t);
        g[a].push_back(b);
    }


    infmin.assign(n, false);
	vector<long long> d(n, INF);
	d[s] = 0;
    for (int i = 0; i <= n; i++) {
        // bool any = false;
		for (int j=0; j<m; ++j) {
			if (d[e[j].a] < INF) {
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
					// any = true;
                    if (i == n) {
                        dfs(e[j].b);
                    }
				}
            }
        }
		/*if (!any) {
            break;
        }*/
	}

    for (int i = 0; i < n; i++) {
        if (infmin[i]) {
            fprintf(fout, "-\n");
        } else if (d[i] == INF) {
            fprintf(fout, "*\n");
        } else {
            fprintf(fout, "%I64d\n", d[i]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
