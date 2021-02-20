#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

void openFile(FILE **Arqv){
    
    *Arqv = fopen("Dados.txt", "r+");
    if(!*Arqv)
        *Arqv = fopen("Dados.txt","w+");
}

void retiraEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n'){
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}

void closeFile(FILE **Arqv){
    fclose(Arqv);
}