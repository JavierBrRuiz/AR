#include <stdlib.h>
#include <time.h>
#include "caracteres.h"

char rand_Char(){
    time_t t;
    int binary_choice;
    char r;
    int ctoi;
    srand((unsigned) time(&t));

    binary_choice = rand() % 2;

    if (binary_choice == 0) {
        ctoi = (rand() % MOD_CHAR) + RANG_MAYUS;
    }
    else {
        ctoi = (rand() % MOD_CHAR) + RANG_MINUS;
    }

    r = ctoi;

    return r;
}

char es_Minus(char c){
    int ctoi = c;

    return (ctoi >= 97 && ctoi <= 122);
}

char es_Mayus (char c){
    int ctoi = c;

    return (ctoi >= 65 && ctoi <= 90);
}

char rand_Num(){
    time_t t;
    int r;
    char itoc;
    
    srand((unsigned) time(&t));

    r = (rand() % MOD_NUM) + RANG_NUM;
    itoc = r;
    return itoc;
}
