#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

FILE *fin = fopen("fire.in", "r");
FILE *fout = fopen("fire.out", "w");

const int MAXN = 20000 + 1;
int n, m;
vector<int> g[MAXN], gr[MAXN];
unordered_set<int> edges[MAXN];
vector<char> used;
vector<int> order, component, answer;
int counter = 0;

void dfs1 (int v) {
    used[v] = true;
    for (size_t i = 0; i < gr[v].size(); ++i){
        if (!used[gr[v][i]]){
            dfs1(gr[v][i]);
        }
    }
    order.push_back(v);
}

void dfs2 (int v) {
    used[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < gr[v].size(); ++i){
        if (!used[gr[v][i]]){
            dfs2 (gr[v][i]);
        }
    }
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);
    answer.assign(n, 0);

    for(int i = 0, v1, v2; i < m; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--; v2--;
        g[v1].push_back(v2);
        gr[v2].push_back(v1);
    }

    used.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!used[i]){
            dfs1(i);
        }
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2(v);
            if(component.size() > 0){
                counter++;
            }
            component.clear();
        }
    }


    fprintf(fout, "%d\n", counter);

    fclose(fin);
    fclose(fout);
}
