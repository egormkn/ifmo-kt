#include <stdio.h>

using namespace std;
FILE *fin = fopen("concert.in", "r");
FILE *fout = fopen("concert.out", "w");
 
int main(int argc, char **argv) {
    int n, b, m, d[51];
    fscanf(fin, "%d", &n);
	for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &d[i]);
	}
	fscanf(fin, "%d %d", &b, &m);

    bool dp[50][1001];
    for (int i = 0; i <= m; i++) {
        if (i == b + d[0] || i == b - d[0]) {
            dp[0][i] = true;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (j - d[i] >= 0 && dp[i - 1][j - d[i]]) {
                dp[i][j] = true;
            } else if (j + d[i] <= m && dp[i - 1][j + d[i]]) {
                dp[i][j] = true;
            }
        }
    }

    for (int i = m; i >= 0; i--) {
        if (dp[n - 1][i]) {
            fprintf(fout, "%d", i);
            fclose(fin);
            fclose(fout);
            return 0;
        }
    }
    fprintf(fout, "-1\n");
    fclose(fin);
    fclose(fout);
    return 0;
}
