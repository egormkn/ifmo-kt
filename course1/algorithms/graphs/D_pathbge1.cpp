#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

FILE *fin = fopen("pathbge1.in", "r");
FILE *fout = fopen("pathbge1.out", "w");

const int MAXN = 30000 + 1;
int n, m;
vector<int> g[MAXN];
int path[MAXN];

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);
    
    for(int i = 0, v1, v2; i < m; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    
    for(int i = 1; i <= n; i++) {
        path[i] = INT_MAX;
    }
    
    path[1] = 0;
    queue<int> q;
    q.push(1);
    vector<int> d(n);
    
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        
        for(size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            
            if(path[to] > path[v] + 1) {
                q.push(to);
                path[to] = path[v] + 1;
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        fprintf(fout, "%d ", path[i]);
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}
