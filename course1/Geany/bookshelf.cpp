#include <stdio.h>
#include <climits>
#include <algorithm> 
#include <stdlib.h>

using namespace std;
FILE *fin = fopen("bookshelf.in", "r");
FILE *fout = fopen("bookshelf.out", "w");

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}
 
int main(int argc, char **argv) {
    int n, l;
    fscanf(fin, "%d %d", &n, &l);
    int h[2000], w[2000];
    for (int i = 0; i < n; i++) {
		fscanf(fin, "%d %d", &h[i], &w[i]);
    }
    
    int dp[2000];
    int sumWidth = 0;
    dp[0] = h[0];
    for (int i = 1; i < n; i++) {
        sumWidth = w[i];
        int minv = INT_MAX;
        int maxHeight = h[i];
        for (int k = i - 1; k >= 0; k--) {
            sumWidth += w[k];
            maxHeight = max(maxHeight, h[k]);
            if (sumWidth > l) {
                break;
            }
            if (k == 0) {
                minv = min(minv, maxHeight);
            } else {
                minv = min(minv, dp[k - 1] + maxHeight);
            }
        }
        dp[i] = min(dp[i - 1] + h[i], minv);
    }

    fprintf(fout, "%d", dp[n - 1]);

    fclose(fin);
    fclose(fout);
    return 0;
}
