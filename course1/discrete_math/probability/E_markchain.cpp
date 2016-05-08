#include <cstdio>
#include <vector>
#include <cmath>
 
using namespace std;
 
FILE *fin = fopen("markchain.in", "r");
FILE *fout = fopen("markchain.out", "w");

bool unstable(vector<vector<double>>& A, vector<vector<double>>& B) {
    bool changed = false;
	int n = A.size();
    vector<vector<double>> T(n);
    for(int i = 0; i < n; i++) {
		T[i].assign(n, 0.0);
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				T[i][j] += A[i][k] * B[k][j];
			}
			if(fabs(T[i][j] - A[i][j]) > 1e-7){
				changed = true;
			}
		}
	}
    A = T;
	return changed;
}

int main(int argc, char **argv) {
	int n;
    fscanf(fin, "%d", &n);
	vector<vector<double>> G(n), R(n);
    for(int i = 0; i < n; i++) {
		G[i].resize(n);
		R[i].assign(n, 0.0);
		R[i][i] = 1.0;
		for(int j = 0; j < n; j++) {
			fscanf(fin, "%lf", &G[i][j]);
		}
	}
    for(;unstable(R, G);); // Magic :D
	for(int i = 0; i < n; i++) {
		fprintf(fout, "%f\n", R[0][i]);
	}
    fclose(fin);
    fclose(fout);
    return 0;
}
