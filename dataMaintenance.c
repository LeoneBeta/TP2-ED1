#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataMaintenance.h"

void loadFile(FILE *Arqv){
    char *string;
    
    openFile(Arqv);
    

    //Testar a função fgets para tirar uma string do arquivo até o \n
    fseek(Arqv,0,SEEK_SET);
    while(fgets(string,100,Arqv));
}