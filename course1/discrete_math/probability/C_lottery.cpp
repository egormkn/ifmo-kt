#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("lottery.in", "r");
FILE *fout = fopen("lottery.out", "w");
 
int main(int argc, char **argv) {
    int n, m;
    fscanf(fin, "%d %d", &n, &m);

    int prev_a, prev_b;
    fscanf(fin, "%d %d", &prev_a, &prev_b);
    
    double result = n, win = 1.0 / prev_a;
    for (int i = 1, a, b; i < m; i++){
		fscanf(fin, "%d %d", &a, &b);
        result -= win * (a - 1) / a * prev_b;
		win *= 1.0 / a;
		prev_b = b;
	}
	result -= win * prev_b;

    fprintf(fout, "%.15f", result);
    fclose(fin);
    fclose(fout);
    return 0;
}
