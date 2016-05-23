#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <unordered_set>

using namespace std;

FILE *fin = fopen("problem5.in", "r");
FILE *fout = fopen("problem5.out", "w");

int n, m, k, l, n_nka, m_nka, k_nka, l_nka
vector<vector<int>> g, g_nka;
vector<bool> T, T_nka;
vector<int> terminal, terminal_nka;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d %d %d", &n_nka, &m_nka, &k_nka, &l_nka);

    T_nka.assign(n_nka, false);
    for(int i = 0, t; i < k_nka; i++) {
        fscanf(fin, "%d", &t);
        T_nka[--t] = true;
        terminal_nka.push_back(t);
    }
    
    g_nka.resize(n_nka);
    char c;
    for(int i = 0, a, b; i < m_nka; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g_nka[--a].push_back(--b);
    }


    vector<set<int>> p;
    queue<set<int>> q;
    set<int> s;
    s.emplace(0);
    q.push(s);


    

    while (!q.empty()) {
		set<int> s = q.front();
		q.pop();
		for (int c = 0; c < 26; c++) {
			//
		}
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
