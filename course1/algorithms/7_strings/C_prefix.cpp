#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

FILE *fin = fopen("prefix.in", "r");
FILE *fout = fopen("prefix.out", "w");

int main(int argc, char **argv) {
	char c;
	fscanf(fin, "%c", &c);
	vector<char> s(1, c);
	vector<int> prefix(1, 0);
	fprintf(fout, "0 ");
	fscanf(fin, "%c", &c);
    while(isalpha(c) && !feof(fin)) {
		s.push_back(c);
		int i = s.size() - 1;
		int j = prefix[i - 1];
		while(j > 0 && s[i] != s[j]) {
			j = prefix[j - 1];
		}
		if(s[i] == s[j]) {
			j++;
		}
		prefix.push_back(j);
		fprintf(fout, "%d ", j);
		fscanf(fin, "%c", &c);
	}
	
    fclose(fin);
    fclose(fout);
    return 0;
}
