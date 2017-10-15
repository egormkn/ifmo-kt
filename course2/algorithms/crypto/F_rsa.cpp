#include <cstdio>
#include <cmath>
#include <cassert>

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

long long mult(long long a, long long b, long long c) {
    long long res = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            b--;
            res = (res + a) % c;

        }
        a = (a + a) % c;
        b /= 2;

    }
    return res;

}

long long modpower(long long a, long long b, long long c) {
    long long ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            b--;
            ans = mult(ans, a, c);
        }
        b /= 2;
        a = mult(a, a, c);
    }
    return ans;
}

int main(int argc, char **argv) {
    unsigned n, e, c, p, q;
    unsigned long phi;
    scanf("%u %u %u", &n, &e, &c);
    if (n % 2 == 0) {
        phi = n / 2 - 1;
    } else {
        p = (unsigned) floor(sqrt(n));
        for (unsigned i = 3; i <= p; i += 2) {
            if (n % i == 0) {
                p = i;
                break;
            }
        }
        q = n / p;
        phi = (p - 1) * (q - 1);
    }

    int d = modInverse(e, (int) phi);
    printf("%d\n", (int) modpower(c, d, n));
}