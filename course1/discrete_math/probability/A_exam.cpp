#include <cstdio>
 
using namespace std;
 
FILE *fin = fopen("exam.in", "r");
FILE *fout = fopen("exam.out", "w");
 
int main(int argc, char **argv) {
    int k, n;
    fscanf(fin, "%d %d", &k, &n);
    double answer = 0.0;
    for(int i = 0, p, m; i < k; i++){
		fscanf(fin, "%d %d", &p, &m);
		answer += ((double) p / n) * ((double) m / 100);
	}
    fprintf(fout, "%.6f", answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
