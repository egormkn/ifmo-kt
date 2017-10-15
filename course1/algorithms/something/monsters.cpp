#include <stdio.h>
#include <climits>
#include <algorithm> 
#include <stdlib.h>

using namespace std;
FILE *fin = fopen("monsters.in", "r");
FILE *fout = fopen("monsters.out", "w");
 
int main(int argc, char **argv) {
    int n;
    long d[50];
    int c[50];
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(fin, "%ld", &d[i]);
	}
    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &c[i]);
	}


    if (n == 1) {
		fprintf(fout, "%d", c[0]);
    } else {
        long dp[50][101];
        dp[0][c[0]] = d[0];
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < 2 * n + 1; j++) {
                if (dp[i][j] != 0) {
                    if (dp[i][j] + d[i + 1] > dp[i + 1][j + c[i + 1]]) {
                        dp[i + 1][j + c[i + 1]] = dp[i][j] + d[i + 1];
                    }
                    if (dp[i][j] >= d[i + 1] && dp[i + 1][j] < dp[i][j]) {
                        dp[i + 1][j] = dp[i][j];
                    }
                }
            }
        }
        int answer = 0;
        for (int i = 0; i < 2 * n + 1; i++) {
            if (dp[n - 1][i] != 0) {
                answer = i;
                break;
            }
        }
        fprintf(fout, "%d", answer);
    }

    
    fclose(fin);
    fclose(fout);
    return 0;
}
