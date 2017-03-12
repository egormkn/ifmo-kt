#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("grassplant.in", "r");
FILE *fout = fopen("grassplant.out", "w");

vector<vector<int>> G;
vector<int> chain_vertex, pos_in_chain, chain_parent, vert_in_chain;

struct chain {
    int size, end;

    chain(int s, int e) : size(s), end(e) {}
};

chain dfs(int v, int parent) {
    int size = 1;
    chain result(0, -1);
    for (int i = 0; i < G[v].size(); i++) {
        int to = G[v][i];
        if(to == parent) continue;
        chain res = dfs(to, v);
        if(res.size > result.size || (res.size == result.size && res.end > result.end)) {
            result = res;
        }
        size += res.size;
    }
    result.size = size;

    if(result.end == -1) {
        result.end = v;
    }
    chain_parent[result.end] = parent;
    G[v].clear();
    G[result.end].push_back(v);
    return result;
}

struct chain_part {
    int chain, low, high;

    chain_part(int c, int l, int h) : chain(c), low(l), high(h) {}
};

vector<chain_part> chain_path(int v1, int v2) {
    vector<pair<int, int>> v1chain, v2chain;

    for (; v1 != -1; v1 = chain_parent[chain_vertex[v1]])
        v1chain.push_back(make_pair(chain_vertex[v1], pos_in_chain[v1]));
    reverse(v1chain.begin(), v1chain.end());

    for (; v2 != -1; v2 = chain_parent[chain_vertex[v2]])
        v2chain.push_back(make_pair(chain_vertex[v2], pos_in_chain[v2]));
    reverse(v2chain.begin(), v2chain.end());

    if(v1chain.size() > v2chain.size()) {
        v2chain.swap(v1chain);
    }

    int i;
    for (i = 0; i < v1chain.size() && v1chain[i] == v2chain[i]; i++);

    vector<chain_part> result;
    if(i == v1chain.size()) {
        result.push_back(chain_part(v1chain.back().first, v1chain.back().second, v1chain.back().second));
    } else if(v1chain[i].first == v2chain[i].first) {
        result.push_back(chain_part(v1chain[i].first, min(v1chain[i].second, v2chain[i].second), max(v1chain[i].second, v2chain[i].second)));
        i++;
    }
    for (int j = i; j < v2chain.size(); j++) {
        result.push_back(chain_part(v2chain[j].first, v2chain[j].second, vert_in_chain[v2chain[j].first]));
    }
    for (int j = i; j < v1chain.size(); j++) {
        result.push_back(chain_part(v1chain[j].first, v1chain[j].second, vert_in_chain[v1chain[j].first]));
    }
    return result;
}

vector<chain_part> remove_empty(const vector<chain_part> &path) {
    vector<chain_part> result;
    for (int i = 0; i < path.size(); i++) {
        if(path[i].low != path[i].high) {
            result.push_back(path[i]);
        }
    }
    return result;
}

int fenwick_sum(int r, vector<int> &T) {
    int result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
        result += T[r];
    return result;
}

void fenwick_add(int i, int delta, vector<int> &A) {
    for (; i < A.size(); i = (i | (i + 1)))
        A[i] += delta;
}

unsigned leading_zeros(int x) {
    unsigned result = 32;
    while (x > 0) {
        x >>= 1;
        result--;
    }
    return result;
}

int main() {
    unsigned n, m;
    fscanf(fin, "%u %u", &n, &m);

    G.resize(n);
    for (int i = 0, v1, v2; i < n - 1; i++) {
        fscanf(fin, "%d %d", &v1, &v2);
        v1--;
        v2--;
        G[v1].push_back(v2);
        G[v2].push_back(v1);
    }

    chain_vertex.resize(n);
    pos_in_chain.resize(n);
    chain_parent.resize(n);
    vert_in_chain.resize(n);

    dfs(0, -1);

    for (int i = 0; i < G.size(); i++) {
        vert_in_chain[i] = G[i].size();
        for (int j = 0; j < G[i].size(); j++) {
            chain_vertex[G[i][j]] = i;
            pos_in_chain[G[i][j]] = j;
        }
    }

    vector<vector<int>> fenwick_tree(n);
    for (int i = 0; i < n; i++) {
        if(vert_in_chain[i] > 0) {
            fenwick_tree[i] = vector<int>((unsigned int) (1 << (32 - leading_zeros(vert_in_chain[i] - 1))), 0);
        }
    }

    char c;
    int u, v;
    for (int i = 0; i < m; i++) {
        fscanf(fin, " %c %d %d", &c, &u, &v);
        u--;
        v--;
        vector<chain_part> path = remove_empty(chain_path(u, v));
        if(c == 'P') {
            for (int i = 0; i < path.size(); i++) {
                int chain = path[i].chain, low = path[i].low, high = path[i].high;
                fenwick_add(low, 1, fenwick_tree[chain]);
                if(high < vert_in_chain[chain]) {
                    fenwick_add(high, -1, fenwick_tree[chain]);
                }
            }
        } else {
            fprintf(fout, "%d\n", fenwick_sum(path[0].low, fenwick_tree[path[0].chain]));
        }
    }
}