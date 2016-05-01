#include <cstdio>
#include <vector>
#include <string>

using namespace std;

FILE *fin = fopen("brackets2num2.in", "r");
FILE *fout = fopen("brackets2num2.out", "w");

int n;
long long answer = 0;
string brackets;
vector<vector<long long>> d;

bool push_opened(char b, string& temp, long long& cur, int& level, int& i){
    if (level < n) {
        cur = d[2 * n - i - 1][level + 1] << ((2 * n - i - level - 2) / 2);
    } else {
        cur = 0;
    }
    if (brackets[i] == b) {
        temp.push_back(b);
        level++;
        return true;
    }
    answer += cur;
    return false;
}

int main(int argc, char **argv) {
    char t[40];
	fscanf(fin, "%s", t);
	brackets = t;
	n = brackets.size() / 2;

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

    string temp;
    int level = 0;
    long long cur = 0;
    for (int i = 0; i < 2 * n; i++) {
        if(push_opened('(', temp, cur, level, i)){
			continue;
		}

        if (temp.size() > 0 && temp.back() == '(' && level - 1 >= 0) {
            cur = d[2 * n - i - 1][level - 1] << ((2 * n - i - level) / 2);
        } else {
            cur = 0;
        }
        if (brackets[i] == ')') {
            temp.pop_back();
            level--;
            continue;
        }
        answer += cur;

        if(push_opened('[', temp, cur, level, i)){
			continue;
		}
        temp.pop_back();
        level--;
    }
    
	fprintf(fout, "%I64d", answer);
    fclose(fin);
	fclose(fout);
	return 0;
}
