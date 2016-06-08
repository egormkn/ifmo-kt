#include <iostream>
#include <fstream>

using namespace std;

int n;
long a[100000];
bool isheap = true;
ifstream fin("isheap.in");
ofstream fout("isheap.out");

int main() {
    fin >> n >> a[0];
    for(int i = 1; i < n; i++) {
        fin >> a[i];
        if (a[(i-1)/2] > a[i]) {
            isheap = false;
            break;
        }
    }
    fout << (isheap ? "YES" : "NO");
    fin.close();
    fout.close();
    return 0;
}
