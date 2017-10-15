#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    vector<unsigned> factors(1000001, 1);
    for (unsigned i = 2; i * i < factors.size(); ++i) {
        for (unsigned j = 2 * i; j < factors.size(); j += i) {
            if (factors[j] == 1) {
                factors[j] = i;
            }
        }
    }

    unsigned n, k;
    scanf("%u", &n);
    for (unsigned i = 0; i < n; ++i) {
        scanf("%u", &k);
        while (factors[k] != 1) {
            printf("%u ", factors[k]);
            k /= factors[k];
        };
        if (k != 1) {
            printf("%u ", k);
        }
        printf("\n");
    }
}