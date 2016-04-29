#include <cstdio>

using namespace std;

FILE *fin = fopen("choose.in", "r");
FILE *fout = fopen("choose.out", "w");

bool generate(int *a, int n, int k){
    a[k] = n + 1;
    int i = k - 1;
    while ((i >= 0) && (a[i + 1] - a[i]) < 2){
        i--;
    }
    if (i >= 0){
        a[i]++;
        for (int j = i + 1; j < k; j++){
            a[j] = a[j - 1] + 1;
		}
        return true;
    } else {
        return false;
	}
}

void print(int *a, int n){
    for(int i = 0; i < n; i++){
		fprintf(fout, "%d ", a[i]);
	}
	fprintf(fout, "\n");
}

int main(int argc, char **argv) {
	int n, k, a[17];
	fscanf(fin, "%d %d", &n, &k);
	for (int i = 0; i < k; i++){
		a[i] = i + 1;
	}
    do {
        print(a, k);
	} while(generate(a, n, k));
	
    fclose(fin);
	fclose(fout);
	return 0;
}
