#include <stdio.h>

using namespace std;
FILE *fin = fopen("knapsack.in", "r");
FILE *fout = fopen("knapsack.out", "w");

int main(int argc, char **argv) {
    int n, m, k = 0, M[2000], C[2000];
    fscanf(fin, "%d %d", &n, &m);
    for (int i = 0; i < n; i++){
        fscanf(fin, "%d", &M[i]);
    }
    for (int i = 0; i < n; i++){
        fscanf(fin, "%d", &C[i]);
    }
    
    int knapsack[1001][10001];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            if (i == 0 || j == 0) {
                knapsack[i][j] = 0;
                continue;
            }
            if (j - M[i - 1] < 0) {
                knapsack[i][j] = knapsack[i - 1][j];
                continue;
            }
            if (knapsack[i - 1][j] > knapsack[i - 1][j - M[i - 1]] + C[i - 1]) {
                knapsack[i][j] = knapsack[i - 1][j];
            } else {
                knapsack[i][j] = knapsack[i - 1][j - M[i - 1]] + C[i - 1];
            }
        }
    }

    int i = n, j = m;
    bool result[1000];
    while (i > 0 && j > 0) {
        if (j - M[i - 1] < 0) {
            i--;
            continue;
        }
        if (knapsack[i - 1][j] > knapsack[i - 1][j - M[i - 1]] + C[i - 1]) {
            i--;
        } else {
            result[i - 1] = true;
            j -= M[i - 1];
            i--;
            k++;
        }
    }

    fprintf(fout, "%d\n", k);
    for (int i = 0; i < n; i++) {
        if (result[i]) {
            fprintf(fout, "%d ", i + 1);
        }
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}
