#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("grassplant.in", "r");
FILE *fout = fopen("grassplant.out", "w");

vector<vector<int>> G;

/* Node fields. */
vector<int> chain_vertex;  // Vertex chain index
vector<int> pos_in_chain; // Vertex chain position

/* Chain fields. */
vector<int> chain_parent; // Chain parent (-1 if none)
vector<int> vert_in_chain; // Number of vertexes in chain.

struct chain {
    int size, end;
    chain(int s, int e): size(s), end(e) {}
};

/* Before calling G[i] represents the edges of vertex i.  After calling G[i] is
 * a list (from root to child) of vertexes in chain i. */
chain dfs(int v, int parent) {
    int size = 1;
    chain result(0, -1);
    for (int i = 0; i < G[v].size(); i++) {
        int to = G[v][i];
        if(to == parent) continue;
        chain res = dfs(to, v);
        if (res.size > result.size || (res.size == result.size && res.end > result.end)) {
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

/* Returns a list of all the sections of the chains on the path from u to v. */
vector<chain_part> chain_path(int u, int v) {
    vector<pair<int, int>> cu, cv;
    for (; u != -1; u = chain_parent[chain_vertex[u]])
        cu.push_back(make_pair(chain_vertex[u], pos_in_chain[u]));
    for (; v != -1; v = chain_parent[chain_vertex[v]])
        cv.push_back(make_pair(chain_vertex[v], pos_in_chain[v]));
    reverse(cu.begin(), cu.end());
    reverse(cv.begin(), cv.end());
    if(cv.size() < cu.size()) cu.swap(cv);

    int i;
    for (i = 0; i < cu.size() && cu[i] == cv[i]; i++);

    vector<chain_part> ret;
    if(i == cu.size()) {
        ret.push_back(chain_part(cu.back().first, cu.back().second, cu.back().second));
    } else if(cu[i].first == cv[i].first) {
        ret.push_back(chain_part(cu[i].first,
                                min(cu[i].second, cv[i].second),
                                max(cu[i].second, cv[i].second)));
        ++i;
    }
    for (int j = i; j < cu.size(); j++) {
        ret.push_back(chain_part(cu[j].first, cu[j].second, vert_in_chain[cu[j].first]));
    }
    for (int j = i; j < cv.size(); j++) {
        ret.push_back(chain_part(cv[j].first, cv[j].second, vert_in_chain[cv[j].first]));
    }
    return ret;
}

/* Get rid of empty chain parts. */
vector<chain_part> filter(const vector<chain_part> &ch) {
    vector<chain_part> res;
    for (int i = 0; i < ch.size(); i++) {
        if(ch[i].low != ch[i].high) {
            res.push_back(ch[i]);
        }
    }
    return res;
}

vector<vector<int>> fenwick_tree;

void fenwick_add2(vector<int> &A, int x, int v) {
    for (int i = x | A.size(); i < (A.size() << 1); i += i & -i) {
        A[i ^ A.size()] += v;
    }
}

void fenwick_add (vector<int> &A, int i, int delta) {
    for (; i < A.size(); i = (i | (i+1)))
        A[i] += delta;
}

int fenwick_sum2(vector<int> &A, int r) {
    int sum = A[0];
    for (; r > 0; r &= r - 1) {
        sum += A[r];
    }
    return sum;
}

int fenwick_sum(vector<int> &A, int r) {
    int result = 0;
    for (; r >= 0; r = (r & (r+1)) - 1)
        result += A[r];
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

    fenwick_tree.resize(n);
    for (int i = 0; i < n; i++) {
        if(vert_in_chain[i] > 0) {
            fenwick_tree[i] = vector<int>(1 << (32 - __builtin_clz(vert_in_chain[i] - 1)), 0);
        }
    }

    char c;
    int u, v;
    for (int i = 0; i < m; i++) {
        fscanf(fin, " %c %d %d", &c, &u, &v);
        u--;
        v--;
        vector<chain_part> ch = filter(chain_path(u, v));
        if(c == 'P') {
            for (int i = 0; i < ch.size(); i++) {
                fenwick_add(fenwick_tree[ch[i].chain], ch[i].low, 1);
                if(ch[i].high < vert_in_chain[ch[i].chain]) {
                    fenwick_add(fenwick_tree[ch[i].chain], ch[i].high, -1);
                }
            }
        } else {
            // assert(ch.size() == 1 && ch[0].low + 1 == ch[0].high);
            printf("%d\n", fenwick_sum(fenwick_tree[ch[0].chain], ch[0].low));
        }
    }
}