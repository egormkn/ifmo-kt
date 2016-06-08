#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Time {
    int h;
    int m;
};

FILE *fin = fopen("saloon.in", "r");
FILE *fout = fopen("saloon.out", "w");
int n, l, head = 0, tail = 0;
Time t;
Time q[100];

int main() {
    fscanf(fin, "%d\n", &n);

    for(int i = 0; i < n; i++) {
        fscanf(fin, "%d %d %d\n", &t.h, &t.m, &l);

        while(head != tail && (t.h > q[head].h || (t.h == q[head].h && t.m >= q[head].m))) {
            head++;
        }

        if(head == tail) {
            q[tail].h = (t.h + (t.m >= 40 ? 1 : 0))%24;
            q[tail].m = (t.m+20)%60;
            fprintf(fout, "%d %d\n", q[tail].h, q[tail].m);
            tail++;
        } else if(tail-head > l) {
            fprintf(fout, "%d %d\n", t.h, t.m);
        } else {
            q[tail].h = q[tail-1].h + (q[tail-1].m >= 40 ? 1 : 0);
            q[tail].m = (q[tail-1].m+20)%60;
            fprintf(fout, "%d %d\n", q[tail].h, q[tail].m);
            tail++;
        }
    }

    return 0;
}
