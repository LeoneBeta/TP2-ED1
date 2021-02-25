#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

void removeEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n'){
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}

//Converse todo texto para maiusculo
void textConverter(char string[]){
    int i = 0;
    do{
        string[i] = toupper(string[i]);
        i++;
    }while(string[i]!= '\0');
}