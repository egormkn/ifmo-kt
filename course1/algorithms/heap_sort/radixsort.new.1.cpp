#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin;
ofstream fout;
int n,k,m,i;
string a[1000];
string b[1000];

void radixsort(int by) {
    char c[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(int j = 0; j < n; j++) {
        c[int(a[j][by])]++;
        b[j] = "";
    }
    b[n] = "";
    int tmp2,tmp = c[0];
    c[0] = 0;
    for(int j = 1; j<256; j++) {
        tmp2 = c[j];
        c[j] = c[j-1]+tmp;
        tmp = tmp2;
    }
    int p;
    for(int j = 0; j < n; j++) {
        p = c[int(a[j][by])];
        while(!b[p].empty()) {
            p++;
        }
        b[p] = a[j];
    }
    for(int j = 0; j < n; j++) {
        a[j] = b[j];
    }
}

int main() {
    fin.open("radixsort.in");
    fout.open("radixsort.out");
    fin >> n >> m >> k;
    for(i = 0; i < n; i++) {
        fin >> a[i];
    }
    for(i = 1; i <= k; i++) {
        radixsort(m-i);
    }
    for(i = 0; i < n; i++) {
        fout << a[i] << endl;
    }
    return 0;
}
