#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("num2perm.in", "r");
FILE *fout = fopen("num2perm.out", "w");

const int MAXN = 18;
int n, result[MAXN];
long long k, factorial[MAXN + 1];
bool used[MAXN];

int main(int argc, char **argv) {
    fscanf(fin, "%d %I64d", &n, &k);
    factorial[0] = 1;
    factorial[1] = 1;
    for (int i = 2; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    long long temp;
    int pos;
    for (int i = 1; i <= n; i++) {
        temp = k / factorial[n - i];
        k %= factorial[n - i];
        pos = 0;
        for (int j = 1; j <= n; j++) {
            if (!used[j - 1]) {
                pos++;
                if (pos == temp + 1) {
                    result[i - 1] = j;
                    used[j - 1] = true;
                }
            }
        }
    }

    
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d ", result[i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
