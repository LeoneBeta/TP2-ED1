#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataMaintenance.h"
#include "list.h"

void loadFile(FILE *Arqv){
    char *string, value[2];
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




    //~~~~EM DESENVOLVIMENTO~~~~~
    
    fseek(Arqv,0,SEEK_SET);
    while(fgets(string,300,Arqv)){
        
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

        //Sai do Loop quando não econtra mais disciplinas
        do{
            while(string[i] != '#'){
                ed.nome[j] = string[i];
                i++;
                j++;
            }

            j=0;
            while(string[i] != '#'){
                ea.nomeAv[j] = string[i];
            }

            j=0;
            while(string[i] != '#'){
                value[j] = string[i];
                i++;
                j++;
            }
            ed.value = atoi(value);

            j=0;
            while(string[i] != "@" || string[i] != '\n'){
                value[j] = string[i];
                i++;
                j++;
            }
            ed.note = atoi(value);

        }while(string[i] != '\n');

        //~~~~EM DESENVOLVIMENTO~~~~~


        
        fseek(Arqv,0,SEEK_CUR);
    }
}