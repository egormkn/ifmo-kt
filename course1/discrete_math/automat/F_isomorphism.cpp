#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("isomorphism.in", "r");
FILE *fout = fopen("isomorphism.out", "w");

vector<vector<int>> g1, g2;
vector<bool> used;
vector<bool> T1, T2;

bool dfs_isomorphism (int u, int v) { 
    used[u] = true;
    if (T1[u] != T2[v]) {
        return false;
    }
     
    bool result = true;
    for (size_t i = 0; i < 26; i++) {     
        int t1 = g1[u][i], t2 = g2[v][i];
        if ((t1 == -1 || t2 == -1) && t2 != t1) {
            return false;
		}
        if (t1 > 0 && !used[t1]) {
            result = result && dfs_isomorphism(t1, t2);
		}             
    }
    return result;
}

int main(int argc, char **argv) {
    int n1, m1, k1;
    fscanf(fin, "%d %d %d", &n1, &m1, &k1);

    T1.assign(n1, false);
    for(int i = 0, t; i < k1; i++) {
        fscanf(fin, "%d", &t);
        T1[--t] = true;
    }
    
    g1.resize(n1);
    for(int i = 0; i < n1; i++) {
		g1[i].assign(26, -1);
	}
    char c;
    for(int i = 0, a, b; i < m1; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g1[--a][c - 'a'] = --b;
    }

    
    int n2, m2, k2;
    fscanf(fin, "%d %d %d", &n2, &m2, &k2);

    T2.assign(n2, false);
    for(int i = 0, t; i < k2; i++) {
        fscanf(fin, "%d", &t);
        T2[--t] = true;
    }
    
    g2.resize(n2);
    for(int i = 0; i < n2; i++) {
		g2[i].assign(26, -1);
	}
    for(int i = 0, a, b; i < m2; i++) {
        fscanf(fin, "%d %d %c", &a, &b, &c);
        g2[--a][c - 'a'] = --b;
    }

    /*if (n1 != n2 || m1 != m2 || k1 != k2) {
		fprintf(fout, "NO");
		fclose(fin);
        fclose(fout);
        return 0;
	}*/

    used.assign(n1, false);

    
    fprintf(fout, dfs_isomorphism(0, 0) ? "YES" : "NO");
    fclose(fin);
    fclose(fout);
    return 0;
}
