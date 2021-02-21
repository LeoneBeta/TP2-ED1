#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataMaintenance.h"
#include "list.h"

void loadFile(FILE *Arqv){
    char *string, value[2];
    int i=0,j=0;

    TNodoStudent *nStudent;
    TNodoDisc *nDisc;
    TNodoAv *nAv;

    listStudent lstudent;

    nStudent = (TNodoStudent*)malloc(sizeof(TNodoStudent));

    openFile(Arqv);
    
    lstudent = creatListStudent();

    if(lstudent == NULL)
        printf("\nErro ao criar a Lista de Alunos");




    //~~~~EM DESENVOLVIMENTO~~~~~
    
    fseek(Arqv,0,SEEK_SET);
    while(fgets(string,300,Arqv)){
        while(string[i] != '#'){
            if(string[i] != '#'){
                nStudent->info.nome[j] = string[i];
                j++;
                i++;
            }else
                nStudent->info.nome[j] = '\0';
        }

        j=0;
        while(string[i] != '#'){
            if(string[i] != '@'){
                nStudent->info.birthDate[j] = string[i];
                j++;
                i++;
            }else
                nStudent->info.birthDate[j] = '\0';
        }
        
        //Sai do Loop quando não econtra mais disciplinas
        j=0;
        do{
            while(string[i] != '#'){
                if(string[i] != '#'){
                    nStudent->ld->first->info.nome[j] = string[i];
                    i++;
                    j++;
                }else
                    nStudent->ld->first->info.nome[j] = '\0';
            }

            j=0;
            while(string[i] != '#'){
                if(string[i] != '#'){
                    nStudent->ld->first->la->first->info.nomeAv[j] = string[i];
                    i++;
                    j++;
                }else
                    nStudent->ld->first->la->first->info.nomeAv[j] = '\0';
            }

            j=0;
            while(string[i] != '#'){
                    value[j] = string[i];
                    i++;
                    j++;
            }
            nStudent->ld->first->info.value = atoi(value);

            j=0;
            while(string[i] != "@" || string[i] != '\n'){
                    value[j] = string[i];
                    i++;
                    j++;
            }
            nStudent->ld->first->info.note = atoi(value);

        }while(string[i] != '\n');

        //~~~~EM DESENVOLVIMENTO~~~~~


        
        fseek(Arqv,0,SEEK_CUR);
    }
}