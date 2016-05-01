#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("nextchoose.in", "r");
FILE *fout = fopen("nextchoose.out", "w");

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
	int n, k;
	long sum = 0;
	vector<int> next;
	fscanf(fin, "%d %d", &n, &k);
	for(int i = n - k + 1, t; i <= n; i++){
		fscanf(fin, "%d", &t);
		next.push_back(t);
		sum += i - t;
	}
	

	bool nonext = sum == 0;
	

	if (nonext){
		fprintf(fout, "-1\n");
	} else {
        next.push_back(n + 1);


        int i = k - 1;
        while (i >= 0 && next[i + 1] - next[i] < 2){ 
            i--;
		}
        if (i >= 0){
             next[i]++;
             for (int j = i + 1; j < k; j ++){
                 next[j] = next[j - 1] + 1;
			 }
			 next.resize(k);
        } else {
            fprintf(fout, "-1\n");
		}




        
		print(next);
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
