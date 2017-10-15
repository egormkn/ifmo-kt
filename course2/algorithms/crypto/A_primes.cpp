#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    vector<bool> prime(1000001, true);
    for (unsigned i = 2; i * i < prime.size(); ++i) {
        if (prime[i]) {
            for (unsigned j = 2*i; j < prime.size(); j += i) {
                prime[j] = false;
            }
        }
    }

    unsigned n, k;
    scanf("%u", &n);
    for (unsigned i = 0; i < n; ++i) {
        scanf("%u", &k);
        printf(prime[k] ? "YES\n" : "NO\n");
    }
}