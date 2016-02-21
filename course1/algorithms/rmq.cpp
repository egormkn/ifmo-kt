#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

FILE *fin = fopen("rmq.in", "r");
FILE *fout = fopen("rmq.out", "w");

const long INF = 1000000000;
long n, n2;
long a[1048580];

long min(long a, long b){
    if(a < b){
        return a;
    }
    return b;
}

int main() {
    fscanf(fin, "%ld\n", &n);
    n2 = 1<<(int)ceil(log2(n));

    for(long i = n2; i < n2 + n2; i++) {
        if(i < n2 + n) {
            fscanf(fin, "%ld", &a[i]);
        } else {
            a[i] = INF;
        }
    }

    for(long i = n2-1; i > 0; i--) {
        a[i] = min(a[2*i], a[2*i+1]);
    }

    char cmd[4] = "   ";
    long k, m;

    while(!feof(fin)) {
        fscanf(fin, "%3s %ld %ld\n", &cmd, &k, &m);

        if(strcmp(cmd, "set") == 0) {
            a[n2+k-1] = m;

            for(long i = (n2+k-1)/2; i > 0; i /= 2) {
                a[i] = min(a[2*i], a[2*i+1]);
            }
        } else if(strcmp(cmd, "min") == 0) {
            long ans = INF;
            long l = k + n2 - 1;
            long r = m + n2 - 1;

            while (l <= r) {
                if (l & 1) {
                    ans = min(ans, a[l]);
                }

                if (!(r & 1)) {
                    ans = min(ans, a[r]);
                }

                l = (l + 1) / 2, r = (r - 1) / 2;
            }

            fprintf(fout, "%ld\n", ans);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
