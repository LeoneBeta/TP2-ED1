#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataMaintenance.h"
#include "list.h"

void loadFile(FILE *Arqv){
    char *string;
    int i=0,j=0;

    TElementStudent es;
    TElementDisc ed;
    TElementAv ea;

    listStudent lstudent;
    listDisc ldisc;
    listAv lav;

    openFile(Arqv);
    

    lstudent = creatListStudent();
    ldisc = creatListDisc();
    lav = creatListAv();

    if(lstudent == NULL)
        printf("\nErro ao criar a Lista de Alunos");
    if(ldisc == NULL)
        printf("\nErro ao criar a Lista de Disciplinas");
    if(lav == NULL)
        printf("\nErro ao criar a Lista de Tarefas");




    //Testar a função fgets para tirar uma string do arquivo até o \n
    fseek(Arqv,0,SEEK_SET);
    while(fgets(string,100,Arqv)){
        do{
            if(string[i] != '#'){
                es.nome[j] = string[i];
                j++;
                i++;
            }else
               es.nome[j] = '\0';

            j=0;
            if(string[i] != '@'){
                es.birthDate[j] = string[i];
                j++;
                i++;
            }else
                es.birthDate[j] = '\0';
            j=0;




        }while(string[i]== '\n');
    }
}