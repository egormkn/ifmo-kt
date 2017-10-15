#define FILENAME lis
#include <stdio.h>
#include <math.h>

using namespace std;
FILE *fin = fopen("lis.in", "r");
FILE *fout = fopen("lis.out", "w");

int main(int argc, char **argv) {
	int n, X[5000];
	fscanf(fin, "%d", &n);
	for (int i = 0; i < n; i++){
		fscanf(fin, "%d", &X[i]);
	}
	
	
	
	
	
	
	int P[5000], M[5001];
	int L = 0;
	for (int i = 0; i < n; i++) {
		// Binary search for the largest positive j ≤ L
		// such that X[M[j]] < X[i]
		int lo = 1;
		int hi = L;
		while (lo <= hi) {
			int mid = ceil((lo + hi) / 2);
			if (X[M[mid]] < X[i]) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		// After searching, lo is 1 greater than the
		// length of the longest prefix of X[i]
		int newL = lo;

		// The predecessor of X[i] is the last index of 
		// the subsequence of length newL-1
		P[i] = M[newL-1];
		M[newL] = i;

		if (newL > L) {
			// If we found a subsequence longer than any we've
			// found yet, update L
			L = newL;
		}
	}
	// Reconstruct the longest increasing subsequence
	int S[5000], k = M[L];
	for (int i = L-1; i >= 0; i--){
		S[i] = X[k];
		k = P[k];
	}
	
	fprintf(fout, "%d\n", L);
	for (int i = 0; i < L; i++){
		fprintf(fout, "%d ", S[i]);
	}
	
	
	
	
	
	fclose(fin);
	fclose(fout);
	return 0;
}

