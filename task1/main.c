#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int n = 0, x1 = 1, y1, x2, y2;
	scanf("%d", &n);
	int **A = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		A[i] = (int*) malloc(n * sizeof(int));
	}
	scanf("%d", &x1);
	while(x1 != 0){
		scanf("%d %d %d", &y1, &x2, &y2);
		char format[4];
		char l = 1;
		int temp = A[x2][y2];
		while(temp != 0){
			temp /= 10;
			l++;
		}
		sprintf(format, "%%%dd", l);
		for (int i = x1-1; i < x2; i++){
			for (int j = y1-1; j < y2; j++){
				printf(format, A[i][j]);
			}
			printf("\n");
		}
		scanf("%d", &x1);
	}
	for (int i = 0; i < n; i++) {
		free(A[i]);
	}
	free(A);
	return 0;
}
