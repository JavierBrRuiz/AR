#include <stdio.h>

int main (){
	int n_filas, l, i, j, k;

	printf("Introduzca un numero de filas: ");
	scanf("%d", &n_filas);

	for (i = 1; i <= n_filas; i++){
		for (j = 1; j <= n_filas-i; j++ ){
			
			printf(" ");

		}
		
			
		for (k = i; k >= 1; k--){
			printf("%d", k);
		}
		
		if (i > 1){
			for (l = 2; l <= i; l++){
				printf("%d", l);
			}
		}
		printf("\n");
		
	}

	return 0;
}
