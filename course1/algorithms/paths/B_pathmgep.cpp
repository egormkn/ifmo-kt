#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

FILE *fin = fopen("pathmgep.in", "r");
FILE *fout = fopen("pathmgep.out", "w");

int n, s, f;
vector<vector<long long>> M;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d %d", &n, &s, &f);
    s--;
    f--;
    M.resize(n);
    long long t;
    for(int i = 0; i < n; i++) {
        M[i].resize(n);
        for(int j = 0; j < n; j++) {
            fscanf(fin, "%I64d", &t);
            M[i][j] = t;
        }
    }
    

    vector<long long> d(n, LLONG_MAX);
    vector<bool> used(n, false);

    d[s] = 0;
    
    for(int i = 0; i < n; i++) {
        int v = -1;
        for(int j = 0; j < n; j++) {
            if(!used[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        if (d[v] == LLONG_MAX) {
            break;
        }
        used[v] = true;
        for(int j = 0; j < n; j++) {    // произведём релаксацию по всем рёбрам, исходящим из v
            if (M[v][j] != -1 && d[v] + M[v][j] < d[j]){
                d[j] = d[v] + M[v][j];
            }
        }
    }

    fprintf(fout, "%I64d", d[f] == LLONG_MAX ? -1 : d[f]);
    fclose(fin);
    fclose(fout);
    return 0;
}
