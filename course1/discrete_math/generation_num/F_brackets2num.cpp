#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("brackets2num.in", "r");
FILE *fout = fopen("brackets2num.out", "w");



int main(int argc, char **argv) {
	vector<bool> brackets;
	char c;
	fscanf(fin, "%c", &c);
	while (!feof(fin)){
		if(c == '(' || c == ')'){
		    brackets.push_back(c == ')');
	    }
		fscanf(fin, "%c", &c);
	}
	int n = brackets.size() / 2;

    long long answer = 0;
    vector<vector<long long>> d(2 * n + 1);
    for (unsigned i = 0; i < d.size(); i++) {
		d[i].resize(n + 2);
	}
	d[0][0] = 1;
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j <= n + 1; j++) {
            if (j > 0) {
                d[i + 1][j - 1] = d[i + 1][j - 1] + d[i][j];
            }
            if (j < n) {
                d[i + 1][j + 1] = d[i + 1][j + 1] + d[i][j];
            }
        }
    }

    int level = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (!brackets[i]) {
            level++;
        } else {
            answer += d[2 * n - i - 1][level + 1];
            level--;
        }
    }
    
	fprintf(fout, "%I64d", answer);
    fclose(fin);
	fclose(fout);
	return 0;
}
