#include <stdio.h>

using namespace std;
FILE *fin = fopen("lcs.in", "r");
FILE *fout = fopen("lcs.out", "w");
 
int main(int argc, char **argv) {
    int n, m, X[2000], Y[2000];
    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++){
        fscanf(fin, "%d", &X[i]);
    }
    fscanf(fin, "%d", &m);
    for (int i = 0; i < m; i++){
        fscanf(fin, "%d", &Y[i]);
    }

	int lcs[2001][2001];
	
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            if (i == 0 || j == 0) {
                lcs[i][j] = 0;
                continue;
            }
            if (X[i - 1] == Y[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                continue;
            }
            if (lcs[i - 1][j] >= lcs[i][j - 1]) {
                lcs[i][j] = lcs[i - 1][j];
            } else {
                lcs[i][j] = lcs[i][j - 1];
            }
        }
    }

    int i = n, j = m;
    int result[2000];
    int k = 0;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result[k] = X[i - 1];
            k++;
            i--;
            j--;
            continue;
        }
        if (lcs[i - 1][j] >= lcs[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    fprintf(fout, "%d\n", lcs[n][m]);
    for (int i = lcs[n][m] - 1; i >= 0; i--) {
        fprintf(fout, "%d ", result[i]);
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}
