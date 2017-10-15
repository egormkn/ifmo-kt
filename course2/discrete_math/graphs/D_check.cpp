#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *fin = fopen("check.in", "r");
FILE *fout = fopen("check.out", "w");

struct subset {
    int size, mask;

    subset(int s, int m): size(s), mask(m) {}
};

bool comparator(subset &a, subset &b) {
    return a.size > b.size;
}

// Checks whether all subsets of 'set' exist in 'I'
bool check2(int set, vector<bool> &used, vector<bool> &checked) {
    if (checked[set]) {
        return true;
    }
    bool result = true;
    for (int bit = 1; bit <= set; bit <<= 1) {
        if ((set | bit) == set) {
            if (!used[set ^ bit]) {
                return false;
            } else {
                result = result & check2(set ^ bit, used, checked);
            }
        }
    }
    checked[set] = result;
    return result;
}

bool check3(int s1, int s2, vector<bool> &used) {
    int diff = s1 & ~s2;
    for (int bit = 1; bit <= diff; bit <<= 1) {
        if ((diff | bit) == diff && used[s2 | bit]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    bool axiom1 = false, axiom2 = true, axiom3 = true;
    unsigned n = 0, m = 0;
    fscanf(fin, "%d %d", &n, &m);

    vector<subset> I;
    vector<bool> used((unsigned int) (1 << n), false), checked((unsigned int) (1 << n), false);

    for (int i = 0, size; i < m; i++) {
        fscanf(fin, "%d", &size);
        if (size == 0) {
            axiom1 = true; // Axiom 1
            checked[0] = true;
        }

        int bitmask = 0;
        for (int j = 0, e; j < size; j++) {
            fscanf(fin, "%d", &e);
            bitmask |= 1 << --e;
        }

        I.push_back(subset(size, bitmask));
        used[bitmask] = true;
    }

    sort(I.begin(), I.end(), comparator);

    for (int i = 0; i < I.size(); i++) {
        int set = I[i].mask;
        bool result = check2(set, used, checked);
        axiom2 = axiom2 && result;
    }

    for (int i = 0; i < I.size(); i++) {
        for (int j = i + 1; j < I.size(); j++) {
            if (I[i].size > I[j].size) {
                bool result = check3(I[i].mask, I[j].mask, used);
                axiom3 = axiom3 && result;
            }
        }
    }

    fprintf(fout, axiom1 && axiom2 && axiom3 ? "YES" : "NO");

    fclose(fin);
    fclose(fout);
    return 0;
}