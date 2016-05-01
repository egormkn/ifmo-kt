#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("nextmultiperm.in", "r");
FILE *fout = fopen("nextmultiperm.out", "w");

void print(const vector<int>& v){
    for(unsigned i = 0; i < v.size(); i++){
        fprintf(fout, "%d ", v[i]);
	}
	fprintf(fout, "\n");
}

void swap(int &i, int &j) {
    int s = i;
    i = j;
    j = s;
}

int main(int argc, char **argv) {
	int n;
	fscanf(fin, "%d", &n);
	vector<int> next;

    for(int i = 0, t; i < n; i++){
        fscanf(fin, "%d", &t);
		next.push_back(t);
	}

    int i = n - 2;
    while (i >= 0 && next[i] >= next[i + 1]){
        i--;
    }
    if (i >= 0){ 
        int j = i + 1;
        while (j < n - 1 && next[j + 1] > next[i]) {
            j++;
		}
        swap(next[i], next[j]);
        while(i + 1 < n - 1){
            swap(next[i++ + 1], next[n-- - 1]);
        }
        
		print(next);
    } else {
      for(int i = 0; i < n; i++){
		    fprintf(fout, "0 ");
		}
		fprintf(fout, "\n");
	}
	
    fclose(fin);
	fclose(fout);
	return 0;
}
