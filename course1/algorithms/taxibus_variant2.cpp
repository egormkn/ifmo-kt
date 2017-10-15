#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
struct tree {
    long long res;
    long long index;
};

tree t[400500];
vector <pair<pair<long long, long long>, long long> > mass;
long long n;

const long long inf =  0;

void update(int pos, long long index, long long res) {
    pos += n;
    t[pos].index = index;
    t[pos].res = res;

    //printf("%d ", t[pos]);
    for (pos >>= 1; pos; pos >>= 1) {
        t[pos].res = t[pos * 2].res+ t[pos * 2 + 1].res;
    }
}

long long get(long long  l, long long r) {
    long long ress = 0;

    for (l += n, r += n; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
        if (l & 1) {
            ress = ress+ t[l].res;
        }

        if (!(r & 1)) {
            ress = ress+ t[r].res;
        }
    }

    return ress;
}

int main() {
    //ifstream �in("rmq.in");
    //ofstream �out("rmq.out");
    freopen("taxibus.in", "rt", stdin);
    freopen("taxibus.out", "wt", stdout);
    scanf("%I64d", &n);
    /*pair<pair<long long,long long>,long long> g;
    g.first.first = 0;
    g.first.second = 0;
    g.second = -1;*/
    mass.resize(n+1);
    for (int i = 1; i <= n; i++) {
        //�in >> mass[i];

        update(i, -1,0);
       // printf("%d", t[i + n]);
    };
    // printf("\n");

    for (long long i=1; i<=n; i++) {
        scanf("%I64d%I64d",  &mass[i].first.first, &mass[i].first.second) ;
        mass[i].second=i;

    }

    sort(mass.begin()+1,mass.end());

     for (long long i=1; i<=n; i++) {
        printf("%I64d %I64d ",  mass[i].first.first, mass[i].first.second) ;
    }


    long long sum;
    for (long long i=1; i<=n; i++) {
        update(mass[i].first.second,mass[i].second,1);
        sum+=get(mass[i].first.first, mass[i].first.second);
    }

    printf("%I64d\n", sum);
    for (long long ii=1; ii<=n; ii++) {
            if (t[ii+n].index!=-1)
              printf("%I64d ", t[ii+n].index);

        }
}
