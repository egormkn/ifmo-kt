#include <iostream>

using namespace std;

int a[11] = {1, 2, 2, 3, 4, 7, 8, 9, 9, 10, 10};
int b[11] = {1, 3, 3, 4, 5, 6, 7, 9, 9, 11, 12};

int main() {
    int j = 0, i = 0;
    bool found = false;
    while(!found && j < 10 && i < 10) {
        if(a[i] <= b[j]) {
            if(a[i] = b[j]) {
                found = true;
                cout << a[i] << endl;
            }

        } else if (b[j] > a[i]) {
            j++;
        }
        i++;
    }
    return 0;
}

int test() {}

