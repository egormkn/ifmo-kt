#include <cstdio>
#include <vector>
#include <cctype>

using namespace std;

FILE *fin = fopen("nextpartition.in", "r");
FILE *fout = fopen("nextpartition.out", "w");

void print(const vector<int>& v){
    for(unsigned i = 0; i < v.size(); i++){
        if(i == 0){
			fprintf(fout, "%d", v[i]);
		} else {
			fprintf(fout, "+%d", v[i]);
		}
	}
	fprintf(fout, "\n");
}

void swap(int &i, int &j) {
    int s = i;
    i = j;
    j = s;
}

int main(int argc, char **argv) {
	int n = 0, t = 0;
	char c;
	fscanf(fin, "%c", &c);
	while(c != '='){
        n = n * 10 + (c - '0');
        fscanf(fin, "%c", &c);
	}
	vector<int> next;
    fscanf(fin, "%c", &c);
    while(!feof(fin)){
        if(c == '+'){
            next.push_back(t);
            t = 0;
		} else if(isdigit(c)) {
			t = t * 10 + (c - '0');
		}
		fscanf(fin, "%c", &c);
	}
	if(feof(fin)){
		next.push_back(t);
        t = 0;
    }
    
    int l = next.size();
    if(l == 1){
        fprintf(fout, "No solution\n");
	} else {
        next[l - 1]--;
        next[l - 2]++;
        if (next[l - 2] > next[l - 1]){
            next[l - 2] += next[l - 1];
            next.pop_back();
        } else {
            while (next[next.size() - 2] * 2 <= next[next.size() - 1]){
                next.push_back(next[next.size() - 1] - next[next.size() - 2]);
                next[next.size() - 2] = next[next.size() - 3];
			}
        }
        fprintf(fout, "%d=", n);
        print(next);
    }
	
    fclose(fin);
	fclose(fout);
	return 0;
}
