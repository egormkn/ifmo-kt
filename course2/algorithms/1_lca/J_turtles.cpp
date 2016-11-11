#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

FILE *fin = fopen("turtles.in", "r");
FILE *fout = fopen("turtles.out", "w");

enum dir {LEFT, RIGHT, UP, DOWN, NONE};
vector<unsigned long> tin, tout, height;
vector<vector<unsigned long>> up;
vector<vector<unsigned long>> cost;
vector<vector<pair<dir, dir>>> direct;
vector<pair<unsigned long, unsigned long>> vertex;
vector<vector<unsigned long>> M;
unsigned long timer = 0, l = 1;

dir opposite(dir d) {
    switch (d) {
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        default:
            return NONE;
    }
}

void dfs(unsigned long v, unsigned long p, dir d, unsigned long h) {
    tin[v] = ++timer;
    height[v] = h;
    up[v][0] = p;
    cost[v][0] = 0;
    direct[v][0] = make_pair(opposite(d), opposite(d));

    for (unsigned long i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
        direct[v][i] = make_pair(direct[v][i-1].first, direct[up[v][i-1]][i-1].second);
        if (i != 1) {
            cost[v][i] = cost[v][i - 1] + cost[up[v][i - 1]][i - 1] + (direct[v][i-1].second != direct[up[v][i - 1]][i-1].first ? 1 : 0);
        } else {
            cost[v][1] = (vertex[v].first != vertex[up[v][1]].first && vertex[v].second != vertex[up[v][1]].second) ? 1 : 0;
        }
    }
    /*for (unsigned long i = 0; i <= l; ++i) {
        printf("\n\nVertex: %lu\n", v);
        printf("Cost of jump 2^%lu: %lu\n", i, cost[v][i]);
    }*/
    if (vertex[v].first > 0 && d != DOWN) {
        unsigned long to = M[vertex[v].first-1][vertex[v].second];
        if (to != p && to != ULONG_MAX) dfs(to, v, UP, h + 1);
    }
    if (vertex[v].first < M.size() - 1 && d != UP) {
        unsigned long to = M[vertex[v].first+1][vertex[v].second];
        if (to != p && to != ULONG_MAX) dfs(to, v, DOWN, h + 1);
    }
    if (vertex[v].second > 0 && d != RIGHT) {
        unsigned long to = M[vertex[v].first][vertex[v].second-1];
        if (to != p && to != ULONG_MAX) dfs(to, v, LEFT, h + 1);
    }
    if (vertex[v].second < M[0].size() - 1 && d != LEFT) {
        unsigned long to = M[vertex[v].first][vertex[v].second+1];
        if (to != p && to != ULONG_MAX) dfs(to, v, RIGHT, h + 1);
    }
    tout[v] = ++timer;
}

bool upper (unsigned long a, unsigned long b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

unsigned long costcount(unsigned long bottom, unsigned long top, dir &end) {
    unsigned long delta = height[bottom] - height[top];
    //printf("Delta: %lu\n", delta);
    unsigned long current = bottom;
    unsigned long costval = 0;
    end = NONE;
    for (unsigned long i = 0; delta > 0; i++) {
        if (delta % 2 == 1) {
            //printf("Jump for 2^%lu\n", i);
            costval = costval + cost[current][i];

            //printf("Cost: %lu\n", cost[current][i]);
            if (end != NONE && end != direct[current][i].first) {
                costval++;
                //printf("+1\n");
            }
            end = direct[current][i].second;
            current = up[current][i];
            //printf("Current: %lu\n", current);
        }
        delta = delta >> 1;
    }
    return costval;
}

unsigned long minlca(unsigned long a, unsigned long b) {
    if (a == b) {
        return 0;
    }
    dir endA, endB; // direction of jump end from A/B
    if (upper(a, b)) {
        return costcount(b, a, endB); // up from b to a
    }
    if (upper(b, a)) {
        return costcount(a, b, endA); // up from a to b
    }
    unsigned long ta = a;
    for (unsigned long i = l; i >= 0; --i) {
        if(!upper(up[a][i], b)) {
            a = up[a][i];
        }
        if (i == 0) {break;}
    }
    unsigned long res = costcount(ta, up[a][0], endA) + costcount(b, up[a][0], endB);
    return res + (endA == opposite(endB) ? 0 : 1); // or 1
}

int main(int argc, char **argv) {
    unsigned long h = 0, w = 0, n = 0, m = 0;
    fscanf(fin, "%lu %lu", &h, &w);
    M.assign(h, vector<unsigned long>(w, ULONG_MAX));

    char c;
    for (unsigned long i = 0; i < h; i++) {
        for (unsigned long j = 0; j < w; j++) {
            do {
                fscanf(fin, "%c", &c);
            } while (c != '#' && c != '.');
            if (c == '#') {
                M[i][j] = n++;
                vertex.push_back(make_pair(i, j));
            }
        }
        fscanf(fin, " ");
    }

    while ((1<<l) <= n) {
        ++l;
    }
    tin.resize(n);
    tout.resize(n);
    height.resize(n);
    up.assign(n, vector<unsigned long>(l+1));
    cost.assign(n, vector<unsigned long>(l+1));
    direct.assign(n, vector<pair<dir, dir>>(l+1));

    dfs(0, 0, DOWN, 0);

    fscanf(fin, "%lu", &m);
    for (int i = 0; i < m; i++) {
        unsigned long r1, c1, r2, c2, res, first, second;
        fscanf(fin, "%lu %lu %lu %lu", &r1, &c1, &r2, &c2);
        r1--; r2--; c1--; c2--;
        first = M[r1][c1];
        second = M[r2][c2];
        res = minlca(first, second);
        fprintf(fout, "%ld\n", res);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

