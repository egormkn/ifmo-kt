#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

FILE *fin = fopen("fullham.in", "r");
FILE *fout = fopen("fullham.out", "w");

int main(int argc, char **argv) {
    int n = 0;
    fscanf(fin, "%d", &n);
    vector<vector<bool>> G(n, vector<bool>(n, false));

    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            fscanf(fin, "%c", &c);
            G[i][j] = G[j][i] = c == '1';
        }
        fscanf(fin, " ");
    }

    deque<int> queue;
    for (int i = 0; i < n; i++) {
        queue.push_back(i);
    }

    for (int k = 0; k < n * (n - 1); k++) {
        if(!G[queue[0]][queue[1]]) {
            int i = 2;
            for(; !G[queue[0]][queue[i]] || !G[queue[1]][queue[i + 1]]; i++);
            reverse(queue.begin() + 1, queue.begin() + i + 1);
        }
        queue.push_back(queue.front());
        queue.pop_front();
    }

    for (int i = 0; i < queue.size(); i++) {
        fprintf(fout, "%d ", queue[i] + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}