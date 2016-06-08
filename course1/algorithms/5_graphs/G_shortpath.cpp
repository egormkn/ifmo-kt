#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

FILE *fin = fopen("shortpath.in", "r");
FILE *fout = fopen("shortpath.out", "w");

struct path {
    int v;
    int len;
};

const int MAXN = 100000 + 1;
int n, m, s, t;
vector<path> g[MAXN];
bool used[MAXN];
enum {white, gray, black} color[MAXN];
vector<int> ans;
int w[MAXN];

bool dfs (int v) {
    color[v] = gray;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); i++) {
        int to = g[v][i].v;
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
    fscanf(fin, "%d %d %d %d", &n, &m, &s, &t);
    for(int i = 0, v1, v2, w; i < m; i++){
        fscanf(fin, "%d %d %d", &v1, &v2, &w);
        path p;
        p.v = v2;
        p.len = w;
        g[v1].push_back(p);
    }

    for (int i = 1; i <= n; i++){
        used[i] = false;
        color[i] = white;
        w[i] = INT_MAX;
    }

            w[s] = 0;
    ans.clear();
    for (int i = 1; i <= n; i++){
        if (!used[i]){
            if(dfs(i)){
                fprintf(fout, "Unreachable\n");
                fclose(fin);
                fclose(fout);
                return 0;
            }
        }
    }
    reverse(ans.begin(), ans.end());

    bool startfound = false;
    for (unsigned i = 0; i < ans.size(); i++){
        if((!startfound && ans[i] != s) || w[ans[i]] == INT_MAX){
            continue;
        } else if(!startfound && ans[i] == s){
            startfound = true;
        }






 for (unsigned j = 0; j < g[ans[i]].size(); j++){
     int v = g[ans[i]][j].v;
     int len = g[ans[i]][j].len;
     w[v] = min(w[v], w[ans[i]] + len);
}





        if(ans[i] == t){
            fprintf(fout, "%d", w[t]);
            fclose(fin);
            fclose(fout);
            return 0;
        }
    }

    fprintf(fout, "Unreachable\n");
    fclose(fin);
    fclose(fout);
    return 0;
}
