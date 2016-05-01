#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("num2part.in", "r");
FILE *fout = fopen("num2part.out", "w");

int n;
long long r;
vector<int> part;
vector<vector<int>> m;

void print(const vector<int>& v){
	fprintf(fout, "%d", v[0]);
    for(unsigned i = 1; i < v.size(); i++){
		fprintf(fout, "+%d", v[i]);
	}
	fprintf(fout, "\n");
}

void generate(int l, int rest) {
    if (l == rest) {
        part.push_back(l);
        return;
    }
    if (r <= m[l][rest]) {
        part.push_back(l);
        generate(l, rest - l);
    } else {
        r -= m[l][rest];
        generate(l + 1, rest);
    }
}


int main(int argc, char **argv) {
    fscanf(fin, "%d %I64d", &n, &r);
    r++;
    m.resize(n + 1);
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

    generate(1, n);
    
    print(part);
    fclose(fin);
    fclose(fout);
    return 0;
}
