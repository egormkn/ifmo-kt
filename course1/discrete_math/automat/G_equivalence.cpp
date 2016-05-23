#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

FILE *fin = fopen("equivalence.in", "r");
FILE *fout = fopen("equivalence.out", "w");

vector<vector<int>> g1, g2;
vector<bool> used1, used2;
vector<bool> T1, T2;

bool bfs_equivalence(int s1, int s2) {
	queue<pair<int, int>> q;
	q.push(make_pair(s1, s2));
	used1[s1] = true;
	used2[s2] = true;
    while (!q.empty()) {
        int t1 = q.front().first, t2 = q.front().second;
        q.pop();
        if (T1[t1] != T2[t2]) {
			return false;
		}
		for (char c = 0; c < 26; c++) {
            int v1 = g1[t1][c], v2 = g2[t2][c];
			if (!used1[v1] || !used2[v2]) {
				q.push(make_pair(v1, v2));
				used1[v1] = true;
				used2[v2] = true;
			}
		}
	}
    return true;
}

int main(int argc, char **argv) {
    int n1, m1, k1;
    fscanf(fin, "%d %d %d", &n1, &m1, &k1);

    T1.assign(n1 + 1, false);
    for(int i = 0, t; i < k1; i++) {
        fscanf(fin, "%d", &t);
        T1[--t] = true;
    }
    
    g1.resize(n1 + 1);
    for(int i = 0; i <= n1; i++) {
		g1[i].assign(26, n1);
	}
    char c;
    for(int i = 0, a, b; i < m1; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g1[--a][c - 'a'] = --b;
    }

    
    int n2, m2, k2;
    fscanf(fin, "%d %d %d", &n2, &m2, &k2);

    T2.assign(n2 + 1, false);
    for(int i = 0, t; i < k2; i++) {
        fscanf(fin, "%d", &t);
        T2[--t] = true;
    }
    
    g2.resize(n2 + 1);
    for(int i = 0; i <= n2; i++) {
		g2[i].assign(26, n2);
	}
    for(int i = 0, a, b; i < m2; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g2[--a][c - 'a'] = --b;
    }

    used1.assign(n1 + 1, false);
    used2.assign(n2 + 1, false);

    fprintf(fout, bfs_equivalence(0, 0) ? "YES" : "NO");
    fclose(fin);
    fclose(fout);
    return 0;
}
