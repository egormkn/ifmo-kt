#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

FILE *fin = fopen("grassplant.in", "r");
FILE *fout = fopen("grassplant.out", "w");

vector<vector<int>> G;

/* Node fields. */
vector<int> vertex_chain;  // Vertex chain index
vector<int> vertex_pos; // Vertex chain position

/* Chain fields. */
vector<int> chain_parent; // Chain parent (-1 if none)
vector<int> vert_in_chain; // Number of vertexes in chain.


pair<int, int> hang(int u, int p) {
    pair<int, int> result = make_pair(0, -1);
    int nodes = 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v == p) continue;
        pair<int, int> res = hang(v, u);
        nodes += res.first;
        result = max(result, res);
    }
    G[u].clear();

    if(result.second == -1) result.second = u;
    G[result.second].push_back(u);
    chain_parent[result.second] = p;

    result.first = nodes;
    return result;
}

/* Represents the nodes in the range [lo, hi) of chain. */
struct ChainPart {
    ChainPart(int chain, int lo, int hi) : chain(chain), lo(lo), hi(hi) {}

    int chain;
    int lo; // lo node on the chain.
    int hi; // hi node on the chain. hi=vert_in_chain[chain] means chain connects to parent
};

/* Returns a list of all the sections of the chains on the path from u to v. */
vector<ChainPart> chain_path(int u, int v) {
    vector<pair<int, int>> cu, cv;
    for (; u != -1; u = chain_parent[vertex_chain[u]])
        cu.push_back(make_pair(vertex_chain[u], vertex_pos[u]));
    for (; v != -1; v = chain_parent[vertex_chain[v]])
        cv.push_back(make_pair(vertex_chain[v], vertex_pos[v]));
    reverse(cu.begin(), cu.end());
    reverse(cv.begin(), cv.end());
    if(cv.size() < cu.size()) cu.swap(cv);

    int i;
    for (i = 0; i < cu.size() && cu[i] == cv[i]; i++);

    vector<ChainPart> ret;
    if(i == cu.size()) {
        ret.push_back(
                ChainPart(cu.back().first, cu.back().second, cu.back().second));
    } else if(cu[i].first == cv[i].first) {
        ret.push_back(ChainPart(cu[i].first,
                                min(cu[i].second, cv[i].second),
                                max(cu[i].second, cv[i].second)));
        ++i;
    }
    for (int j = i; j < cu.size(); j++) {
        ret.push_back(ChainPart(cu[j].first, cu[j].second, vert_in_chain[cu[j].first]));
    }
    for (int j = i; j < cv.size(); j++) {
        ret.push_back(ChainPart(cv[j].first, cv[j].second, vert_in_chain[cv[j].first]));
    }
    return ret;
}

/* Get rid of empty chain parts. */
vector<ChainPart> filter(const vector<ChainPart> &ch) {
    vector<ChainPart> res;
    for (int i = 0; i < ch.size(); i++) {
        if(ch[i].lo != ch[i].hi) {
            res.push_back(ch[i]);
        }
    }
    return res;
}

vector<vector<int>> bit;

void bit_add(vector<int> &A, int x, int v) {
    for (int i = x | A.size(); i < (A.size() << 1); i += i & -i) {
        A[i ^ A.size()] += v;
    }
}

int bit_get(vector<int> &A, int x) {
    int ret = A[0];
    for (int i = x; i; i &= i - 1) ret += A[i];
    return ret;
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

    vertex_chain.resize(n);
    vertex_pos.resize(n);
    chain_parent.resize(n);
    vert_in_chain.resize(n);

    /* Before calling G[i] represents the edges of vertex i.  After calling G[i] is
     * a list (from root to child) of vertexes in chain i. */
    hang(0, -1);
    for (int i = 0; i < G.size(); i++) {
        vert_in_chain[i] = G[i].size();
        for (int j = 0; j < G[i].size(); j++) {
            vertex_chain[G[i][j]] = i;
            vertex_pos[G[i][j]] = j;
        }
    }

    bit.resize(n);
    for (int i = 0; i < n; i++) {
        if(vert_in_chain[i] == 0) continue;
        bit[i] = vector<int>(1 << (32 - __builtin_clz(vert_in_chain[i] - 1)), 0);
    }

    char c;
    int u, v;
    for (int i = 0; i < m; i++) {
        fscanf(fin, " %c %d %d", &c, &u, &v);
        u--;
        v--;
        vector<ChainPart> ch = filter(chain_path(u, v));
        if(c == 'P') {
            for (int i = 0; i < ch.size(); i++) {
                bit_add(bit[ch[i].chain], ch[i].lo, 1);
                if(ch[i].hi < vert_in_chain[ch[i].chain]) {
                    bit_add(bit[ch[i].chain], ch[i].hi, -1);
                }
            }
        } else {
            assert(ch.size() == 1 && ch[0].lo + 1 == ch[0].hi);
            printf("%d\n", bit_get(bit[ch[0].chain], ch[0].lo));
        }
    }
}