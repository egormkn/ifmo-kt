#include <iostream>
#include <fstream>

using namespace std;

//ifstream fin("antiqs.in");
//ofstream fout("antiqs.out");
int n,i;
int a[70000];

int main() {
    cin >> n;
    for (i = 0; i<n; i++){
        a[i] = i+1;
        if (i > 1) swap(a[i], a[i/2]);
    }
    for (i = 0; i<n; i++){
cout << a[i] << " ";
    }
    //fin.close();
    //fout.close();
    return 0;
}
