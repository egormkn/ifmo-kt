#include <cstdio>
#include <cctype>

using namespace std;

FILE *fin = fopen("hash.in", "r");
FILE *fout = fopen("hash.out", "w");

int main(int argc, char **argv) {
	int t, r;
	char c;
	long long answer = 0;
    fscanf(fin, "%d %d\n", &t, &r);
	fscanf(fin, "%c", &c);
    while(!feof(fin) && isalpha(c)) {
		answer = (answer * t + c) % r;
		fprintf(fout, "%I64d\n", answer);
		fscanf(fin, "%c", &c);
	}
    fclose(fin);
    fclose(fout);
    return 0;
}
