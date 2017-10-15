#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

FILE *fin = fopen("count.in", "r");
FILE *fout = fopen("count.out", "w");

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

        for (int i = 0; i < n; i++) {
            suffixes[i].index = i;
            suffixes[i].rank[0] = str[i] - 'a';
            suffixes[i].rank[1] = ((i + 1) < n) ? (str[i + 1] - 'a') : -1;
        }

        sort(suffixes.begin(), suffixes.end(), Suffix::comparator);

        vector<int> ind(n);
        for (int k = 4; k < n << 1; k <<= 1) {
            int rank = 0;
            int prev_rank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            ind[suffixes[0].index] = 0;

            for (int i = 1; i < n; i++) {
                if(suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                } else {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
                ind[suffixes[i].index] = i;
            }

            for (int i = 0; i < n; i++) {
                int nextindex = suffixes[i].index + k / 2;
                suffixes[i].rank[1] = (nextindex < n) ?
                                      suffixes[ind[nextindex]].rank[0] : -1;
            }

            sort(suffixes.begin(), suffixes.end(), Suffix::comparator);
        }

        vector<int> suffixArr(n);
        for (int i = 0; i < n; i++) {
            suffixArr[i] = suffixes[i].index;
        }
        return suffixArr;
    }

    static vector<int> getLCPArray(const string &str, const vector<int> &sa) {
        unsigned n = str.size(), k = 0;
        vector<int> lcp(n - 1, 0), rank(n, 0);

        for (int i = 0; i < n; ++i) {
            rank[sa[i]] = i;
        }

        for (int i = 0; i < n; i++, k ? k-- : 0) {
            if(rank[i] == n - 1) {
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
        int start, end, parent, height;
        bool leaf;
        vector<int> children;

        Node() : children(26, -1), start(0), end(0), parent(0), height(0), leaf(false) {}

        int size() {
            return end - start;
        }

        void print() {
            printf("Node <parent: %d, start: %d, end: %d, height: %d>\n", parent, start, end, height);
        }
    };

    SuffixTree(const string &str,
               const vector<int> &suffixArray,
               const vector<int> &lcpArray) {
        tree.resize(2);

        tree[0].children[str[suffixArray[0]] - 'a'] = 1;

        tree[1].start = suffixArray[0];
        tree[1].end = str.size();
        tree[1].parent = 0;
        tree[1].height = tree[1].size();
        tree[1].leaf = true;

        for (int i = 0; i < lcpArray.size(); i++) {
            int lcp = lcpArray[i];
            int start_ch = suffixArray[i + 1] + lcp;

            int last = tree.size() - 1;
            int up = tree[last].height - lcp;


            if (up > 0) {
                int new_node = make_node(str, last, up);
                int leaf = tree.size();
                tree.resize((unsigned) (leaf + 1));
                tree[leaf].start = start_ch;
                tree[leaf].leaf = true;
                tree[leaf].end = str.size();
                tree[leaf].parent = new_node;
                tree[leaf].height = tree[new_node].height + tree[leaf].size();
                tree[new_node].children[str[start_ch] - 'a'] = leaf;
            } else {
                tree[tree[last].parent].children[str[tree[last].start] - 'a'] = -1;
                tree[last].start = start_ch - tree[last].size();
                tree[last].leaf = true;
                tree[last].end = str.size();
                tree[last].height = tree[tree[last].parent].height + tree[last].size();
                tree[tree[last].parent].children[str[tree[last].start] - 'a'] = last;
            }
        }
    }

    int make_node(const string &str, int current, int up) {
        if(up == 0) {
            return current;
        }
        if(tree[current].size() > up) {
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
            return middle;
        }
        int parent = tree[current].parent;
        return make_node(str, parent, up - (tree[current].height - tree[parent].height));
    }

    void print() {
        fprintf(fout, "%d %d\n", tree.size(), tree.size() - 1);
        for (int i = 1; i < tree.size(); i++) {
            fprintf(fout, "%d %d %d %d\n", tree[i].parent + 1, i + 1, tree[i].start + 1, tree[i].end);
        }
    }

    long long countSubstrings(int node) {
        long long size = tree[node].size();
        for (int next : tree[node].children) {
            if (next != -1) {
                size += countSubstrings(next);
            }
        }
        return size;
    }

private:
    vector<Node> tree;

};

int main() {
    char buffer[400001];
    fscanf(fin, "%s", buffer);

    string str(buffer);

    vector<int> suffArray = Suffix::getArray(str);
    vector<int> lcpArray = Suffix::getLCPArray(str, suffArray);

    SuffixTree tree(str, suffArray, lcpArray);

    fprintf(fout, "%lld\n", tree.countSubstrings(0));

    fclose(fin);
    fclose(fout);
}
