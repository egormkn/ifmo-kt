#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct warrior {
    long left;
    long right;
};

FILE *fin = fopen("formation.in", "r");
FILE *fout = fopen("formation.out", "w");
warrior a[75001];
long n, m;

int main() {
    fscanf(fin, "%ld %ld\n", &n, &m);
    char c[256];
    long i, j;

    for(int k = 1; k <= n; k++) {
        a[k].left = 0;
        a[k].right = 0;
    }

    for(int k = 0; k < m; k++) {
        fscanf(fin, "%s", c);
        string cmd = c;

        if(cmd == "left") {
            fscanf(fin, "%ld %ld\n", &i, &j);
            a[i].right = j;

            if(a[j].left != 0) {
                a[a[j].left].right = i;
                a[i].left = a[j].left;
            }

            a[j].left = i;
        } else if(cmd == "right") {
            fscanf(fin, "%ld %ld\n", &i, &j);
            a[i].left = j;

            if(a[j].right != 0) {
                a[a[j].right].left = i;
                a[i].right = a[j].right;
            }

            a[j].right = i;
        } else if(cmd == "leave") {
            fscanf(fin, "%ld\n", &i);
            a[a[i].left].right = a[i].right;
            a[a[i].right].left = a[i].left;
            a[i].left = 0;
            a[i].right = 0;
        } else if(cmd == "name") {
            fscanf(fin, "%ld\n", &i);
            fprintf(fout, "%ld %ld\n", a[i].left, a[i].right);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
