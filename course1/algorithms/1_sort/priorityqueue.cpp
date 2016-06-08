#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin("priorityqueue.in");
ofstream fout("priorityqueue.out");
string cmd;
long val, to, op = 0;
int n, ad;
long a[100000];
long b[100000];
long *p[100000];
bool pushed = true;

void quicksort(int l, int r) {
    int i = l, j = r;
    long x = a[(l+r)/2];
    while (i<=j) {
        while (a[i] > x) {i++;}
        while (a[j] < x) {j--;}
        if (i <= j) {
            swap(a[i], a[j]);
            swap(b[i], b[j]);
            p[b[i]] = &a[i];
            p[b[j]] = &a[j];
            i++;
            j--;
        }
    }
    if (i < r) {quicksort(i,r);}
    if (l < j) {quicksort(l,j);}
}

int main() {
    ios::sync_with_stdio(false);
    n = 0;
    ad = 0;

    while(fin >> cmd) {
        op++;
        if (cmd == "push") {
            fin >> val;
            a[n] = val;
            b[n] = op-1;
            p[op-1] = &a[n];
            n++;
            if(!pushed) {
                quicksort(0, n-1);
                pushed = true;
            }
        } else if(cmd == "extract-min") {
            if(pushed) {
                quicksort(0, n-1);
                pushed = false;
            }
            if(n>0) {
                fout << a[n-1] << endl;
                n--;
            } else {
                fout << "*" << endl;
            }
        } else if (cmd == "decrease-key") {
            fin >> val >> to;
            *p[val-1] = to;
            quicksort(0, n-1);
        }
    }
    return 0;
}
