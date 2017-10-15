#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }
    return x1;
}


int main(int argc, char **argv) {
    int a, b, n, m;
    scanf("%d %d %d %d", &a, &b, &n, &m);
    // x ≡ a (mod n)
    // x ≡ b (mod m)
    // k1 * n + k2 * m = 1
    // x*a + y*b = 1
    // x = a^-1 mod b
    printf("%d\n", (a * m * modInverse(m, n) + b * n * modInverse(n, m)) % (n * m));
}