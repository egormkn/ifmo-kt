#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

FILE *fin = fopen("refrain.in", "r");
FILE *fout = fopen("refrain.out", "w");

class Suffix {
private:
    int index;
    int rank[2];

    static int comparator(const Suffix &a, const Suffix &b) {
        return (a.rank[0] == b.rank[0])
               ? (a.rank[1] < b.rank[1] ? 1 : 0)
               : (a.rank[0] < b.rank[0] ? 1 : 0);
    }

public:

    static vector<int> getArray(const string &str) {
        unsigned n = str.size();
        vector<Suffix> suffixes(n);

        for (unsigned i = 0; i < n; i++) {
            suffixes[i].index = i;
            suffixes[i].rank[0] = str[i] - 'a';
            suffixes[i].rank[1] = ((i + 1) < n) ? (str[i + 1] - 'a') : -1;
        }

        sort(suffixes.begin(), suffixes.end(), Suffix::comparator);

        vector<int> ind(n);
        for (unsigned k = 4; k < n << 1; k <<= 1) {
            int rank = 0;
            int prev_rank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            ind[suffixes[0].index] = 0;

            for (unsigned i = 1; i < n; i++) {
                if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                } else {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
                ind[suffixes[i].index] = i;
            }

            for (unsigned i = 0; i < n; i++) {
                unsigned nextindex = suffixes[i].index + k / 2;
                suffixes[i].rank[1] = (nextindex < n) ?
                                      suffixes[ind[nextindex]].rank[0] : -1;
            }

            sort(suffixes.begin(), suffixes.end(), Suffix::comparator);
        }

        vector<int> suffixArr(n);
        for (unsigned i = 0; i < n; i++) {
            suffixArr[i] = suffixes[i].index;
        }
        return suffixArr;
    }

    static vector<int> getLCPArray(const string &str, const vector<int> &sa) {
        unsigned n = str.size(), k = 0;
        vector<int> lcp(n - 1, 0), rank(n, 0);

        for (unsigned i = 0; i < n; ++i) {
            rank[sa[i]] = i;
        }

        for (unsigned i = 0; i < n; i++, k ? k-- : 0) {
            if (rank[i] == (int) n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && str[i + k] == str[j + k]) k++;
            lcp[rank[i]] = k;
        }
        return lcp;
    }
};

class SuffixTree {
public:
    struct Node {
        int start, end, parent, height, leaves;
        bool leaf;
        vector<int> children;

        Node() : start(0), end(0), parent(0), height(0), leaves(0), leaf(false), children(26, -1) {}

        int size() {
            return end - start;
        }

        void print() {
            printf("Node <parent: %d, start: %d, end: %d, height: %d, leaf: %d>\n", parent, start, end, height, leaf);
        }
    };

    SuffixTree(const string &str,
               const vector<int> &suffixArray,
               const vector<int> &lcpArray) {
        s = string(str.begin(), str.end());
        tree.resize(2);

        tree[0].children[str[suffixArray[0]] - 'a'] = 1;

        tree[1].start = suffixArray[0];
        tree[1].end = str.size();
        tree[1].parent = 0;
        tree[1].height = tree[1].size();
        tree[1].leaves = 1;
        tree[1].leaf = true;

        // Занесли в дерево лексикографически первый суффикс

        for (unsigned i = 0; i < lcpArray.size(); i++) {
            int lcp = lcpArray[i];
            int start_ch = suffixArray[i + 1] + lcp;

            int last = tree.size() - 1;
            int up = tree[last].height - lcp;

            // Поднимаемся выше
            int new_node = this->make_node(str, last, up);
            int leaf = tree.size();
            tree.resize((unsigned) (leaf + 1));
            tree[leaf].start = start_ch;
            tree[leaf].leaf = true;
            tree[leaf].end = str.size();
            tree[leaf].parent = new_node;
            tree[leaf].height = tree[new_node].height + tree[leaf].size();
            tree[new_node].children[str[start_ch] - 'a'] = leaf;
            tree[leaf].leaves = 1;
            tree[leaf].leaf = true;
        }

        for (int ch : tree[0].children) {
            if (ch != -1) {
                tree[0].leaves += tree[ch].leaves;
            }
        }
    }

    int make_node(const string &str, int current, int up) {
        while (up != 0 && tree[current].size() <= up) {
            int parent = tree[current].parent;
            up = up - (tree[current].height - tree[parent].height);
            for (int ch : tree[current].children) {
                if (ch != -1) {
                    tree[current].leaves += tree[ch].leaves;
                }
            }
            current = parent;
        }
        if (up == 0) {
            return current;
        } else if (tree[current].size() > up) {
            int parent = tree[current].parent;
            int child = current;
            int middle = tree.size();
            tree.resize((unsigned) (middle + 1));

            tree[child].parent = middle;
            tree[middle].parent = parent;

            tree[middle].start = tree[child].start;
            tree[middle].end = tree[child].end - up;

            tree[child].start = tree[middle].end;

            tree[middle].height = tree[parent].height + tree[middle].size();
            tree[child].height = tree[middle].height + tree[child].size();
            tree[middle].leaf = false;

            tree[parent].children[str[tree[middle].start] - 'a'] = middle;

            tree[middle].children[str[tree[child].start] - 'a'] = child;
            for (int ch : tree[child].children) {
                if (ch != -1) {
                    tree[child].leaves += tree[ch].leaves;
                }
            }
            tree[child].leaf = true;
            return middle;
        }
        return 0;
    }

    void calcRefrain() {
        int node = 0; long long refn = 0;
        for (unsigned n = 0; n < tree.size(); ++n) {
            if (tree[n].leaves == 1) {
                tree[n].height--;
                tree[n].end--;
            }

            if ((long long) tree[n].leaves * tree[n].height > refn ||
                ((long long) tree[n].leaves * tree[n].height == refn && tree[n].height < tree[node].height)) {
                refn = (long long) tree[n].leaves * tree[n].height;
                node = n;
            }
        }
        vector<int> answer;
        while (node != 0) {
            for (int i = tree[node].end - 1; i >= tree[node].start; --i) {
                answer.push_back((int) s[i]);
            }
            node = tree[node].parent;
        }
        std::reverse(answer.begin(), answer.end());
        fprintf(fout, "%lld\n%d\n", refn, answer.size());
        for (int a : answer) {
            fprintf(fout, "%d ", a - 'a' + 1);
        }
        fprintf(fout, "\n");
    }

    void print() {
        for (int i = 0; i < tree.size(); i++) {
            fprintf(fout, "%d: ", i);
            for (int c : tree[i].children) {
                if (c != -1) fprintf(fout, "%d ", c);
            }
            fprintf(fout, "\n");
        }
    }

private:
    vector<Node> tree;
    string s;
};

int main() {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);

    vector<char> buffer;
    for (int i = 0, d; i < n; i++) {
        fscanf(fin, "%d", &d);
        buffer.push_back((char) ('a' + d - 1));
    }
    buffer.push_back('z');
    string str(buffer.begin(), buffer.end());

    vector<int> suffArray = Suffix::getArray(str);
    vector<int> lcpArray = Suffix::getLCPArray(str, suffArray);

    SuffixTree tree(str, suffArray, lcpArray);

    tree.calcRefrain();

    fclose(fin);
    fclose(fout);
}