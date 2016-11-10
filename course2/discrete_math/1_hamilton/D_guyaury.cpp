#include <cstdio>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

FILE *fin = fopen("guyaury.in", "r");
FILE *fout = fopen("guyaury.out", "w");

enum color {
    BLACK, GREY, WHITE
};

int DFS(int v, vector<vector<int>> &G, vector<int> &color, list<int> &cycle) {
    color[v] = GREY;
    for (int i = 0; i < G[v].size(); i++) {
        int to = G[v][i];
        if(color[to] == GREY) {
            cycle.push_front(v);
            return to;
        } else if (color[to] == WHITE) {
            int cycleEnd = DFS(to, G, color, cycle);
            if(cycleEnd > -1){
                if(cycle.front() != cycleEnd) {
                    cycle.push_front(v);
                }
                return cycleEnd;
            }
        }
    }
    color[v] = BLACK;
    return -1;
}

// Finds any cycle in a graph in O(E)
list<int> findCycle(vector<vector<int>> &G) {
    vector<int> color(G.size(), WHITE);
    list<int> cycle;
    DFS(0, G, color, cycle);
    return cycle;
}

int main(int argc, char **argv) {
    unsigned n = 0;
    fscanf(fin, "%u", &n);

    vector<vector<int>> G(n);
    vector<vector<bool>> M(n, vector<bool>(n, false));

    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            fscanf(fin, "%c", &c);
            if(c == '1') {
                G[i].push_back(j);
                M[i][j] = true;
            } else {
                G[j].push_back(i);
                M[j][i] = true;
            }
        }
        fscanf(fin, " ");
    }

    // Find any cycle in G
    list<int> path = findCycle(G);
    vector<bool> inPath(n, false);
    for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
        inPath[*it] = true;
    }

    // Construct a Hamiltonian path by Rédei theorem (1934)
    for (int v0 = 0; v0 < n; v0++) {
        if (inPath[v0]) {
            continue;
        }
        list<int>::iterator it = path.begin();
        for (; it != path.end() &&  M[*it][v0]; it++);
        path.insert(it, v0);
    }

    // Here we have a full Hamiltonian path in a strongly-connected tournament
    // We need to convert it to cycle using algorithm described by Yannis Manoussakis

    // Find maximum k so there is an edge path[k] -> path[0]
    int k = path.size() - 1;
    for (list<int>::reverse_iterator rit = path.rbegin(); !M[*rit][path.front()] && rit != path.rend(); rit++) {
        k--;
    }

    // If k: (2 <= k <= n-1) does not exist, then path[0] has indegree 0
    // So there is no Hamiltonian cycle
    if (k < 2) {
        printf("Not a Hamiltonian: indegree of path[0] = 0");
        return 0;
    }

    // If k == n-1, then our hamiltonian path is a cycle
    if (k != n - 1) {
        // C = path[0],path[1],...path[j] - cycle
        // P = path[j+1]...path[n-1]
        list<int>::iterator cycleEnd = path.begin();
        for(int i = 0; i <= k; i++) {
            cycleEnd++; // *cycleEnd == path[j+1]
        }
        list<int> C(path.begin(), cycleEnd);
        list<int> P(cycleEnd, path.end());

        while (P.size() > 0) {
            list<int>::iterator fromP, toC;
            for (fromP = P.begin(); fromP != P.end(); fromP++) {
                for (toC = C.begin(); toC != C.end(); toC++) {
                    if (M[*fromP][*toC]) {
                        break; // fromP dominates toC
                    }
                }

                if (toC != C.end()) {
                    break;
                }
            }

            if (fromP == P.end() || toC == C.end()) {
                printf("Not a Hamiltonian: there is no vertex in P dominating vertex in C");
                return 0;
            }

            fromP++;
            while (P.begin() != fromP) {
                C.insert(toC, P.front());
                P.pop_front();
            }

            while (C.begin() != toC) {
                C.push_back(C.front());
                C.pop_front();
            }
        }

        path = C;
    }

    for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
        fprintf(fout, "%d ", *it + 1);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}