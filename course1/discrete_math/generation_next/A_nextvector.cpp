#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("nextvector.in", "r");
FILE *fout = fopen("nextvector.out", "w");

void print(const vector<bool>& v){
    for(unsigned i = 0; i < v.size(); i++){
        fprintf(fout, v[i] ? "1" : "0");
	}
	fprintf(fout, "\n");
}

int main(int argc, char **argv) {
	char c;
	vector<bool> prev, next;
	bool noprev = true, nonext = true;
	fscanf(fin, "%c", &c);
	while (!feof(fin)){
		if(c == '0' || c == '1'){
		    prev.push_back(c == '1');
		    next.push_back(c == '1');
		    if (c == '1' && noprev){
			    noprev = false;
		    } else if (c == '0' && nonext){
			    nonext = false;
		    }
	    }
		fscanf(fin, "%c", &c);
	}

	if (noprev){
		fprintf(fout, "-\n");
	} else {
        for(int i = prev.size() - 1; i >= 0; i--){
			prev[i] = !prev[i];
			if(!prev[i]){
				break;
			}
		}
		print(prev);
	}

	if (nonext){
		fprintf(fout, "-\n");
	} else {
		for(int i = next.size() - 1; i >= 0; i--){
			next[i] = !next[i];
			if(next[i]){
				break;
			}
		}
		print(next);
	}
	
    fclose(fin);
	fclose(fout);
	return 0;
}
