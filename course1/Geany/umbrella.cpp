#include <stdio.h>
#include <climits>
#include <algorithm> 
#include <stdlib.h>

using namespace std;
FILE *fin = fopen("umbrella.in", "r");
FILE *fout = fopen("umbrella.out", "w");

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}
 
int main(int argc, char **argv) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);
    int x[5000];
    for (int i = 0; i < n; i++) {
		fscanf(fin, "%d", &x[i]);
    }
    int c[100000];
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d", &c[i]);
    }

    int dp[5000];
    dp[0] = c[0];
    qsort(x, n, sizeof(int), compare);
    for (int i = 1; i < n; i++) {
        int minv = INT_MAX;
        int j = i - 1;
        for (int k = 0; k < m; k++) {
            while (j != -1 && x[i] - x[j] <= k) {
                j--;
            }
            if (j == -1) {
                minv = min(minv, c[k]);
            } else {
                minv = min(minv, dp[j] + c[k]);
            }
        }
        dp[i] = minv;
    }

    fprintf(fout, "%d", dp[n - 1]);
    
    fclose(fin);
    fclose(fout);
    return 0;
}
