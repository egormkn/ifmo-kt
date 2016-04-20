#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("cycle.in", "r");
FILE *fout = fopen("cycle.out", "w");

const int MAXN = 100000 + 1;
int n = 1, m = 0;
vector<int> g[MAXN];
enum {white, gray, black} color[MAXN];
vector<int> p;
int cycle_st = -1, cycle_end = -1;
 
bool dfs (int v) {
	color[v] = gray;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (color[to] == white) {
			p[to] = v;
			if(dfs(to)){
				return true;
			}
		} else if(color[to] == gray) {
			cycle_end = v;
			cycle_st = to;
			return true;
		}
	}
	color[v] = black;
	return false;
}

int main(int argc, char **argv) {
	fscanf(fin, "%d %d", &n, &m);
	for(int i = 0, v1, v2; i < m; i++){
        fscanf(fin, "%d %d", &v1, &v2);
        g[v1].push_back(v2);
	}
    for (int i = 1; i <= n; i++){
		color[i] = white;
	}
	p.assign(n + 1, -1);

    for (int i = 1; i <= n; i++){
		if(dfs(i)){
			break;
		}
	}

	if (cycle_st == -1){
		fprintf(fout, "NO\n");
	} else {
		fprintf(fout, "YES\n");
		vector<int> cycle;
		cycle.push_back(cycle_st);
		for (int v = cycle_end; v != cycle_st; v = p[v]){
			cycle.push_back(v);
		}
		reverse(cycle.begin(), cycle.end());
		for (size_t i = 0; i < cycle.size(); i++){
			fprintf(fout, "%d ", cycle[i]);
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
