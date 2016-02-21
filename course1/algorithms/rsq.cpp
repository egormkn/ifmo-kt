#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

FILE *fin = fopen("rsq.in", "r");
FILE *fout = fopen("rsq.out", "w");

const long INF = 0;
long n, n2;
long long a[1048580];

int main() {
    fscanf(fin, "%ld\n", &n);
    n2 = 1<<(int)ceil(log2(n));

    for(long i = n2; i < n2 + n2; i++) {
        if(i < n2 + n) {
            fscanf(fin, "%I64d", &a[i]);
        } else {
            a[i] = INF;
        }
    }

    for(long i = n2-1; i > 0; i--) {
        a[i] = a[2*i] + a[2*i+1];
    }

    char cmd[4] = "   ";
    long long k, m;

    while(!feof(fin)) {
        fscanf(fin, "%3s %I64d %I64d\n", &cmd, &k, &m);

        if(strcmp(cmd, "set") == 0) {
            a[n2+k-1] = m;

            for(long i = (n2+k-1)/2; i > 0; i /= 2) {
                a[i] = a[2*i] + a[2*i+1];
            }
        } else if(strcmp(cmd, "sum") == 0) {
            long long ans = INF;
            long l = k + n2 - 1;
            long r = m + n2 - 1;

            while (l <= r) {
                if (l & 1) {
                    ans += a[l];
                }

                if (!(r & 1)) {
                    ans += a[r];
                }

                l = (l + 1) / 2, r = (r - 1) / 2;
            }

            fprintf(fout, "%I64d\n", ans);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
