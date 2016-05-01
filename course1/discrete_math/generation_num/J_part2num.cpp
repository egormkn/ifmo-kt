#include <cstdio>
#include <vector>
#include <cctype>

using namespace std;

FILE *fin = fopen("part2num.in", "r");
FILE *fout = fopen("part2num.out", "w");

int main(int argc, char **argv) {
	int n = 0, t = 0;
	char c;
	vector<int> part;
    fscanf(fin, "%c", &c);
    while(!feof(fin)){
        if(c == '+'){
            part.push_back(t);
            n += t;
            t = 0;
		} else if(isdigit(c)) {
			t = t * 10 + (c - '0');
		}
		fscanf(fin, "%c", &c);
	}
	if(feof(fin)){
		part.push_back(t);
		n += t;
    }
    int k = part.size();
    vector<vector<int>> m(n + 1);
    for (unsigned i = 0; i < m.size(); i++) {
		m[i].resize(n + 1);
	}
    m[1][1] = 1;
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (i == j) {
                m[i][j] = 1;
            } else {
                for (int k = i; k < j + 1; k++) {
                    m[i][j] += m[k][j - i];
                }
			}
        }
    }
    long long number = 0;
    int l = 1, r = n, i = 0;
    while(true){
        while (l != part[i]) {
            number += m[l][r];
            l++;
        }
        if (i == k - 1) {
			break;
		}
		r -= l;
        i++;
    }

    fprintf(fout, "%I64d", number);
	
    fclose(fin);
	fclose(fout);
	return 0;
}
