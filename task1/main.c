#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int n = 0, x1 = 1, y1, x2, y2;
	scanf("%d\n", &n);

	int **A = malloc(n*sizeof(int*) + n*n*sizeof(int));
	int * pc = A;
	pc += n*sizeof(int*);
    for (int i=0; i<n; i++){
        A[i] = pc + i*sizeof(n*sizeof(int));
        
	}
	for (int i=0; i<n; i++){
		for (int j = i; j < n; j++){
			A[i][j] = i * j;
			A[j][i] = A[i][j];
		}
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
		
		for (int i = x1; i <= x2; i++){
			for (int j = y1; j <= y2; j++){
				printf(format, A[i][j]);
			}
			printf("\n");
		}
		
		scanf("%d", &x1);
	}
	
	free(A);
	return 0;
}


