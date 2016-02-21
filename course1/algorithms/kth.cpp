#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("kth.in");
ofstream fout("kth.out");
int32_t n,k,A,B,C,i;
int32_t a[30000000]; // *Нужно больше памяти, милорд!*

void findk(int l, int r) {
    int i = l;
    int j = r;
    int32_t x = a[(l+r)/2];

    while (i<=j) {
        while (a[i] < x) {i++;}
        while (a[j] > x) {j--;}
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if(k <= j) {
        findk(l,j);
    } else if(k >= i) {
        findk(i,r);
    } else {
        fout << a[k];
    }
}

int main() {
    fin >> n >> k >> A >> B >> C >> a[0] >> a[1];
    for(i = 2; i < n; i++) {
        a[i] = A*a[i-2] + B*a[i-1] + C;
    }
    k--;
    findk(0,n-1);
    fin.close();
    fout.close();
    return 0;
}
