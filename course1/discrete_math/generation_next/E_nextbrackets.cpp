#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = fopen("nextbrackets.in", "r");
FILE *fout = fopen("nextbrackets.out", "w");

void print(const vector<bool>& v){
    for(unsigned i = 0; i < v.size(); i++){
        fprintf(fout, v[i] ? ")" : "(");
	}
	fprintf(fout, "\n");
}

int main(int argc, char **argv) {
	char c, t = ')';
	vector<bool> next;
	bool nonext = true;
	fscanf(fin, "%c", &c);
	while (!feof(fin)){
		if(c == '(' || c == ')'){
		    next.push_back(c == ')');
		    if (c == t && nonext){
			    nonext = false;
		    }
		    t = c;
	    }
		fscanf(fin, "%c", &c);
	}

	if (nonext){
		fprintf(fout, "-\n");
	} else {
        int counter_close = 0;
        int counter_open = 0;
        for (int i = next.size() - 1; i > 0; i--){
            if (!next[i]){
                counter_open++;
                if (counter_close > counter_open){
                    break;
                }
            } else {
                counter_close++;
            }
        }
        // начиная с символа с индексом "length(s) - counter_open - counter_close" удаляем все символы (индексация с 0)
        next.resize(next.size() - counter_open - counter_close);
        if (next.empty()) {
            // return "No Solution"
        } else {
            int j;
            next.push_back(true);
            for (j = 1; j <= counter_open; j++){
                next.push_back(false);
            }
            for (j = 1; j < counter_close; j++){
                next.push_back(true);
            }
        }		
		print(next);
	}
	
    fclose(fin);
	fclose(fout);
	return 0;
}
