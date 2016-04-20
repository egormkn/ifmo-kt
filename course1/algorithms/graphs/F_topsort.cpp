#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
FILE *fin = fopen("topsort.in", "r");
FILE *fout = fopen("topsort.out", "w");
 
const int MAXN = 100000 + 1;
int n = 1, m = 0;
vector<int> g[MAXN];
bool used[MAXN];
enum {white, gray, black} color[MAXN];
vector<int> ans;
  
bool dfs (int v) {
    color[v] = gray;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (color[to] == 0) {
            if (dfs(to)){
                return true;
            }
        } else if (color[to] == 1) {
            return true;
        }
    }
    ans.push_back(v);
    color[v] = black;
    return false;
}
 
int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);
    for(int i = 0, v1, v2; i < m; i++){
        fscanf(fin, "%d %d", &v1, &v2);
        g[v1].push_back(v2);
    }
    for (int i = 1; i <= n; i++){
        used[i] = false;
        color[i] = white;
    }
    ans.clear();
    for (int i = 1; i <= n; i++){
        if (!used[i]){
            if(dfs(i)){
                fprintf(fout, "-1\n");
                fclose(fin);
                fclose(fout);
                return 0;
            }
        }
    }
    reverse(ans.begin(), ans.end());
     
    for (unsigned i = 0; i < ans.size(); i++){
        fprintf(fout, "%d ", ans[i]);
    }
 
    fclose(fin);
    fclose(fout);
    return 0;
}
