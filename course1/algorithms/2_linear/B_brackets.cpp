#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("brackets.in");
ofstream fout("brackets.out");
char stack[10000];
long n = 0;

int main() {
    ios::sync_with_stdio(false);
    char c;

    while(fin >> c) {
        if(n > 0 && (stack[n-1] == '(' && c == ')') || (stack[n-1] == '[' && c == ']') || (stack[n-1] == '{' && c == '}')) {
            n--;
        } else {
            stack[n++] = c;
        }
    }

    fout << ((n == 0) ? "YES" : "NO");

    fin.close();
    fout.close();
    return 0;
}
