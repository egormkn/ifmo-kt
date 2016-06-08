#include <stdio.h>
#include <stdlib.h>
//#include <iostream>

using namespace std;

FILE *fin = fopen("stack-min.in", "r");
FILE *fout = fopen("stack-min.out", "w");
long st[1000000];
long m[1000000];
long n = 0, k;

long min(long a, long b){
    if(a < b){
        return a;
    } else {
        return b;
    }
}

int main() {
    fscanf(fin, "%ld", &k);
    short cmd;
    long num;

    for(long i = 0; i < k; i++) {
        //fin >> cmd;
        fscanf(fin, "%hd", &cmd);
        switch(cmd) {
        case 1:
            //fin >> num;
            fscanf(fin, "%ld", &num);
            m[n] = (n > 0) ? min(m[n-1], num) : num;
            st[n++] = num;
            break;

        case 2:
            n--;
            break;

        case 3:
            fprintf(fout, "%ld\n", m[n-1]);
            //fout << m[n-1] << endl;
            break;
        }
    }


    fclose(fin);
    fclose(fout);
    //fin.close();
    //fout.close();
    return 0;
}
