#include <cstdio>
#include <string>

using namespace std;

FILE *fin = fopen("subsets.in", "r");
FILE *fout = fopen("subsets.out", "w");

void generate(int b, int min, string answer){
	if (min == 0 || min > b) {
		fprintf(fout, "%s\n", answer.c_str());
		return;
	}
		
	generate(b, 0, answer);
	for (int i = min; i <= b; i++) {
		generate(b, i + 1, answer + to_string(i) + " ");
	}
}

int main(int argc, char **argv) {
	int n;
	fscanf(fin, "%d", &n);
	generate(n, 1, "");
    fclose(fin);
	fclose(fout);
	return 0;
}
