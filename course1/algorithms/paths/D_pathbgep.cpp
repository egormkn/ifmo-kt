#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <climits>

using namespace std;

FILE *fin = fopen("pathbgep.in", "r");
FILE *fout = fopen("pathbgep.out", "w");

int n, m;
vector<vector<pair<int, long long>>> M;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &m);
    M.resize(n);
    
    long long t;
    for(int i = 0, a, b; i < m; i++) {
        fscanf(fin, "%d %d %I64d", &a, &b, &t);
        M[--a].push_back(make_pair(--b, t));
        M[b].push_back(make_pair(a, t));
    }

    vector<long long> d(n, LLONG_MAX / 2);
    d[0] = 0;
    
    set<pair<long long, int>> q;

	for (int i = 0; i < n; i++) {
		q.insert(make_pair(d[i], i));
	}

	while (!q.empty()) {
		pair<long long, int> cur = *q.begin();
		q.erase(q.begin());
		
		for (int i = 0; i < (int)M[cur.second].size(); ++i) {
			if (d[M[cur.second][i].first] > cur.first + M[cur.second][i].second) {
				q.erase(make_pair(d[M[cur.second][i].first], M[cur.second][i].first));
				d[M[cur.second][i].first] = cur.first + M[cur.second][i].second;
				q.insert(make_pair(d[M[cur.second][i].first], M[cur.second][i].first));
			}
		}
	}

	
  
    for(int i = 0; i < n; i++) {
        fprintf(fout, "%I64d ", d[i] == LLONG_MAX / 2 ? -1 : d[i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
