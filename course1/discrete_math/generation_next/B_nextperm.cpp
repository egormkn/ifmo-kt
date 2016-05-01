#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("nextperm.in", "r");
FILE *fout = fopen("nextperm.out", "w");

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
	int n, t, min, max;
	vector<int> prev, next;
	bool noprev = true, nonext = true;
	fscanf(fin, "%d", &n);
	for(int i = 0; i < n; i++){
		fscanf(fin, "%d", &t);
		prev.push_back(t);
		next.push_back(t);
		if (i > 0 && t < prev[i - 1] && noprev){
			noprev = false;
		} else if (i > 0 && t > prev[i - 1] && nonext){
			nonext = false;
		}
	}

	if (noprev){
		for(int i = 0; i < n; i++){
		    fprintf(fout, "0 ");
		}
		fprintf(fout, "\n");
	} else {
        for(int i = next.size() - 2; i >= 0; i--){
            if (prev[i] > prev[i + 1]){
                max = i + 1;
                for(int j = i + 1; j < n; j++){
                    if (prev[j] > prev[max] && prev[j] < prev[i]){
                        max = j;
                    }
                }
                swap(prev[i], prev[max]);
                while(i + 1 < n - 1){
                    swap(prev[i++ + 1], prev[n-- - 1]);
                }
                break;
            }
        }
		print(prev);
	}

	if (nonext){
		for(int i = 0; i < n; i++){
		    fprintf(fout, "0 ");
		}
		fprintf(fout, "\n");
	} else {
        for(int i = next.size() - 2; i >= 0; i--){
            if (next[i] < next[i + 1]){
                min = i + 1;
                for(int j = i + 1; j < n; j++){
                    if (next[j] < next[min] && next[j] > next[i]){
                        min = j;
                    }
                }
                swap(next[i], next[min]);
                while(i + 1 < n - 1){
                    swap(next[i++ + 1], next[n-- - 1]);
                }
                break;
            }
        }
		print(next);
	}
	
    fclose(fin);
	fclose(fout);
	return 0;
}
