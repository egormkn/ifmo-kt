#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

FILE *fin = fopen("array2.in", "r");
FILE *fout = fopen("array2.out", "w");

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
        unsigned int n = str.size();
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

int main() {
    char buffer[400000];
    fscanf(fin, "%s", buffer);

    string str(buffer);

    vector<int> suffArray = Suffix::getArray(str);
    for (int i : suffArray) {
        fprintf(fout, "%d ", i + 1);
    }

    fprintf(fout, "\n");

    for (int i : Suffix::getLCPArray(str, suffArray)) {
        fprintf(fout, "%d ", i);
    }

    fclose(fin);
    fclose(fout);
}