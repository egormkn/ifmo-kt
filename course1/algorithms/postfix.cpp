#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("postfix.in");
ofstream fout("postfix.out");
int stack[100];
long n = 0;

int main() {
    ios::sync_with_stdio(false);
    char c;

    while(fin >> c) {
        if(c == ' ') {
            continue;
        }

        if(c < '0' || c > '9') {
            switch(c) {
            case '+':
                stack[n-2] = stack[n-2] + stack[n-1];
                n--;
                break;

            case '-':
                stack[n-2] = stack[n-2] - stack[n-1];
                n--;
                break;

            case '*':
                stack[n-2] = stack[n-2] * stack[n-1];
                n--;
                break;

            case '/':
                stack[n-2] = stack[n-2] / stack[n-1];
                n--;
                break;
            }
        } else {
            stack[n++] = c - '0';
        }
    }

    fout << stack[0];

    fin.close();
    fout.close();
    return 0;
}
