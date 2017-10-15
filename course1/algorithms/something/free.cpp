#include <stdio.h>
#include <climits>
#include <algorithm> 
#include <stdlib.h>

using namespace std;
FILE *fin = fopen("free.in", "r");
FILE *fout = fopen("free.out", "w");
 
int main(int argc, char **argv) {
    int a, b, c, k;
    fscanf(fin, "%d %d %d %d", &a, &b, &c, &k);

//stars = new int[c + 1][b + 1][a + 1];
//shirt = new int[c + 1][b + 1][a + 1];

    
    fclose(fin);
    fclose(fout);
    return 0;
}
