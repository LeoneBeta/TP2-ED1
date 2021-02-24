#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utilities.h"
#include "dataMaintenance.h"

//Carrega os dados do arquivo para as listas geradas /* 1 */
void loadFile(FILE *Arqv, listStudent lStudent){
    char string[500], value[2], mat[10];
    int i=0,j=0;

    TElementStudent eStudent;
    TElementDisc eDisc;
    TElementAv eAv;

    openFile(&Arqv);

    fseek(Arqv,0,SEEK_SET);
    //Loop percorrendo o arquivo, verificando se o mesmo chegou no fim.
    while(fgets(string,500,Arqv)){
        i = 0;
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

        while(string[i] != '@'){
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
            eDisc.nome[j] = '\0';
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
                    if(string[i] == '@' || string[i] == '\n')
                        break;
                    value[j] = string[i];
                    i++;
                    j++;
                }
                value[j] = '\0';
                eAv.note = atoi(value);
                j = 0;
                i++;
                //Passando a lista avaliação do atual aluno
                insertEndAv(lStudent->last->info.ld->last->info.la,eAv);

                if(string[i-1] == '\n')
                    break;
            }while(string[i-1] == '#');
            if(string[i-1] == '\n')
                break;
        }while(string[i-1] == '@');

        //Coloca o ponteiro na ultima posição utilizada anteriormente na função fgets para coletar a string
        //o posicionando para coletar a proxima string
        fseek(Arqv,0,SEEK_CUR);
    }
    closeFile(&Arqv);
}
//Cadastrar um novo aluno /* 2 */
void newStudent(listStudent lStudent){
    char menu[2], string[100];
    int insert;
    TElementStudent eStudent;
    TElementDisc eDisc;
    TElementAv eAv;

    do{
        printf("\nMatricula do Aluno: ");
        scanf("%d", &insert);
        eStudent.id = insert;

        //verificação de a matricula ja existe

        setbuf(stdin,NULL);
        printf("\nNome do Aluno: ");
        fgets(string,100,stdin);
        removeEnter(string);
        textConverter(string);
        //verificação se o nome ja existe
        strcpy(eStudent.nome,string);

        setbuf(stdin,NULL);
        printf("\nData de Nascimento: ");
        fgets(string,100,stdin);
        removeEnter(string);
        textConverter(string);
        //Verificaçaõ da data de nascimento
        strcpy(eStudent.birthDate,string);
        
        insertEndStudent(lStudent,eStudent);

        do{
            setbuf(stdin,NULL);
            printf("\nNome da Disciplina: ");
            fgets(string,100,stdin);
            removeEnter(string);
            textConverter(string);
            strcpy(eDisc.nome,string);

            insertEndDisc(lStudent->last->info.ld,eDisc);
            
            do{
                setbuf(stdin,NULL);
                printf("\nNome da Avaliação: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);
                strcpy(eAv.nomeAv,string);

                setbuf(stdin,NULL);
                printf("\nValor da Avaliação: ");
                scanf("%d",&eAv.value);

                setbuf(stdin,NULL);
                printf("\nNota da Avaliação: ");
                scanf("%d",&eAv.note);

                insertEndAv(lStudent->last->info.ld->last->info.la,eAv);

                setbuf(stdin,NULL);
                printf("\nDeseja cadastrar outra Avaliação");
                printf("\n0 - Sim ... 1 - Não ");
                fgets(menu,2,stdin);
                removeEnter(menu);
            }while(menu[0] != '1');

            setbuf(stdin,NULL);
            printf("\nDeseja cadastrar outra Disciplina");
            printf("\n0 - Sim ... 1 - Não ");
            fgets(menu,2,stdin);
            removeEnter(menu);
        }while(menu[0] != '1');

        setbuf(stdin,NULL);
        printf("\nDeseja cadastrar outro Aluno");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}

//Remover um Aluno /* 6 */
void removeStudent(listStudent lStudent){
    char menu[2];
    int mat, val;

    do{
        do{
            printf("\nForneça a Matricula");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatricula Inválida");
        }while(val == 0);

        printf("\nMatricula: %d",lStudent->current->info.id);
        printf("\nNome: %s",lStudent->current->info.nome);

        printf("\nDeseja deletar este Aluno?");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);

        if(menu[0] == '0'){
            removeElementStudent(lStudent,mat);
            printf("\nAluno Removido com Sucesso");
        }else
            printf("\nRemoção de Aluno Cancelado");

        setbuf(stdin,NULL);
        printf("\nDeseja Remover outro Aluno");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}
//Remover uma disciplina de um Aluno /* 7 */
void removeDisc(listStudent lStudent){
    char menu[2], nomeDisc[50];
    int mat, val;

    do{
        do{
            printf("\nForneça a Matricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatricula Inválida");
        }while(val == 0);

        do{
            setbuf(stdin,NULL);
            printf("\nForneça o nome da Disciplina");
            fets(nomeDisc,50,stdin);
            removeEnter(nomeDisc);
            textConverter(nomeDisc);

            val = setCurrentDisc(lStudent->current->info.ld,nomeDisc);
            if(val == 0)
                printf("\nDisciplina Inválida");
        }while(val == 0);

        printf("\nNome da Disciplina: %s",lStudent->current->info.ld->current->info.nome);
        printf("\nDeseja deletar esta Disciplina?");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);

        if(menu[0] == '0'){
            removeElementDisc(lStudent->current->info.ld,nomeDisc);
            printf("\nDisciplina Removido com Sucesso");
        }else
            printf("\nRemoção de Disciplina Cancelado");

        setbuf(stdin,NULL);
        printf("\nDeseja Remover outra Disciplina");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}
//Remover uma avaliação de uma disciplina de um Aluno /* 8 */
void removeAv(listStudent lStudent){
    char menu[2], nomeDisc[50], nomeAv[50];
    int mat, val;

    do{
        do{
            printf("\nForneça a Matricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatricula Inválida");
        }while(val == 0);

        do{
            setbuf(stdin,NULL);
            printf("\nForneça o nome da Disciplina");
            fets(nomeDisc,50,stdin);
            removeEnter(nomeDisc);
            textConverter(nomeDisc);

            val = setCurrentDisc(lStudent->current->info.ld,nomeDisc);
            if(val == 0)
                printf("\nDisciplina Inválida");
        }while(val == 0);
        
        do{
            setbuf(stdin,NULL);
            printf("\nForneça o nome da Avaliação");
            fets(nomeAv,50,stdin);
            removeEnter(nomeAv);
            textConverter(nomeAv);

            val = setCurrentAv(lStudent->current->info.ld->current->info.la,nomeAv);
            if(val == 0)
                printf("\nAvaliação Inválida");
        }while(val == 0);


        printf("\nNome da Avaliação: %s",lStudent->current->info.ld->current->info.la->current->info.nomeAv);
        printf("\nDeseja deletar esta Avaliação?");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);

        if(menu[0] == '0'){
            removeElementAv(lStudent->current->info.ld->current->info.la,nomeAv);
            printf("\nAvaliação Removido com Sucesso");
        }else
            printf("\nRemoção de Avaliação Cancelado");

        setbuf(stdin,NULL);
        printf("\nDeseja Remover outra Avaliação");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}