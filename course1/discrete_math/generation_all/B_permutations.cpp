#include <cstdio>
#include <string>

using namespace std;

FILE *fin = fopen("permutations.in", "r");
FILE *fout = fopen("permutations.out", "w");

void swap(int &i, int &j) {
    int s = i;
    i = j;
    j = s;
}

bool generate(int *a, int n){
	for(int i = n - 2; i >= 0; i--){
        if(a[i] < a[i + 1]){
            int min = i + 1;
            for(int j = i + 1; j < n; j++){
                if (a[j] < a[min] && a[j] > a[i]){
                    min = j;
				}
			}
            swap(a[i], a[min]);
            while(i + 1 < n - 1){
                swap(a[i++ + 1], a[n-- - 1]);
	        }
            return true;
		}
	}
    return false; 
}

void print(int *a, int n){
    for(int i = 0; i < n; i++){
		fprintf(fout, "%d ", a[i]);
	}
	fprintf(fout, "\n");
}

int main(int argc, char **argv) {
	int n = 0, a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	fscanf(fin, "%d", &n);
    do {
        print(a, n);
	} while(generate(a, n));
    fclose(fin);
	fclose(fout);
	return 0;
}
