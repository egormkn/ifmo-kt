#include <iostream>
#include <fstream>

using namespace std;

FILE *fin = fopen("bureaucracy.in", "r");
FILE *fout = fopen("bureaucracy.out", "w");
long n, m, s;
int a[1000000];

int main() {
    fscanf(fin, "%ld %ld", &n, &m);
    for(int i = 0; i < n; i++) {
        fscanf(fin, "%d", &a[i]);
    }

    while(m >= n && n > 0) {
        long t = m / n;
        m = m % n;
        s = 0;
        for(int i = 0; i < n; i++) {
            a[i] -= t;

            if(a[i] <= 0) {
                m -= a[i];
            } else {
                a[s++] = a[i];
            }
        }

        n = s;
    }

    if(n == 0) {
        fprintf(fout, "-1");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    s = 0;
    for(int i = 0; i < m; i++) {
        if(--a[i] == 0) {
            s++;
        }
    }

    fprintf(fout, "%ld\n", n-s);
    for(int i = m; i < n+m; i++) {
        if(i < n || a[i%n] != 0) {
            fprintf(fout, "%d ", a[i%n]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
