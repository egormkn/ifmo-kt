#include <cstdio>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("problem1.in", "r");
FILE *fout = fopen("problem1.out", "w");

int main(int argc, char **argv) {
    vector<char> s;
    char c;
    fscanf(fin, "%c", &c);
    while(c != '\r' && c != '\n') {
		s.push_back(c);
        fscanf(fin, "%c", &c);
    }

	int n, m, k;
    fscanf(fin, "%d %d %d", &n, &m, &k);

    vector<bool> terminal(n + 1, false);
    for(int i = 0, t; i < k; i++) {
		fscanf(fin, "%d", &t);
		terminal[--t] = true;
	}

	vector<vector<int>> transitions(n);
	for(int i = 0; i < n; i++) {
		transitions[i].assign('z' - 'a' + 1, n);
	}
	for(int i = 0, a, b; i < m; i++) {
		fscanf(fin, "%d %d %c", &a, &b, &c);
        transitions[--a][c - 'a'] = --b;
	}
	
    int state = 0;
	for(unsigned i = 0; i < s.size(); i++) {
		state = transitions[state][s[i] - 'a'];
		if(state == n) {
			terminal[state] = false;
			break;
		}
	}
	
    fprintf(fout, terminal[state] ? "Accepts" : "Rejects");
    fclose(fin);
    fclose(fout);
    return 0;
}
