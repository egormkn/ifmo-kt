#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *fin = fopen("bridges.in", "r");
FILE *fout = fopen("bridges.out", "w");

const int MAXN = 20000 + 1;
int n, m;
vector<pair<int, int>> g[MAXN];
vector<int> answer;
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i].first;
        int num = g[v][i].second;
        if (to == p) {
            continue;
        }
        if (used[to]){
            fup[v] = min(fup[v], tin[to]);
        } else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > tin[v]){
                answer.push_back(num);
            }
        }
    }
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);

    for(int i = 0, v1, v2; i < m; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--; v2--;
        g[v1].push_back(make_pair(v2, i + 1));
        g[v2].push_back(make_pair(v1, i + 1));
    }

    timer = 0;
    for (int i = 0; i < n; ++i){
        used[i] = false;
    }
    for (int i = 0; i < n; ++i){
        if (!used[i]){
            dfs(i);
        }
    }

    sort(answer.begin(), answer.end());

    fprintf(fout, "%d\n", answer.size());
    for(size_t i = 0; i < answer.size(); i++) {
        fprintf(fout, "%d\n", answer[i]);
    }

    fclose(fin);
    fclose(fout);
}
