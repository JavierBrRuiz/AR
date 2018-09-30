#include <stdio.h>
#include <stdlib.h>

struct lista_dinamica {
    int valor;
    struct lista_dinamica *siguiente;
};
void imprimir_valores(int array[],int cont); 
void insercion_men_may(int array[], int inicio, int fin);
void insercion_may_men(int array[], int inicio, int fin);
void burbuja_may_men(int array[], int inicio, int fin);
void burbuja_men_may(int array[], int inicio, int fin);
void seleccion_may_men(int array[], int inicio, int fin);
void seleccion_men_may(int array[], int inicio, int fin);
int menor(int array[], int inicio, int fin);
void seleccion_may_men(int array[], int inicio, int fin);
int mayor(int array[], int inicio, int fin);
void anadir_elemento(int elemento, struct lista_dinamica *primero, struct lista_dinamica *ultimo);
void rellenar_valores(int array[], struct lista_dinamica *primero); 



typedef struct lista_dinamica lista_dinamica;

int main(){
    struct lista_dinamica *primero, *ultimo;
    int algoritmo, valor_elemento, cont = 0;
    int *valores; 
    int metodo;
    
    do{
        printf("¿Que elemento desea anadir? Pulse -999 para dejar de introducir elementos: ");
        scanf("%d", &valor_elemento);
        anadir_elemento(valor_elemento, primero, ultimo);
        cont++; 
    }while(valor_elemento != -999);
    
    valores = (int *) malloc(cont * sizeof(int));
    if (valores == NULL){
        printf("Error using malloc.");
    }
    rellenar_valores(valores, primero);
    /*    
    printf("-----ALGORITMOS DE ORDENACION-----\n");
    printf("INSERCION -> Pulse 1\n"); 
    printf("SELECCION -> Pulse 2\n"); 
    printf("BURBUJA -> Pulse 3\n");

   // scanf("%d", &algoritmo);
    
    printf("¿Como quiere ordenar, ascendente-1 o desdendente-2?: ");
    scanf("%d", &metodo);
    algoritmo = 3;
    switch (algoritmo){
        case 1: (metodo == 1) ? insercion_men_may(valores, 0,cont) : insercion_may_men(valores, 0, cont); break;

        case 2: (metodo == 1) ? seleccion_men_may(valores, 0, cont) : seleccion_may_men(valores, 0, cont); break;
        
        case 3: (metodo == 1) ? burbuja_men_may(valores, 0,cont) : burbuja_may_men(valores, 0, cont); break;
    }
*/     
    imprimir_valores(valores, cont); 
    
    //free(valores);

    return 0;
}

void imprimir_valores(int array[], int cont){
    int i = 0;
    int valor;
    for (i; i < cont; i++){
        valor = array[i];
        printf("%d", valor);
    }
    printf("\n");
}

void rellenar_valores(int array[], struct lista_dinamica *primero){
    lista_dinamica *auxiliar;
    int i = 0;
    auxiliar = primero;

    while (auxiliar != NULL){
        array[i] = auxiliar->valor;
        auxiliar = auxiliar->siguiente;
        i++;
    }
    printf("while has executed: %d times\n", i);
}

void anadir_elemento(int elemento, lista_dinamica *primero, lista_dinamica
*ultimo){
    lista_dinamica *nueva;
    nueva = (lista_dinamica *) malloc(sizeof(lista_dinamica));
    nueva->valor = elemento;
    nueva->siguiente = NULL;

    if (primero == NULL){
        primero = nueva;
        ultimo = nueva;
        printf("Añadiendo primer elemento\n");
    }
    else{
        ultimo->siguiente = nueva;
        ultimo = nueva;
        printf("El primer elemento ya ha sido creado, cualquier otro\n");
    }
}

int menor (int array[], int inicio, int fin){
	int menor = 99999;
	int i = inicio;

	for (i; i < fin; i++){
		menor = (array[i] < menor) ? array[i] : menor;
	}
	
	return menor;
}

int mayor (int array[], int inicio, int fin){
	int mayor = 0;
	int i = inicio;

	for (i; i < fin; i++){
		mayor = (array[i] > mayor) ? array[i] : mayor;
	}
	
	return mayor;
}

void seleccion_men_may(int array[], int inicio, int fin){
	int pos_menor;
	int temp;
    int i = inicio;

	for (i; i < fin; i++){
		pos_menor = menor(array, inicio, fin);
		temp = array[i];
		array[i] = array[pos_menor];
		array[pos_menor] = temp;
	}
	
}
void seleccion_may_men(int array[], int inicio, int fin){
	int pos_mayor;
	int temp;
    int i = inicio;
	for (i; i < fin; i++){
		pos_mayor = mayor(array, i, fin);
		temp = array[i];
		array[i] = array[pos_mayor];
		array[pos_mayor] = temp;
	}
	
}

void insercion_may_men(int array[], int inicio, int fin){
	int i = inicio +1;
	int f = fin +1;
	int temp, j;
	for (i; i <= f; i++){
		temp = array[i];
		j = i-1;
		while (j >= 0 && array[j] < temp){
			array [j + 1] = array [j];
			j--;
		}
		array [j+1] = temp;
	}
}    
void insercion_men_may(int array[], int inicio, int fin){
	int i = inicio +1;
	int f = fin +1;
	int temp, j;
	for (i; i <= f; i++){
		temp = array[i];
		j = i-1;
		while (j >= 0 && array[j] > temp){
			array [j + 1] = array [j];
			j--;
		}
		array [j+1] = temp;
	}
}
void burbuja_men_may(int array[], int inicio, int fin){
    int f = fin;
    int i = inicio;
    int temp;

    for (i; i < f; i++){
        for (f; f >= i; f--){
            if (array[f] < array[f-1]){
                temp = array[f-1];
                array[f-1] = array[f];
                array[f] = temp;
            }
        }
    }    
}

void burbuja_may_men(int array[], int inicio, int fin){
    int f = fin;
    int i = inicio;
    int temp;

    for (i; i < f; i++){
        for (f; f >= i; f--){
            if (array[f] > array[f-1]){
                temp = array[f-1];
                array[f-1] = array[f];
                array[f] = temp;
            }
        }
    }
}
    



