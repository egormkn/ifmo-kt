#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

FILE *fin = fopen("pathsg.in", "r");
FILE *fout = fopen("pathsg.out", "w");

int n, m;
vector<vector<long long>> M;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);
    M.resize(n);
    for(int i = 0; i < n; i++) {
        M[i].assign(n, LLONG_MAX / 2);
        M[i][i] = 0;
    }
    
    long long t;
	for(int i = 0, a, b; i < m; i++) {
		fscanf(fin, "%d %d %I64d", &a, &b, &t);
		M[--a][--b] = t;
	}
    
    for (int i1 = 0; i1 < n; i1++) {
		for (int j2 = 0; j2 < n; j2++) {
			for (int k3 = 0; k3 < n; k3++) {
				M[j2][k3] = min(M[j2][k3], M[j2][i1] + M[i1][k3]);
			}
		}
	}

    for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			fprintf(fout, "%I64d ", M[i][j]);
		}
		fprintf(fout, "\n");
	}
    fclose(fin);
    fclose(fout);
    return 0;
}
