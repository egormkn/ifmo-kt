#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

FILE *fin = fopen("trie.in", "r");
FILE *fout = fopen("trie.out", "w");

vector<vector<int>> trie;
string str;

unsigned add_vertex() {
    unsigned size = trie.size();
    trie.resize(size + 1);
    trie[size].assign(26, -1);
    return size;
}

void add(int offset, int node) {
    if (offset == str.size()) {
        return;
    }
    const char c = str[offset] - 'a';
    if (trie[node][c] == -1) {
        int v = add_vertex();
        trie[node][c] = v;
        add(offset + 1, v);
    } else {
        add(offset + 1, trie[node][c]);
    }
}

int main() {
    char buffer[101];
    fscanf(fin, "%100s", buffer);
    str = buffer;

    unsigned root = add_vertex();
    for (int i = 0; i < str.size(); i++) {
        add(i, root);
    }

    fprintf(fout, "%d %d\n", trie.size(), trie.size() - 1);
    for (int i = 0; i < trie.size(); i++) {
        for (int j = 0; j < trie[i].size(); j++) {
            if (trie[i][j] != -1) {
                fprintf(fout, "%d %d %c\n", i + 1, trie[i][j] + 1, j + 'a');
            }
        }
    }

}