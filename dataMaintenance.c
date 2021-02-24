#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utilities.h"
#include "dataMaintenance.h"

//Carrega os dados do arquivo para as listas geradas            /* 1 */
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

//Cadastrar um novo aluno                                       /* 2 */
void newStudent(listStudent lStudent){
    char menu[2], string[100];
    int insert, mat, val;
    TElementStudent eStudent;
    TElementDisc eDisc;
    TElementAv eAv;

    do{
        do{ //Validação da Matricula Fornecida
            printf("\nMatricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 1)
                printf("\nMatricula já cadastrda");
            else
                break;
        }while(val == 1);
        eStudent.id = mat;

        setbuf(stdin,NULL);
        printf("\nNome do Aluno: ");
        fgets(string,100,stdin);
        removeEnter(string);
        textConverter(string);

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
//Cadastrar uma nova Disciplina para um Aluno                   /* 3 */
void newDisc(listStudent lStudent){
    char menu[2], string[100];
    int insert, mat, val;
    TElementDisc eDisc;
    TElementAv eAv;

    do{
        do{ //Validação da Matricula Fornecida
            printf("\nMatricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatrcula não encontrada");
        }while(val == 0);

        do{
            do{ //Validação da Matricula Fornecida
                setbuf(stdin,NULL);
                printf("\nNome da Disciplina: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);

                //Pega a posição da disciplina caso ja tenha uma cadastrada com esse nome
                val = setCurrentDisc(lStudent->current->info.ld,string);
                if(val == 1)
                    printf("\nDisciplina já Cadastrada");
            }while(val == 1);
            strcpy(eDisc.nome,string);

            insertEndDisc(lStudent->current->info.ld,eDisc);
            
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

                insertEndAv(lStudent->current->info.ld->last->info.la,eAv);

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
        printf("\nDeseja cadastrar disciplina em outro aluno");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}
//Cadastraruma nova avaliação numa disciplina de um aluno       /* 4 */
void newAv(listStudent lStudent){
    char menu[2], string[100];
    int insert, mat, val;
    TElementAv eAv;

    do{
        do{ //Validação da Matricula Fornecida
            printf("\nMatricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatrcula não encontrada");
        }while(val == 0);

        do{
            do{ //Validação da Matricula Fornecida
                setbuf(stdin,NULL);
                printf("\nNome da Disciplina: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);

                //Pega a posição da disciplina caso ja tenha uma cadastrada com esse nome
                val = setCurrentDisc(lStudent->current->info.ld,string);
                if(val == 0)
                    printf("\nDisciplina não encontrada");
            }while(val == 0);

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

                insertEndAv(lStudent->current->info.ld->current->info.la,eAv);

                setbuf(stdin,NULL);
                printf("\nDeseja cadastrar outra Avaliação");
                printf("\n0 - Sim ... 1 - Não ");
                fgets(menu,2,stdin);
                removeEnter(menu);
            }while(menu[0] != '1');

            setbuf(stdin,NULL);
            printf("\nDeseja cadastrar Avaliação em outra Disciplina");
            printf("\n0 - Sim ... 1 - Não ");
            fgets(menu,2,stdin);
            removeEnter(menu);
        }while(menu[0] != '1');

        setbuf(stdin,NULL);
        printf("\nDeseja cadastrar em outro Aluno?");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}

//Remover um Aluno                                              /* 6 */
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
//Remover uma disciplina de um Aluno                            /* 7 */
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
            fgets(nomeDisc,50,stdin);
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
//Remover uma avaliação de uma disciplina de um Aluno           /* 8 */
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
            fgets(nomeDisc,50,stdin);
            removeEnter(nomeDisc);
            textConverter(nomeDisc);

            val = setCurrentDisc(lStudent->current->info.ld,nomeDisc);
            if(val == 0)
                printf("\nDisciplina Inválida");
        }while(val == 0);
        
        do{
            setbuf(stdin,NULL);
            printf("\nForneça o nome da Avaliação");
            fgets(nomeAv,50,stdin);
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

//Printa os alunos Aprovados                                    /* 9 */
void approvedStudents(listStudent lStudent){

}
//Ṕrinta os alunos Reprovados                                   /* 10 */
void failedStudents(listStudent lStudent){

}

//Consulta Alunos por Matricula                                 /* 12 */
void consultRegistration(listStudent lStudent){
    char menu[2];
    int mat, val, i, j;

    do{
        do{
            printf("\nForneça a Matricula");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatricula Inválida");
        }while(val == 0);

        printList(lStudent);

        setbuf(stdin,NULL);
        printf("\nDeseja Consultar outro Aluno");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}
//Consulta Alunos por Nome                                      /* 13 */
void consultName(listStudent lStudent){
    char menu[2], pref[5];
    int val = 0, i, j, sizeListStudent;

    do{
        do{
            setbuf(stdin,NULL);
            printf("\nForneça as 3 primeiras letras do Aluno");
            fgets(pref,5,stdin);
            removeEnter(pref);
            textConverter(pref);

            //Busca na lista Alunos o prefixo fornecido, caso não encontrar, printa um aviso e retorna a pedir
            //um novo prefixo
            sizeListStudent = lStudent->size;
            lStudent->current = lStudent->first;
            for(i=0;i<sizeListStudent;i++){
                if(strncmp(lStudent->current->info.nome,pref,3) == 0){
                    val = 1;
                    break;
                }else
                    lStudent->current = lStudent->current->next;
            }
            if(val != 1)
                printf("\nPrefixo não encontrado");
        }while(val != 1);

        printList(lStudent);

        setbuf(stdin,NULL);
        printf("\nDeseja Consultar outro Aluno");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
}

//Printa a consulta requerida
void printList(listStudent lStudent){
    int sizeListDisc, sizeListAv;
    int i, j;

    printf("\nMatrícula: %d",lStudent->current->info.id);
    printf("\nNome: %s",lStudent->current->info.nome);
    printf("\nData de Nascimento: %s",lStudent->current->info.birthDate);

    //Percorre a lista de disciplinas desse aluno
    sizeListDisc = lStudent->current->info.ld->size ;
    //Ponteiro Current apontar para o primeiro nodo da Lista Disc
    lStudent->current->info.ld->current = lStudent->current->info.ld->first;
    for(i=0;i<sizeListDisc;i++){
        printf("\nDisciplina: %s", lStudent->current->info.ld->current->info.nome);
        
        //Ponteiro Current da lista Avaliação aponta para o primeiro Nodo da lista
        sizeListAv = lStudent->current->info.ld->current->info.la->size;
        lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
        for(j=0;j<sizeListAv;i++){
            printf("Avaliação: %s",lStudent->current->info.ld->current->info.la->current->info.nomeAv);
            printf("Valor: %d",lStudent->current->info.ld->current->info.la->current->info.value);
            printf("Nota: %d",lStudent->current->info.ld->current->info.la->current->info.note);
            
            //Ponteiro Current da lista Av. passa a apontar para o proximo nodo da lista Avaliação
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
        }
        //Ponteiro Current da lista Disc. passa a apontar para o proximo nodo da lista Disc
        lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
    }
}