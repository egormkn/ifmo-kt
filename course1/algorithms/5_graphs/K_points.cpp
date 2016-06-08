#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("points.in", "r");
FILE *fout = fopen("points.out", "w");

const int MAXN = 20000 + 1;
int n, m;
vector<int> g[MAXN];
vector<int> answer;
bool used[MAXN], used_as_cp[MAXN];
int timer, tin[MAXN], fup[MAXN];

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p){
            continue;
        }
        if (used[to]){
            fup[v] = min (fup[v], tin[to]);
        } else {
            dfs(to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1 && !used_as_cp[v]){
                used_as_cp[v] = true;
                answer.push_back(v + 1);
            }
            ++children;
        }
    }
    if (p == -1 && children > 1 && !used_as_cp[v]){
        used_as_cp[v] = true;
        answer.push_back(v + 1);
    }
}


int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);

    for(int i = 0, v1, v2; i < m; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--; v2--;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    timer = 0;
    for (int i = 0; i < n; ++i){
        used[i] = false;
        used_as_cp[i] = false;
    }
    dfs(0);


    sort(answer.begin(), answer.end());

    fprintf(fout, "%d\n", answer.size());
    for(size_t i = 0; i < answer.size(); i++) {
        fprintf(fout, "%d ", answer[i]);
    }

    fclose(fin);
    fclose(fout);
}
