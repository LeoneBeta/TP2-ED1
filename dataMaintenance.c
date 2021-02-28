#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "utilities.h"
#include "dataMaintenance.h"

//Carrega os dados do arquivo para as listas geradas            /* 1 */
void loadFile(FILE *Arqv, listStudent lStudent){
    char string[1000], value[2], mat[10];
    int i=0,j=0;

    TElementStudent eStudent;
    TElementDisc eDisc;
    TElementAv eAv;

    Arqv = fopen("Dados.txt", "r+");
    if(!Arqv)
        Arqv = fopen("Dados.txt","w+");

    fseek(Arqv,0,SEEK_SET);
    //Loop percorrendo o arquivo, verificando se o mesmo chegou no fim.
    while(fgets(string,1000,Arqv)){
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

        printf("\n\nMatricula: %d",lStudent->last->info.id);
        printf("\nNome: %s",lStudent->last->info.nome);
        printf("\nData Nascimento: %s", lStudent->last->info.birthDate);

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
            printf("\nNome Disciplina: %s",lStudent->last->info.ld->last->info.nome);


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
                printf("\nNome Avaliação: %s",lStudent->last->info.ld->last->info.la->last->info.nomeAv);
                printf("\nValor: %d",lStudent->last->info.ld->last->info.la->last->info.value);
                printf("\nNota: %d",lStudent->last->info.ld->last->info.la->last->info.note);            

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
    fclose(Arqv);
}

//Cadastrar um novo aluno                                       /* 2 */
void newStudent(listStudent lStudent){
    char menu[2], string[100];
    int insert, mat, val;
    int totalDisc;
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
            totalDisc = 0;
            
            do{
                setbuf(stdin,NULL);
                printf("\nNome da Avaliação: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);
                strcpy(eAv.nomeAv,string);

                printf("\nPontos para distriuição: %d",100-totalDisc);
                do{
                    setbuf(stdin,NULL);
                    printf("\nValor da Avaliação: ");
                    scanf("%d",&eAv.value);

                    totalDisc += eAv.value;
                    if(totalDisc > 100)
                        printf("\nValor total da Disciplina ultrapassou 100 pontos");
                }while(totalDisc > 100);


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
    int insert, mat, val, totalDisc;
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
            totalDisc = 0;
            do{
                setbuf(stdin,NULL);
                printf("\nNome da Avaliação: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);
                strcpy(eAv.nomeAv,string);

                printf("\nPontos para distriuição: %d",100-totalDisc);
                do{
                    setbuf(stdin,NULL);
                    printf("\nValor da Avaliação: ");
                    scanf("%d",&eAv.value);

                    totalDisc += eAv.value;
                    if(totalDisc > 100)
                        printf("\nValor total da Disciplina ultrapassou 100 pontos");
                }while(totalDisc > 100);

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
    int insert, mat, val, totalDisc, i, sizeListAv;
    TElementAv eAv;

    do{
        do{ //Validação da Matricula Fornecida
            printf("\nMatricula do Aluno");
            scanf("%d",&mat);
            //verifica se a matricula existe
            val = setCurrentStudent(lStudent,mat);
            if(val == 0)
                printf("\nMatrícula não encontrada");
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
            
            totalDisc = 0;
            sizeListAv = lStudent->current->info.ld->current->info.la->size;
            for(i=0;i<sizeListAv;i++){
                totalDisc += lStudent->current->info.ld->current->info.la->current->info.value;
                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
            }

            do{
                setbuf(stdin,NULL);
                printf("\nNome da Avaliação: ");
                fgets(string,100,stdin);
                removeEnter(string);
                textConverter(string);
                strcpy(eAv.nomeAv,string);

                printf("\nPontos para distriuição: %d",100-totalDisc);
                do{
                    setbuf(stdin,NULL);
                    printf("\nValor da Avaliação: ");
                    scanf("%d",&eAv.value);

                    totalDisc += eAv.value;
                    if(totalDisc > 100)
                        printf("\nValor total da Disciplina ultrapassou 100 pontos");
                }while(totalDisc > 100);

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

//Verifica a Integridade das Listas                             /* 5 */
int checkIntegrity(listStudent lStudent){
    int i, j, k;
    int sizeListStudent, sizeListDisc, sizeListAv, sumAv = 0;

    sizeListStudent = lStudent->size;
    if(sizeListStudent < 1){
        printf("\nLista de Alunos vazia");
        return 0;
    }
    lStudent->current = lStudent->first;
    for(i=0;i<sizeListStudent;i++){
        
        sizeListDisc = lStudent->current->info.ld->size;
        if(sizeListDisc < 1){
            printf("\nAluno %s não está matriculado em nenhuma disciplina",lStudent->current->info.nome);
            return 0;
        }
        lStudent->current->info.ld->current = lStudent->current->info.ld->first;
        for(j=0;j<sizeListDisc;j++){

            sizeListAv = lStudent->current->info.ld->current->info.la->size;
            if(sizeListAv < 1){
                printf("\nAluno: %s",lStudent->current->info.nome);
                printf("\nDisciplina %s sem avaliações cadastradas", lStudent->current->info.ld->current->info.nome);
                return 0;
            }
            sumAv = 0;
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
            for(k=0;k<sizeListAv;k++){
                sumAv += lStudent->current->info.ld->current->info.la->current->info.value;
                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
            }
            if(sumAv != 100){
                printf("\nAluno: %s",lStudent->current->info.nome);
                printf("\nTotal de Pontos distribuidos na Disciplina %s é diferente que 100 pontos",lStudent->current->info.ld->current->info.nome);
                return 0;
            }
            lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
        }
        lStudent->current = lStudent->current->next;
    }
    printf("\nListas Integras");
    return 1;
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
    int i, j, k, contDisc = 0;
    int sizeListStudent, sizeListDisc, sizeListAv, sumAv = 0, aprove;

    printf("\nAlunos Aprovados");
    printf("\nMatrícula\tNome\t\t\tData de Nascimento");

    sizeListStudent = lStudent->size;
    lStudent->current = lStudent->first;
    for(i=0;i<sizeListStudent;i++){         //Percorrer a Lista Aluno
        aprove = 1;
        printf("\n%d\t\t%s\t%s",lStudent->current->info.id,lStudent->current->info.nome,lStudent->current->info.birthDate);

        sizeListDisc = lStudent->current->info.ld->size;
        lStudent->current->info.ld->current = lStudent->current->info.ld->first;
        for(j=0;j<sizeListDisc;j++){        //Percorrer a Lista Disciplina do Aluno corrente

            sumAv = 0;
            sizeListAv = lStudent->current->info.ld->current->info.la->size;
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
            for(k=0;k<sizeListAv;k++){      //Percorrer a Lista Avaliação da Disciplina corrente

                sumAv += lStudent->current->info.ld->current->info.la->current->info.note;

                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
            }
            if(sumAv < 60){
                aprove = 0;
                break;
            }
            lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
        }
        //Se todas as disciplinas do Aluno corrente estiverem com nota acima de 60, ele printa as disciplinas
        //e notas do aluno
        if(aprove == 1){
            sizeListDisc = lStudent->current->info.ld->size;
            lStudent->current->info.ld->current = lStudent->current->info.ld->first;
            for(j=0;j<sizeListDisc;j++){        //Percorrer a Lista Disciplina do Aluno corrente

                sumAv = 0;
                sizeListAv = lStudent->current->info.ld->current->info.la->size;
                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
                for(k=0;k<sizeListAv;k++){      //Percorrer a Lista Avaliação da Disciplina corrente
                    
                    sumAv += lStudent->current->info.ld->current->info.la->current->info.note;
                    
                    lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
                }
                //Printa a Disciplina corrente e a soma da nota das avaliações
                printf("\n%s: %d",lStudent->current->info.ld->current->info.nome,sumAv);
                lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
            }
            //Printa a média da nota de todas as Disciplinas do aluno aprovado
            printf("\n\t\tMédia: %d\n", sumAv/sizeListDisc);
        }
        //Passa o ponteiro Current para o proximo Aluno da lista
        lStudent->current = lStudent->current->next;
    }
}
//Ṕrinta os alunos Reprovados                                   /* 10 */
void failedStudents(listStudent lStudent){
    int i, j, k, contDisc = 0;
    int sizeListStudent, sizeListDisc, sizeListAv, sumAv = 0, aprove, average = 0;

    printf("\nAlunos Reprovados");
    printf("\nMatrícula\tNome\t\t\tData de Nascimento");

    sizeListStudent = lStudent->size;
    lStudent->current = lStudent->first;
    for(i=0;i<sizeListStudent;i++){         //Percorrer a Lista Aluno
        aprove = 0;

        sizeListDisc = lStudent->current->info.ld->size;
        lStudent->current->info.ld->current = lStudent->current->info.ld->first;
        for(j=0;j<sizeListDisc;j++){        //Percorrer a Lista Disciplina do Aluno corrente

            sizeListAv = lStudent->current->info.ld->current->info.la->size;
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
            for(k=0;k<sizeListAv;k++){      //Percorrer a Lista Avaliação da Disciplina corrente

                sumAv += lStudent->current->info.ld->current->info.la->current->info.note;

                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
            }
            if(sumAv > 60){
                aprove = 1;
                break;
            }
            lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
        }
        //Se o Aluno corrente não conseguir média em pelo menos 1 Disciplina, ele consta como reprovado,
        //então é printado suas notas nas disciplinas e a média total
        if(aprove == 0){
            printf("\n%d\t%s\t\t\t%s",lStudent->current->info.id,lStudent->current->info.nome,lStudent->current->info.birthDate);
            sizeListDisc = lStudent->current->info.ld->size;
            lStudent->current->info.ld->current = lStudent->current->info.ld->first;
            for(j=0;j<sizeListDisc;i++){        //Percorrer a Lista Disciplina do Aluno corrente

                sizeListAv = lStudent->current->info.ld->current->info.la->size;
                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
                for(k=0;k<sizeListAv;k++){      //Percorrer a Lista Avaliação da Disciplina corrente
                    
                    sumAv += lStudent->current->info.ld->current->info.la->current->info.note;
                    
                    lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
                }
                //Printa a Disciplina corrente e a soma da nota das avaliações
                printf("\n%s: %d",lStudent->current->info.ld->current->info.nome,sumAv);
                average += sumAv;
                lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
            }
            //Printa a média da nota de todas as Disciplinas do aluno aprovado
            printf("\n\t\tMédia: %d", average/sizeListDisc);
        }
        //Passa o ponteiro Current para o proximo Aluno da lista
        lStudent->current = lStudent->current->next;
    }
}

//ALtera Nota                                                   /* 11 */
void alterNote(listStudent lStudent){
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

        printf("\nForneça a nova Nota");
        scanf("%d",&lStudent->current->info.ld->current->info.la->current->info.note);

        setbuf(stdin,NULL);
        printf("\nDeseja alterar outra Nota");
        printf("\n0 - Sim ... 1 - Não ");
        fgets(menu,2,stdin);
        removeEnter(menu);
    }while(menu[0] != '1');
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


/*~~~~~ EM DESENVOLVIMENTO ~~~~~*/
//Gravar as listas no arquivo                                   /* 14 */
void writeToFile(FILE *Arqv, listStudent lStudent){
    char string[1000], valueString[10];
    int i, j, k, pos = 0, posString = 0, contAv = 0, contDisc = 0, posValue = 0;
    int sizeListStudent, sizeListDisc, sizeListAv;
    Arqv = fopen("Dados.txt","w+");
    fseek(Arqv,0,SEEK_SET);

    checkIntegrity(lStudent);

    /*
    for(posString=0;posString<999;posString++)
        string[i] = '\0';
    for(posValue=0;posValue<9;posValue++)
        valueString[posValue] = '\0';
    */

    sizeListStudent = lStudent->size;
    lStudent->current = lStudent->first;
    for(i=0;i<sizeListStudent;i++){         //Percorrer a Lista Aluno
        posString = 0;
        //Transforma o valor Matricula de int para string para manipulação
        sprintf(valueString,"%d",lStudent->current->info.id);
        for(pos=0;pos<10;pos++){
            if(valueString[pos] == '\0')
                break; 
            string[posString] = valueString[pos];
            posString++;
        }
        //Após encontrar o /0, o programa incrementa a cerquilha separando os dados
        string[posString] = '#';
        posString++;
        for(pos=0;pos<50;pos++){
            if(lStudent->current->info.nome[pos] == '\n')
                break;
            string[posString] = lStudent->current->info.nome[pos];
            posString++;
        }
        string[posString] = '#';
        posString++;
        for(pos=0;pos<11;pos++){
            if(lStudent->current->info.birthDate[pos] == '\n')
                break;
            string[posString] = lStudent->current->info.birthDate[pos];
            posString++;
        }
        string[posString] = '@';
        posString++;


        contDisc = 0;
        sizeListDisc = lStudent->current->info.ld->size;
        lStudent->current->info.ld->current = lStudent->current->info.ld->first;
        for(j=0;j<sizeListDisc;j++){        //Percorrer a Lista Disciplina do Aluno corrente

            for(pos=0;pos<20;pos++){
                if(lStudent->current->info.ld->current->info.nome[pos] == '\n')
                    break;
                string[posString] = lStudent->current->info.ld->current->info.nome[pos];
                posString++;
            }
            string[posString] = '#';
            posString++;

            contAv = 0;
            sizeListAv = lStudent->current->info.ld->current->info.la->size;
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
            for(k=0;k<sizeListAv;k++){      //Percorrer a Lista Avaliação da Disciplina corrente

                for(pos=0;pos<20;pos++){
                    if(lStudent->current->info.ld->current->info.la->current->info.nomeAv[pos] == '\n')
                        break;
                    string[posString] = lStudent->current->info.birthDate[pos];
                    posString++;
                }
                string[posString] = '#';
                posString++;

                sprintf(valueString,"%d",lStudent->current->info.ld->current->info.la->current->info.value);
                for(pos=0;pos<10;pos++){
                    if(valueString[pos] == '\0')
                        break; 
                    string[posString] = valueString[pos];
                    posString++;
                }
                string[posString] = '#';
                posString++;
            
                sprintf(valueString,"%d",lStudent->current->info.ld->current->info.la->current->info.note);
                for(pos=0;pos<10;pos++){
                    if(valueString[pos] == '\0')
                        break; 
                    string[posString] = valueString[pos];
                    posString++;
                }

                //Incrementa a quantidade de avaliações lidas em seguida seta o ponteiro current das avaliações
                //para o próximo Nodo
                contAv++;
                lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
            
                //Verifica se tem mais avaliações para ser lidas, casom sim, coloca uma cerquilha para
                //continuar a leitura
                if(contAv < sizeListAv){
                    string[posString] = '#';
                    posString++;
                }
            }

            //Incrementa a quantiade de Disciplinas lidas, em seguida seta o ponteiro current para o próximo
            //Nodo
            contDisc++;
            lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;

            //Verifica se tem mais Disciplinas neste aluno, se sim, coloca uma '@' e continua, se não, coloca 
            //um '\n' identificando o fim da string
            if(contDisc < sizeListDisc){
                string[posString] = '@';
                posString++;
            }else{
                string[posString] = '\n';
                posString++;
            }
        }
        printf("\n%s",string);
        //Gravar a string no arquivo
        fprintf(Arqv,"%s",string);
        fseek(Arqv,0,SEEK_CUR);
        lStudent->current = lStudent->current->next;
    }
    fclose(Arqv);
}
/*~~~~~ EM DESENVOLVIMENTO ~~~~~*/


//Printa a consulta requerida
void printList(listStudent lStudent){
    int sizeListDisc, sizeListAv;
    int i = 1, j = 1;

    printf("\nMatrícula: %d",lStudent->current->info.id);
    printf("\nNome: %s",lStudent->current->info.nome);
    printf("\nData de Nascimento: %s",lStudent->current->info.birthDate);

    sizeListDisc = lStudent->current->info.ld->size;
    //Ponteiro Current apontar para o primeiro nodo da Lista Disc
    lStudent->current->info.ld->current = lStudent->current->info.ld->first;

    for(i=1;i<=sizeListDisc;i++){
        printf("\nDisciplina: %s", lStudent->current->info.ld->current->info.nome);
        
        //Ponteiro Current da lista Avaliação aponta para o primeiro Nodo da lista
        sizeListAv = lStudent->current->info.ld->current->info.la->size;
        lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->first;
        for(j=1;j<=sizeListAv;j++){
            printf("\nAvaliação: %s",lStudent->current->info.ld->current->info.la->current->info.nomeAv);
            printf("\nValor: %d",lStudent->current->info.ld->current->info.la->current->info.value);
            printf("\nNota: %d",lStudent->current->info.ld->current->info.la->current->info.note);
            
            //Ponteiro Current da lista Av. passa a apontar para o proximo nodo da lista Avaliação
            lStudent->current->info.ld->current->info.la->current = lStudent->current->info.ld->current->info.la->current->next;
        }
        //Ponteiro Current da lista Disc. passa a apontar para o proximo nodo da lista Disc
        lStudent->current->info.ld->current = lStudent->current->info.ld->current->next;
    }
}