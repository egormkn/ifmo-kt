#include <cstdio>
#include <string>

using namespace std;

FILE *fin = fopen("brackets.in", "r");
FILE *fout = fopen("brackets.out", "w");

void generate(int n, int open, int close, string answer){
   if (open + close == 2 * n){
       fprintf(fout, "%s\n", answer.c_str());
       return;
   }
   if (open < n){
       generate(n, open + 1, close, answer + '(');
   }
   if (open > close){
       generate(n, open, close + 1, answer + ')');
   }
}

int main(int argc, char **argv) {
	int n;
	fscanf(fin, "%d", &n);
	generate(n, 0, 0, "");
    fclose(fin);
	fclose(fout);
	return 0;
}
