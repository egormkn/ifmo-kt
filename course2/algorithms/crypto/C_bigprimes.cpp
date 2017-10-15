#include <cstdio>
#include <cstdlib>

using namespace std;

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

long long modexp(long long a, long long b, long long c) {
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

bool isPrime(long long n) {
    if (n == 2 || n == 3)
        return true;
    if (n == 0 || n == 1 || n % 2 == 0)
        return false;

    // 2^s * t == n - 1
    long long s = 0, t = n - 1;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }

    for (int i = 0; i < 10; i++) {
        long long a = rand() % (n - 3) + 2;
        long long x = modexp(a, t, n);
        bool next_iteration = (x == 1) || (x == n - 1);
        if (next_iteration) continue;
        for (long long j = 0; j < s; j++) {
            x = modexp(x, 2, n);
            if (x == 1) return false;
            if (x == n - 1) {
                next_iteration = true;
                break;
            }
        }
        if (next_iteration) continue;
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    srand(100500);
    int n;
    long long k;
    for (scanf("%d", &n); n > 0; --n) {
        scanf("%lld", &k);
        printf(isPrime(k) ? "YES\n" : "NO\n");
    }
}