#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

FILE *fin = fopen("search4.in", "r");
FILE *fout = fopen("search4.out", "w");

class AhoCorasick {
private:

    class Node {
    public:
        vector<int> children, paths, str_ids;
        char ch;
        int parent, link, min_link, counter;

        Node() : str_ids(), children(26, -1), paths(26, -1), link(-1), min_link(-1), parent(-1), ch(0), counter(0) {}
    };

    vector<Node> nodes;
    unsigned int strings = 0;

public:

    AhoCorasick() {
        nodes.resize(1);
    }

    void put(const string &str) {
        int v = 0;
        for (size_t i = 0; i < str.length(); ++i) {
            char c = str[i] - 'a';
            if(nodes[v].children[c] == -1) {
                size_t u = nodes.size();
                nodes.resize(u + 1);
                nodes[u].parent = v;
                nodes[u].ch = c;
                nodes[v].children[c] = u;
            }
            v = nodes[v].children[c];
        }
        nodes[v].str_ids.push_back(strings++);
    }

    int size() {
        return strings;
    }

    int get_link(int v) {
        if(nodes[v].link == -1) {
            if(v == 0 || nodes[v].parent == 0) {
                nodes[v].link = 0;
            } else {
                nodes[v].link = go(get_link(nodes[v].parent), nodes[v].ch);
            }
        }
        return nodes[v].link;
    }

    int get_min_link(int v) {
        if (nodes[v].min_link == -1) {
            if(v == 0 || nodes[v].parent == 0) {
                nodes[v].min_link = 0;
            } else {
                int s = v;
                while (s != 0) {
                    int u = get_link(s);
                    if (!nodes[u].str_ids.empty()) { // Если терминальная
                        nodes[v].min_link = u;
                        return nodes[v].min_link;
                    }
                    s = u;
                }
                nodes[v].min_link = 0;
            }
        }
        return nodes[v].min_link;
    }

    int go(int v, char c) {
        if(nodes[v].paths[c] == -1) {
            if(nodes[v].children[c] != -1) {
                nodes[v].paths[c] = nodes[v].children[c];
            } else {
                nodes[v].paths[c] = v == 0 ? 0 : go(get_link(v), c);
            }
        }
        return nodes[v].paths[c];
    }

    vector<int> substr_count(const string &str) {
        vector<int> count(strings, 0);
        int node = 0;
        for (char c : str) {
            node = go(node, c - 'a');
            nodes[node].counter++;
        }
        for (int j = 0; j < nodes.size(); ++j) {
            int suff = j;
            while (suff != 0) {
                for (int i : nodes[suff].str_ids) {
                    count[i] += nodes[j].counter;
                }
                suff = get_min_link(suff);
            }
        }

        return count;
    }
};

int main() {
    char buffer[1000000];
    int n = 0;
    fscanf(fin, "%d ", &n);

    AhoCorasick trie;

    for (int i = 0; i < n; ++i) {
        fscanf(fin, "%s ", buffer);
        trie.put(string(buffer));
    }

    fscanf(fin, "%s ", buffer);
    fscanf(fin, "%s ", buffer);
    vector<int> result = trie.substr_count(string(buffer));
    for (int count : result) {
        fprintf(fout, count > 0 ? "YES\n" : "NO\n");
    }

    fclose(fin);
    fclose(fout);
}