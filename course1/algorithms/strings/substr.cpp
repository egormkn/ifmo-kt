#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;

FILE *fin = fopen("substr.in", "r");
FILE *fout = fopen("substr.out", "w");

int main(int argc, char **argv) {
	int t, r, m;
	char c;
	vector<int> prefix(1, 0), power(1, 1); 
    fscanf(fin, "%d %d\n", &t, &r);
	fscanf(fin, "%c", &c);
    while(isalpha(c)) {
		power.push_back(((long long)power.back() * t) % r);
		prefix.push_back(((long long)prefix.back() * t + c) % r);
		fscanf(fin, "%c", &c);
	}
	fscanf(fin, "%d", &m);

	for(int i = 0, a, b; i < m; i++) {
		fscanf(fin, "%d %d", &a, &b);
		a++; b++;
		long long res = prefix[b] - ((long long)prefix[a - 1] * power[b - a + 1]) % r;
		while(res < 0) {
			res += r;
		}
		fprintf(fout, "%I64d\n", res);
	}
	
    fclose(fin);
    fclose(fout);
    return 0;
}
