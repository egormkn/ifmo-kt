#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("choose2num.in", "r");
FILE *fout = fopen("choose2num.out", "w");

int n, k;
vector<vector<int>> C;
vector<int> choose;

int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &k);
    choose.push_back(0);
    for(int i = 0, t; i < k; i++){
		fscanf(fin, "%d", &t);
		choose.push_back(t);
	}
    
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

    long long answer = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = choose[i - 1] + 1; j < choose[i]; j++) {
            answer += C[n - j][k - i];
        }
    }
    
    fprintf(fout, "%I64d", answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
