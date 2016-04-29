#include <cstdio>
#include <string>

using namespace std;

FILE *fin = fopen("vectors.in", "r");
FILE *fout = fopen("vectors.out", "w");

int fib(int n){
  int a = 0, b = 1, c;
  for (int i = 1; i < n; i++){
     c = a + b;
     a = b;
     b = c;
  }
  return b;
}

void gen(string s, unsigned n){
    if(s.size() == n){
		fprintf(fout, "%s\n", s.c_str());
    	return;
	}
	gen(s + '0', n);
	if(s.empty() || s.back() == '0'){
		gen(s + '1', n);
	}
}

int main(int argc, char **argv) {
	unsigned n;
	fscanf(fin, "%d", &n);
	fprintf(fout, "%d\n", fib(n + 2));
    gen("", n);
    fclose(fin);
	fclose(fout);
	return 0;
}