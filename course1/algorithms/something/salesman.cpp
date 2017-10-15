#include <stdio.h>
#include <climits>
#include <algorithm> 
#include <stdlib.h>

using namespace std;
FILE *fin = fopen("salesman.in", "r");
FILE *fout = fopen("salesman.out", "w");
 
int main(int argc, char **argv) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);

    const long long longMax = 10000000001L;
    long long arc[18][18];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arc[i][j] = longMax;
        }
    }

    int a, b, w;
    for(int i = 0; i < m; i++){
		fscanf(fin, "%d %d %d", &a, &b, &w);
		arc[a - 1][b - 1] = w;
        arc[b - 1][a - 1] = w;
	}
    
    long long dp[18][262144];
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == (1 << j)) {
                dp[j][i] = 0;
            } else {
                dp[j][i] = longMax;
            }
        }
    }

    long long answer = longMax;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            int temp = i & (1 << j);
            if (temp == 0) {
                continue;
            }
            for (int k = 0; k < n; k++) {
                int temp1 = i & (1 << k);
                if (temp1 == 0) {
                    int temp2 = i + (1 << k);
                    if (dp[k][temp2] >= dp[j][i] + arc[k][j]) {
                        dp[k][temp2] = dp[j][i] + arc[k][j];
                    }
                }
            }
            if (i == (1 << n) - 1) {
                answer = min(answer, dp[j][i]);
            }
        }
    }

    if (answer == longMax) {
		fprintf(fout, "-1");
    } else {
		fprintf(fout, "%I64d", answer);
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}
