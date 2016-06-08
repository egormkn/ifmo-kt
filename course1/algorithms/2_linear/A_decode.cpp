#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("decode.in");
ofstream fout("decode.out");
char stack[200000];
long n = 0;

int main() {
    ios::sync_with_stdio(false);
    char c;

    while(fin >> c) {
        if(n > 0 && stack[n-1] == c) {
            n--;
        } else {
            stack[n++] = c;
        }
    }

    for(int i = 0; i < n; i++) {
        fout << stack[i];
    }

    fin.close();
    fout.close();
    return 0;
}
