#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("problem3.in", "r");
FILE *fout = fopen("problem3.out", "w");

vector<vector<int>> g, gr;
vector<bool> useful;

void dfs_useful (int v) {
    useful[v] = true;
    for (size_t i = 0; i < gr[v].size(); i++) {
        if (!useful[gr[v][i]]) {
            dfs_useful(gr[v][i]);
        }
    }
}

enum cl {white, gray, black};
vector<cl> color;
vector<int> topsort;

bool top_sort(int v) {
	color[v] = gray;
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == white) {
			if (top_sort(to)) {
				return true;
		    }
		} else if (useful[to] && color[to] == gray) {
			return true;
		}
	}
	color[v] = black;
	topsort.push_back(v);
	return false;
}

int main(int argc, char **argv) {
    int n, m, k;
    fscanf(fin, "%d %d %d", &n, &m, &k);

    vector<bool> T(n, false);
    vector<int> terminal;
    for(int i = 0, t; i < k; i++) {
        fscanf(fin, "%d", &t);
        terminal.push_back(--t);
        T[t] = true;
    }
    
    g.resize(n);
    gr.resize(n);
    char c;
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g[--a].push_back(--b);
        gr[b].push_back(a);
    }

    useful.assign(n, false);
    for(int i = 0; i < k; i++) {
        dfs_useful(terminal[i]);
    }

    color.assign(n, white);
    bool has_cycle = top_sort(0);
    if(has_cycle){
        fprintf(fout, "-1\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    reverse(topsort.begin(), topsort.end());
    
    int answer = 0;
    vector<int> paths(n, 0);
    paths[0] = 1;
    for(size_t i = 0; i < topsort.size(); i++) {
        int to = topsort[i];
        for (size_t j = 0; j < gr[to].size(); j++) {
            paths[to] = (paths[to] + paths[gr[to][j]]) % 1000000007;
        }
    }

    for(size_t i = 0; i < terminal.size(); i++) {
        answer = (answer + paths[terminal[i]]) % 1000000007;
	}
    fprintf(fout, "%d\n", answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
