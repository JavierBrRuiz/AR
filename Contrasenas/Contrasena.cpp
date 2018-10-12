#include "Contrasena.h"
#include "caracteres.h"
#include <string.h>
#include <stdlib.h>
Contrasena::Contrasena(){
    length = 8; 
    caracteres[length];
    char input;
    int i, bc;
    for (i = 0; i < length; i++){
        bc = rand() % 2;
        if (bc == 0){
            input = rand_Char();
            caracteres [i] = input;
        }
        else{
           input = rand_Num();
           caracteres[i] = input
        }
    }

}
Contrasena::Contrasena(int _length){
    length = _length;
    caracteres[length];    
    for (i = 0; i < length; i++){
       bc = rand() % 2;
       if (bc == 0){
           input = rand_Char();
           caracteres [i] = input;
        }
        else{
           input = rand_Num();
           caracteres [i] = input
        }
    }

}
Contrasena::~Contrasena(){
    
}

bool Contrasena::es_Constrasena(int _length){
    if (length != _length){
        return false;
    }
    else{

        int i, ctoi, cont = 0;
        for (i = 0; i < length; i++){
            ctoi = caracteres[i];
            if ((ctoi <= 57 && ctoi >= 48) || (ctoi <= 90 && ctoi >= 65) ||(ctoi<= 122 && ctoi >=97)){
                cont++;
            }
        }
        return (cont == length);
    }
}
