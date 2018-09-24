#include <stdio.h>
#include <stdlib.h>

int main(){
    
}


int *insercion_men_may(int array[], int inicio, int fin){
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

    return array;
}

int *insercion_may_men(int array[], int inicio, int fin){
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

    return array;
}


