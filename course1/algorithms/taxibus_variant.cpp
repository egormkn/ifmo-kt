#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string>
 
using namespace std;
 
 
//ifstream in("taxibus.in"); //
//ofstream out("taxibus.out"); //
 
 
 
 
long long n, sz, n_old,ans,ki,kj;
double lo, z;
string m;
 
vector <long long> A;
 
vector <pair<pair<long long, long long>, long long>> B;
 
vector <pair<pair<long long, long long>, long long>> Z;
 
pair<pair<long long, long long>, long long> i, j,g;
 
/*void build() {
 
    for (long long i = n; i < n + n_old; i++) {
        B[i] = Z[i - n];
    }
 
    for (long long i = n - 1; i > 0; i--) {
        B[i] = (B[2 * i] + B[2 * i + 1]);//min(B[2 * i], B[2 * i + 1]);
    }
 
}*/
 
long long min1(long long tek, long long l, long long r, long long tl, long long tr) {
    if (tl > tr) {
        return 0;//1000000001;
    }
    if (tl == l && tr == r) {
        return B[tek].first.first;
    }
 
    long long mid = (l + r) / 2;
 
    return (min1(2 * tek, l, mid, tl, min(tr, mid)) + min1(2 * tek + 1, mid + 1, r, max(tl, mid + 1), tr));
 
}
 
void set(long long tek, long long tl, long long tr, pair<pair<long long, long long>, long long> p, long long val) {
    if (tl == tr) {
        B[tek].first.first = val;
        B[tek].second = p.second;
    }
    else {
        long long mid = (tl + tr) / 2;
        if (p.first.second + n - 1 <= mid) {
            set(2 * tek, tl, mid, p, val);
        }
        else {
            set(2 * tek + 1, mid + 1, tr, p, val);
        }
        B[tek].first.first = B[2 * tek].first.first + B[2 * tek + 1].first.first;
    }
 
 
 
}
 
 
 
int main() {
 
    freopen("taxibus.in", "r", stdin);
    freopen("taxibus.out", "w", stdout);
 
    //ios_base::sync_with_stdio(0);
    //in.tie(0);
 
    //in >> n;
    scanf("%lld",&n);
    n = 2 * n;
    n_old = n;
 
    Z.resize((n_old / 2)+1);
 
    for (long long jj = 1; jj <= n_old / 2; jj++) {
        //in >> Z[jj].first.first >> Z[jj].first.second;
        scanf("%lld%lld", &Z[jj].first.first,&Z[jj].first.second);
        Z[jj].second = jj;
    }
 
    sort(Z.begin()+1, Z.end());
 
 
    lo = log10(n) / log10(2);
    n = ceil(lo);
    n = pow(2, n);
 
    g.first.first = 0;
    g.first.second = 0;
    g.second = -1;
 
    B.resize(2 * 131072, g); //1000000001
 
    //build();
 
    for (long long jj = 1; jj <= n_old / 2; jj++) {
        i = Z[jj];
            ans = ans + min1(1, n, 2 * n - 1, i.first.first+n-1, i.first.second+n-1);
            set(1, n, 2 * n - 1, i, 1);
    }
 
    A.resize((n_old/2)+1);
 
    long long pod;
    pod = 1;
    for (long long jj = n; jj <= 2 * n - 1; jj++) {
        if (B[jj].second != -1) {
            A[B[jj].second] = pod;
	pod++;
        }
    }
    printf("%lld \n", ans);
    //out << ans << endl;
    for (long long jj = 1; jj <= n_old/2; jj++) {
        //out << A[jj] << " ";
        printf("%lld ", A[jj]);
    }
 
    //out.close();
    //in.close();
}
