#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataMaintenance.h"
#include "list.h"
#include "utilities.h"

void loadFile(FILE *Arqv){
    char string[500], value[2], mat[10];
    int i=0,j=0;

    TNodoStudent *nStudent;
    TNodoDisc *nDisc;
    TNodoAv *nAv;

    listStudent lstudent;

    openFile(&Arqv);

    nStudent = (TNodoStudent*)malloc(sizeof(TNodoStudent));
    lstudent = creatListStudent();

    if(lstudent == NULL)
        printf("\nErro ao criar a Lista de Alunos");


    /*~~~~~~~ EM DESENVOLVIMENTO ~~~~~~~~*/
    
    fseek(Arqv,0,SEEK_SET);
    while(fgets(string,500,Arqv)){
        while(string[i] != '#'){
            if(string[1 != '#']){
                mat[j] = string[i];
            j++;
            i++;
            }else
                mat[j] = string[i];
            nStudent->info.id = atoi(mat);
        }

        j=0;
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
                    nDisc->info.nome[j] = string[i];
                    i++;
                    j++;
                }else
                    nDisc->info.nome[j] = '\0';
            }

            j=0;
            while(string[i] != '#'){
                if(string[i] != '#'){
                    nAv->info.nomeAv[j] = string[i];
                    i++;
                    j++;
                }else
                    nAv->info.nomeAv[j] = '\0';
            }

            j=0;
            while(string[i] != '#'){
                    value[j] = string[i];
                    i++;
                    j++;
            }
            nDisc->info.value = atoi(value);

            j=0;
            while(string[i] != '@' || string[i] != '\n'){
                    value[j] = string[i];
                    i++;
                    j++;
            }
            nDisc->info.note = atoi(value);

        printf("Matricula: %d", nStudent->info.id);
        printf("Nome do Aluno: %s", nStudent->info.nome);
        printf("Data de Nascimento: %s", nStudent->info.birthDate);

        }while(string[i] != '\n');

        /*~~~~~~~ EM DESENVOLVIMENTO ~~~~~~~~*/


        
        fseek(Arqv,0,SEEK_CUR);
    }
}