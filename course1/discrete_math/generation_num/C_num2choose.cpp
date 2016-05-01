#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("num2choose.in", "r");
FILE *fout = fopen("num2choose.out", "w");

int n, k;
long long m;
vector<vector<int>> C;
vector<int> answer;

void print(const vector<int>& v){
    for(unsigned i = 0; i < v.size(); i++){
        fprintf(fout, "%d ", v[i]);
	}
	fprintf(fout, "\n");
}

void generate() {
    int num = 1;
    while (k > 0) {
        if (m < C[n - 1][k - 1]) {
            answer.push_back(num);
            k -= 1;
        } else {
            m -= C[n - 1][k - 1];
        }
        n--;
        num++;
    }
}

int main(int argc, char **argv) {
    fscanf(fin, "%d %d %I64d", &n, &k, &m);
    
    C.resize(n + 1);
    for(unsigned i = 0; i < C.size(); i++){
		C[i].resize(k + 1);
		C[i][0] = 1;
		if(i > 0){
			for (int j = 1; j <= k; j++) {
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            }
		}
    }
    generate();
    print(answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
