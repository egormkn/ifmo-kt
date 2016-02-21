#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin;
ofstream fout;
string cmd;
long val,key,to;
int n,ad;
long a[100000];
long *p[100000];
bool pushed = false;

void quicksort(int l, int r) {
    int i = l;
    int j = r;
    long x = a[(l+r)/2];
    while (i<=j) {
        while (a[i] > x) {
            i++;
        }
        while (a[j] < x) {
            j--;
        }
        if (i <= j) {
            swap(a[i], a[j]);
            swap(p[i], p[j]);
            i++;
            j--;
        }
    }
    if (i < r) {
        quicksort(i,r);
    }
    if (l < j) {
        quicksort(l, j);
    }
}

int main() {
    fin.open("priorityqueue.in");
    fout.open("priorityqueue.out");
    n = 0;
    ad = 0;

    while(fin >> cmd) {
        if (cmd == "push") {
            fin >> val;
            a[n] = val;
            p[ad] = &a[n];
            n++;
            ad++;
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
                fout<<"*"<< endl;
            }

        } else if (cmd == "decrease-key") {
            fin >> key >> to;
            *p[key-1] = to;
            quicksort(0, n-1);
        }
    }


    return 0;
}
