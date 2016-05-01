#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("num2brackets2.in", "r");
FILE *fout = fopen("num2brackets2.out", "w");

int n;
long long k;
string brackets;
vector<vector<long long>> d;

bool push_opened(char b, string& temp, long long& cur, int& level, int& i){
    if (level < n) {
        cur = d[i][level + 1] << ((i - level - 1) / 2);
    } else {
        cur = 0;
    }

    if (cur >= k) {
        brackets.push_back(b);
        temp.push_back(b);
        level++;
        return true;
    }
    k -= cur;
    return false;
}

void generate() {
    string temp;
    int level = 0;
    long long cur;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if(push_opened('(', temp, cur, level, i)){
			continue;
		}
        if (temp.size() > 0 && temp.back() == '(' && level > 0){
            cur = d[i][level - 1] << ((i - level + 1) / 2);
        } else {
            cur = 0;
		}
        if (cur >= k) {
            brackets.push_back(')');
            temp.pop_back();
            level--;
            continue;
        }
        k -= cur;
        if(push_opened('[', temp, cur, level, i)){
			continue;
		}
        brackets.push_back(']');
        temp.pop_back();
        level--;
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

    k++;
    generate();
    
    fprintf(fout, "%s\n", brackets.c_str());
    fclose(fin);
    fclose(fout);
    return 0;
}
