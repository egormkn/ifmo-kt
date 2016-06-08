#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("game.in", "r");
FILE *fout = fopen("game.out", "w");

const int MAXN = 100000 + 1;
int n, m, s;
vector<int> g[MAXN];
bool win[MAXN];
bool used[MAXN];

bool dfs_win(int v) {
    used[v] = true;
    win[v] = false;
    for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i){
        if(used[*i] && !win[*i]){
            win[v] = true;
        }
        if(!used[*i] && !dfs_win(*i)){
            win[v] = true;
        }
    }
    return win[v];
}


int main(int argc, char **argv) {
    fscanf(fin, "%d %d %d", &n, &m, &s);
    for(int i = 0, v1, v2; i < m; i++){
        fscanf(fin, "%d %d", &v1, &v2);
        g[v1].push_back(v2);
    }
    for (int i = 1; i <= n; i++){
        win[i] = false;
        used[i] = false;
    }

    fprintf(fout, dfs_win(s) ? "First player wins" : "Second player wins");

    fclose(fin);
    fclose(fout);
    return 0;
}
