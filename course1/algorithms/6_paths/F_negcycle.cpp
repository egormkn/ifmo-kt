#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <climits>

using namespace std;

FILE *fin = fopen("negcycle.in", "r");
FILE *fout = fopen("negcycle.out", "w");

struct edge {
	int a, b, cost;
};

int n, m = 0;
vector<edge> e;
const int INF = 1000000000;

int main(int argc, char **argv) {
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++) {
		for(int j = 0, w; j < n; j++) {
            fscanf(fin, "%d", &w);
			if (w != INF) {
				edge t;
				t.a = i;
				t.b = j;
				t.cost = w;
				e.push_back(t);
				m++;
			}
		}
    }


    vector<int> d(n), p(n, -1);
	int x;
	for (int i = 0; i < n; i++) {
		x = -1;
		for (int j = 0; j < m; j++) {
			if (d[e[j].b] > d[e[j].a] + e[j].cost) {
				d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
				p[e[j].b] = e[j].a;
				x = e[j].b;
			}
		}
	}
 
	if (x == -1) {
		fprintf(fout, "NO");
	} else {
		int y = x;
		for (int i = 0; i < n; i++) {
			y = p[y];
		}
 
		vector<int> path;
		for (int cur = y; ; cur = p[cur]) {
			path.push_back(cur);
			if (cur == y && path.size() > 1) {
				break;
			}
		}
		reverse(path.begin(), path.end());
 
		fprintf(fout, "YES\n%d\n", path.size());
		for (size_t i = 0; i < path.size(); i++) {
			fprintf(fout, "%d ", path[i] + 1);
		}
	}


    fclose(fin);
    fclose(fout);
    return 0;
}
