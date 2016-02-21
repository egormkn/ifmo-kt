#include <stdio.h>
#include <stdlib.h>

using namespace std;

FILE *fin = fopen("hemoglobin.in", "r");
FILE *fout = fopen("hemoglobin.out", "w");
int n, k, last = 0;
long l;
char c;
unsigned long a[50001];
unsigned long h[50001];

int main() {
    fscanf(fin, "%d\n", &n);

    for(int i = 0; i < n; i++) {
        fscanf(fin, "%c", &c);

        if(c == '+') {
            fscanf(fin, "%ld\n", &l);
            h[last] = l;
            a[last] = (last > 0) ? a[last-1] + l : l;
            last++;
        } else if(c == '?') {
            fscanf(fin, "%d\n", &k);
            fprintf(fout, "%lu\n", (k == last) ? a[last-1] : a[last-1]-a[last-k-1]);
        } else if(c == '-') {
            fscanf(fin, "\n");
            last--;
            fprintf(fout, "%ld\n", h[last]);
        }
    }

    return 0;
}
