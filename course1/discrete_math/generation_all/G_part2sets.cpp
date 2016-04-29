#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
FILE *fin = fopen("part2sets.in", "r");
FILE *fout = fopen("part2sets.out", "w");
 
int n, k;
 
void generate(vector<string> sets, int k, int number, int max, int offset){
    if(number == max){
        for(int i = 0; i < k; i++){
            if(sets[i].empty()){
                return;
            }
        }
        for(int i = 0; i < k; i++){
            fprintf(fout, "%s\n", sets[i].c_str());
        }
        fprintf(fout, "\n");
        return;
    }
    for(int i = 0; i < min(number - offset, k); i++){
        string s = sets[i];
        sets[i] += to_string(number) + " ";
        generate(sets, k, number + 1, max, offset + (i + 1 == (number - offset) ? 0 : 1));
        sets[i] = s;
    }
}
 
int main(int argc, char **argv) {
    fscanf(fin, "%d %d", &n, &k);
    vector<string> sets(k);
    generate(sets, k, 1, n + 1, 0);
    fclose(fin);
    fclose(fout);
    return 0;
}
