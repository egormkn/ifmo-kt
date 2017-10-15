#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin("palindrome.in"); 
ofstream fout("palindrome.out"); 

int main(int argc, char **argv) {
	string s;
	fin >> s;
	int len = s.length();

    int dp[2001][2001];
    for (int i = 0; i < len + 1; i++) {
        for (int j = 0; j < len + 1; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
                continue;
            }
            if (s[i - 1] == s[len - 1 - (j - 1)]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                continue;
            }
            if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    int i = len;
    int j = len;
    string result;
    while (i > 0 && j > 0) {
        if (s[i - 1] == s[len - 1 - (j - 1)]) {
            result += s[i - 1];
            i--;
            j--;
            continue;
        }
        if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    fout << result.length() << endl << result << endl;
    
	fin.close();
	fout.close();
    return 0;
}
