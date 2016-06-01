#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

FILE *fin = fopen("z.in", "r");
FILE *fout = fopen("z.out", "w");

int main(int argc, char **argv) {
	char c;
	vector<char> s;
	fscanf(fin, "%c", &c);
    while(isalpha(c) && !feof(fin)) {
		s.push_back(c);
		fscanf(fin, "%c", &c);
	}

	int n = (int) s.size();
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i < n; i++) {
		if(i <= r) {
			z[i] = min(r-i+1, z[i-l]);
		}
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if(i + z[i] - 1 > r) {
			l = i,  r = i + z[i] - 1;
		}
		fprintf(fout, "%d ", z[i]);
	}

	
    fclose(fin);
    fclose(fout);
    return 0;
}
