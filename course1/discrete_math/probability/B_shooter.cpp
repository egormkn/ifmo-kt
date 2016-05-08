#include <cstdio>
#include <cmath>
 
using namespace std;
 
FILE *fin = fopen("shooter.in", "r");
FILE *fout = fopen("shooter.out", "w");
 
int main(int argc, char **argv) {
    int n, m, k;
    fscanf(fin, "%d %d %d", &n, &m, &k);
    double p, player, all = 0.0;
    for (int i = 1; i <= n; i++){
		fscanf(fin, "%lf", &p);
		p = pow(1.0 - p, m);
		if (i == k) {
			player = p;
		}
		all += p;
	}
    fprintf(fout, "%.14f", player / all);
    fclose(fin);
    fclose(fout);
    return 0;
}
