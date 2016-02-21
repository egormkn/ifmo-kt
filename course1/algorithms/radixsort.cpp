#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;
ifstream fin("radixsort.in");
ofstream fout("radixsort.out");
int n,k,m,i,by;
string a[1000];

bool compare(string j, string k){
    return j[by] < k[by];
}

int main() {
    fin >> n >> m >> k;
    for(i = 0; i < n; i++) {
        fin >> a[i];
    }
    for(i = 1; i <= k; i++) {
        by = m-i;
        stable_sort(&a[0], &a[n], compare);
    }
    for(i = 0; i < n; i++) {
        fout << a[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
