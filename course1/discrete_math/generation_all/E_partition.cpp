#include <cstdio>
#include <string>

using namespace std;

FILE *fin = fopen("partition.in", "r");
FILE *fout = fopen("partition.out", "w");

void generate(int rest, int min, string answer){
    if (rest == 0){
        fprintf(fout, "%s\n", answer.c_str());
        return;
    }

    for (int i = min; i <= rest; i++) {
        if (rest - i > i) {
			generate(rest - i, i, answer + to_string(i) + "+");
		} else if (rest - i == i) {
			fprintf(fout, "%s\n", (answer + to_string(i) + "+" + to_string(i)).c_str());
		} else if (rest == i) {
			generate(rest - i, i, answer + to_string(i));
		}
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
