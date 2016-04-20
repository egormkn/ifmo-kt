#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

FILE *fin = fopen("spantree2.in", "r");
FILE *fout = fopen("spantree2.out", "w");

vector<int> p;

int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    
    if(rand() & 1) {
        swap(a, b);
    }
    
    if(a != b) {
        p[a] = b;
    }
}

int main(int argc, char **argv) {
    int n, m;
    vector<pair<int, pair<int, int>>> g;
    fscanf(fin, "%d %d", &n, &m);
    
    for(int i = 0, b, e, w; i < m; i++) {
        fscanf(fin, "%d %d %d", &b, &e, &w);
        pair<int, int> edge(b, e);
        pair<int, pair<int, int>> record(w, edge);
        g.push_back(record);
    }
    
    int cost = 0;
    vector < pair<int, int> > res;
    sort(g.begin(), g.end());
    p.resize(n + 1);
    
    for(int i = 0; i < n; ++i) {
        p[i] = i;
    }
    
    for(int i = 0; i < m; ++i) {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        
        if(dsu_get(a) != dsu_get(b)) {
            cost += l;
            dsu_unite(a, b);
        }
    }
    
    fprintf(fout, "%d", cost);
    fclose(fin);
    fclose(fout);
    return 0;
}
