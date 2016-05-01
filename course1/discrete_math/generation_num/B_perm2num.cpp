#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("perm2num.in", "r");
FILE *fout = fopen("perm2num.out", "w");

const int MAXN = 18;
int n, perm[MAXN];
long long k, factorial[MAXN + 1];
bool used[MAXN];

int main(int argc, char **argv) {
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &perm[i]);
	}
    factorial[0] = 1;
    factorial[1] = 1;
    for (int i = 2; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    
    k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < perm[i] - 1; j++) {
            if (!used[j]) {
                k += factorial[n - i - 1];
            }
        }
        used[perm[i] - 1] = true;
    }
    
    fprintf(fout, "%I64d", k);

    fclose(fin);
    fclose(fout);
    return 0;
}
