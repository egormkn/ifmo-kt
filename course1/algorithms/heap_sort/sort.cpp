#include <iostream>
#include <fstream>

using namespace std;

int n,i,cnt=0;
long a[100000];
ifstream fin("sort.in");
ofstream fout("sort.out");

void quicksort(int l, int r) {
    int i = l, j = r;
    long x = a[(l+r)/2];
    while (i<=j) {
        while (a[i] < x) {i++;cnt++;}
        while (a[j] > x) {j--;cnt++;}
        if (i <= j) {swap(a[i++], a[j--]);}
    }
    if (i < r) {quicksort(i,r);}
    if (l < j) {quicksort(l,j);}
}

int main() {
    fin >> n;
    for(i = 0; i < n; i++) {
        fin >> a[i];
    }
    quicksort(0,n-1);
    for(i = 0; i < n; i++){
        fout << a[i] << " ";
    }
    fin.close();
    fout.close();
    return 0;
}
