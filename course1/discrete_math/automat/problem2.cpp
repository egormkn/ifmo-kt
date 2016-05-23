#include <cstdio>
#include <vector>
#include <unordered_set>
 
using namespace std;
 
FILE *fin = fopen("problem2.in", "r");
FILE *fout = fopen("problem2.out", "w");

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

    vector<bool> terminal(n, false);
    for(int i = 0, t; i < k; i++) {
		fscanf(fin, "%d", &t);
		terminal[--t] = true;
	}
    
	vector<vector<vector<int>>> transitions(n);
	for(int i = 0; i < n; i++) {
		transitions[i].resize('z' - 'a' + 1);
	}

	for(int i = 0, a, b; i < m; i++) {
		fscanf(fin, "%d %d %c", &a, &b, &c);
        transitions[--a][c - 'a'].push_back(--b);
	}
    
    unordered_set<int> states;
    states.emplace(0);
    
	for(unsigned i = 0; i < s.size(); i++) {
		unordered_set<int> temp;
		for(auto it = states.begin(); it != states.end(); it++) {
			for(unsigned j = 0; j < transitions[*it][s[i] - 'a'].size(); j++) {
				temp.emplace(transitions[*it][s[i] - 'a'][j]);
			}
		}
		states = temp;
	}

    bool accepts = false;
    for(auto it = states.begin(); it != states.end(); it++) {
		if(terminal[*it]) {
			accepts = true;
			break;
		}
	}
	
    fprintf(fout, accepts ? "Accepts" : "Rejects");
    fclose(fin);
    fclose(fout);
    return 0;
}
