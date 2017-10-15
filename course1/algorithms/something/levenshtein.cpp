#include <fstream>
#include <string>

using namespace std;
ifstream fin("levenshtein.in"); 
ofstream fout("levenshtein.out"); 

int main(int argc, char **argv) {
	string s1, s2;
	fin >> s1 >> s2;
	int s1len = s1.length(), s2len = s2.length();
	
	short dp[501][501];
    for (int i = 0; i < s1len + 1; i++) {
        for (int j = 0; j < s2len + 1; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j > 0) {
                dp[i][j] = j;
                continue;
            }
            if (i > 0 && j == 0) {
                dp[i][j] = i;
                continue;
            }
            if (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            if (i > 0 && j > 0 && s1[i - 1] != s2[j - 1]) {
                if (dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] <= dp[i - 1][j - 1])
                    dp[i][j] = dp[i][j - 1] + 1;
                if (dp[i - 1][j - 1] <= dp[i - 1][j] && dp[i - 1][j - 1] <= dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i - 1][j] <= dp[i - 1][j - 1] && dp[i - 1][j] <= dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }

	fout << dp[s1len][s2len];
	
	fin.close();
	fout.close();
    return 0;
}
