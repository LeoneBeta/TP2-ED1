#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utilities.h"
#include "dataMaintenance.h"

//Carrega os dados do arquivo para as listas geradas
void loadFile(FILE *Arqv, listStudent lStudent){
    char string[500], value[2], mat[10];
    int i=0,j=0;

    TElementStudent eStudent;
    TElementDisc eDisc;
    TElementAv eAv;

    openFile(&Arqv);

    /*~~~~~~~ EM DESENVOLVIMENTO ~~~~~~~~*/
    fseek(Arqv,0,SEEK_SET);
    //Loop percorrendo o arquivo, verificando se o mesmo chegou no fim.
    while(fgets(string,500,Arqv)){
        printf("\n%s",string);

        j = 0;
        while(string[i] != '#'){
        mat[j] = string[i];
        i++;
        j++;
        }
        mat[j] = '\0';
        eStudent.id = atoi(mat);
        i++;
        j = 0;

        while(string[i] != '#'){
            eStudent.nome[j] = string[i];
            i++;
            j++;
        }
        eStudent.nome[j] = '\0';
        i++;
        j = 0;

        while(string[i] != '#'){
            eStudent.birthDate[j] = string[i];
            i++;
            j++;
        }
        eStudent.birthDate[j] = '\0';
        i++;
        j = 0;

        insertEndStudent(lStudent,eStudent);

        //Loop que percorre as disciplinas da string, se encontrar um @ ao final da coleta dos dados
        //ele retorna armazenando outra disciplina.
        do{ 
            while(string[i] != '#'){
                eDisc.nome[j] = string[i];
                i++;
                j++;
            }
            eDisc.nome[j] = string[i];
            i++;
            j = 0;

            insertEndDisc(lStudent->last->info.ld,eDisc);

            //Loop armazenando as avaliações, no final da coleta ele verifica se exite um '@' ou '#'
            //caso encontre um '#', quer dizer que existe outra avaliação a ser coletada
            do{
                
                while(string[i] != '#'){
                    eAv.nomeAv[j] = string[i];
                    i++;
                    j++;
                }
                eAv.nomeAv[j] = '\0';
                i++;
                j = 0;

                while(string[i] != '#'){
                    value[j] = string[i];
                    i++;
                    j++;
                }
                value[j] = '\0';
                eAv.value = atoi(value);
                i++;
                j = 0;

                while(string[i] != '#'){
                    value[j] = string[i];
                    i++;
                    j++;
                }
                value[j] = '\0';
                eAv.note = atoi(value);
                i++;
                j = 0;
                
                //Resolver o problema de Inserir um novo elemento na lista Avaliação
                //insertEndAv(lStudent->last->info.ld->last->info.la,eAv);

            }while(string[i] == '#');
        }while(string[i] == '@');

        //Coloca o ponteiro na ultima posição utilizada anteriormente na função fgets para coletar a string
        //o posicionando para coletar a proxima string
        fseek(Arqv,0,SEEK_CUR);
    }
    
    /*~~~~~~~ EM DESENVOLVIMENTO ~~~~~~~~*/
}

void newStudent(listStudent listStudent){
    
}