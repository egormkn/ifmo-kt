#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;

FILE *fin = fopen("problem4.in", "r");
FILE *fout = fopen("problem4.out", "w");

int n, m, k, l;
vector<vector<int>> g;
vector<bool> T;
vector<int> terminal;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d %d %d", &n, &m, &k, &l);

    T.assign(n, false);
    for(int i = 0, t; i < k; i++) {
        fscanf(fin, "%d", &t);
        T[--t] = true;
        terminal.push_back(t);
    }
    
    g.resize(n);
    char c;
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g[--a].push_back(--b);
    }

    vector<int> d(n, 0);
    d[0] = 1;



    unordered_set<int> states;
    states.emplace(0);
    
	for(int i = 0; i < l; i++) {
		unordered_set<int> temp;
		vector<int> tempd(n, 0);
		for(auto it = states.begin(); it != states.end(); it++) {
			for(unsigned j = 0; j < g[*it].size(); j++) {
				int to = g[*it][j];
				tempd[to] = (tempd[to] + d[*it]) % 1000000007;
				temp.emplace(to);
			}
		}
		states = temp;
		d = tempd;
	}


    int answer = 0;
    for(size_t i = 0; i < d.size(); i++) {
		if(T[i]) {
			answer = (answer + d[i]) % 1000000007;
		}
	}

    fprintf(fout, "%d", answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
