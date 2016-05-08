#include <cstdio>
#include <vector>
#include <cmath>
 
using namespace std;
 
FILE *fin = fopen("absmarkchain.in", "r");
FILE *fout = fopen("absmarkchain.out", "w");
 
int main(int argc, char **argv) {
	const double eps = 1e-8;
    int n, m, nonabs, abs = 0;
    fscanf(fin, "%d %d", &n, &m);
    vector<int> a, b;
    vector<double> p;
    vector<bool> absorbing(m, false);
    double pt;
    for(int i = 0, at, bt; i < m; i++) {
		fscanf(fin, "%d %d %lf", &at, &bt, &pt);
		at--;
		bt--;
		a.push_back(at);
		b.push_back(bt);
		p.push_back(pt);
		if(at == bt && fabs(pt - 1.0) < eps) {
            absorbing[at] = true;
            abs++;
		}
	}
	nonabs = n - abs;
    
    vector<vector<double>> R(n), Q(n), G(n);
    
    vector<int> position(n);
    int count_q = 0, count_r = 0;
    for(int i = 0; i < n; i++) {
        if(absorbing[i]) {
            position[i] = count_r;
            count_r++;
        } else { 
            position[i] = count_q;
            count_q++;
		}
		R[i].resize(n);
		Q[i].resize(n);
		G[i].resize(n);
	}
	
    for(int i = 0; i < m; i++) {
        if(absorbing[b[i]]) {
            if(!absorbing[a[i]]){
                R[position[a[i]]][position[b[i]]] = p[i];
			}
        } else {
            Q[position[a[i]]][position[b[i]]] = p[i];
		}
    }

    vector<vector<double>> N(nonabs), E(nonabs);
	
    for(int i = 0; i < nonabs; i++) {
		N[i].resize(nonabs);
		E[i].resize(nonabs);
        N[i][i] = 1.0;
        E[i][i] = 1.0;
        for(int j = 0; j < nonabs; j++) {
            E[i][j] -= Q[i][j];
	    }
    }

    double mul;
    for(int i = 0; i < nonabs; i++) {
        if(fabs(E[i][i] - 1.0) > eps) {
            mul = E[i][i];
            for(int j = 0; j < nonabs; j++) {
                E[i][j] /= mul;
                N[i][j] /= mul;
			}
		}
        for(int row = 0; row < nonabs; row++) {
            if(i != row) {
                mul = E[row][i];
                for(int j = 0; j < nonabs; j++) {
                    E[row][j] -= mul * E[i][j];
                    N[row][j] -= mul * N[i][j];
				}
			}
		}
	}

    for(int i = 0; i < nonabs; i++) {
        for(int j = 0; j < abs; j++) {
            G[i][j] = 0.0;
            for(int k = 0; k < nonabs; k++) {
                G[i][j] += N[i][k] * R[k][j];
			}
		}
	}
          
    for(int i = 0; i < n; i++) {
        double prob = 0;
        if(absorbing[i]) {
            for(int j = 0; j < nonabs; j++) {
                prob += G[j][position[i]];
			}
            prob += 1;
            prob /= n;
		}
        fprintf(fout, "%f\n", prob);
	}
    
    fclose(fin);
    fclose(fout);
    return 0;
}
