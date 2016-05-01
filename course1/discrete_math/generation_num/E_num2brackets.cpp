#include <cstdio>
#include <string>
#include <vector>
  
using namespace std;
  
FILE *fin = fopen("num2brackets.in", "r");
FILE *fout = fopen("num2brackets.out", "w");
 
int n;
long long k;
vector<vector<long long>> d;
vector<bool> brackets;
 
void print(const vector<bool>& v){
    for(unsigned i = 0; i < v.size(); i++){
        fprintf(fout, v[i] ? ")" : "(");
    }
    fprintf(fout, "\n");
}
 
void generate() {
    int level = 0;
    k++;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (level < n && d[i][level + 1] >= k) {
            brackets.push_back(false);
            level++;
        } else {
            if (level < n) {
                k -= d[i][level + 1];
            }
            brackets.push_back(true);
            level--;
        }
    }
}
 
int main(int argc, char **argv) {
    fscanf(fin, "%d %I64d", &n, &k);
 
    d.resize(2 * n + 1);
    for (unsigned i = 0; i < d.size(); i++) {
        d[i].resize(n + 1);
    }
    d[0][0] = 1;
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j > 0) {
                d[i + 1][j - 1] = d[i + 1][j - 1] + d[i][j];
            }
            if (j < n) {
                d[i + 1][j + 1] = d[i + 1][j + 1] + d[i][j];
            }
        }
    }
 
    generate();
     
    print(brackets);
    fclose(fin);
    fclose(fout);
    return 0;
}
