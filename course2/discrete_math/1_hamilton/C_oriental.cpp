#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

FILE *fin = stdin;
FILE *fout = stdout;

bool compare(const int &x, const int &y) { // true if x -> y
    fprintf(fout, "1 %d %d\n", x + 1, y + 1);
    fflush(fout);
    char answer[5];
    fscanf(fin, "%s", &answer[0]);
    return answer[0] == 'Y';
}

int main(int argc, char **argv) {
    int n = 0;
    fscanf(fin, "%d", &n);
    deque<int> path(1, 0);
    for (int i = 1; i < n; i++) {
        path.insert(lower_bound(path.begin(), path.end(), i, compare), i);
    }
    fprintf(fout, "0 ");
    for (deque<int>::iterator it = path.begin(); it != path.end(); it++) {
        fprintf(fout, "%d ", *it + 1);
    }
    return 0;
}