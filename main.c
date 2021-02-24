#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "list.h"
#include "utilities.h"
#include "dataMaintenance.h"

int main(){
    setlocale(LC_ALL,"portuguese");
    char menu[3];
    FILE *Arqv;
    
    listStudent lStudent;

    lStudent = creatListStudent();
    if(lStudent == NULL)
        printf("\nErro ao criar a Lista de Alunos");
    
    do{

        setbuf(stdin,NULL);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~ 1 - Carregar Dados ~~~~~~~~~~~");
        printf("\n~~ 2 - Cadastrar Alunos ~~~~~~~~~");
        printf("\n~~ 3 - Cadastrar Disciplina ~~~~~");
        printf("\n~~ 4 - Cadastrar Avaliação ~~~~~~");
        printf("\n~~ 5 - Verificar Integridade ~~~~");
        printf("\n~~ 6 - Excluir Aluno ~~~~~~~~~~~~");
        printf("\n~~ 7 - Excluir Disciplina ~~~~~~~");
        printf("\n~~ 8 - Excluir Avaliação ~~~~~~~~");
        printf("\n~~ 9 - Relatório de Aprovados ~~~");
        printf("\n~~ 10 - Relatório de Reprovados ~");
        printf("\n~~ 11 - Alterar Nota ~~~~~~~~~~~~");
        printf("\n~~ 12 - Consulta Matricula ~~~~~~");
        printf("\n~~ 13 - Consulta Nome ~~~~~~~~~~~");
        printf("\n~~ 14 - Gravar ~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~ 0 - Sair ~~~~~~~~~~~~~~~~~~~~~");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        fgets(menu,3,stdin);
        removeEnter(menu);

        if(menu[0] == '1'){loadFile(Arqv,lStudent);}
        if(menu[0] == '2'){newStudent(lStudent);}
        if(menu[0] == '3'){}
        if(menu[0] == '4'){}
        if(menu[0] == '5'){}
        if(menu[0] == '6'){removeStudent(lStudent);}
        if(menu[0] == '7'){removeDisc(lStudent);}
        if(menu[0] == '8'){removeAv(lStudent);}
        if(menu[0] == '9'){}
        if(menu[0] == '1' && menu[1] == '0'){}
        if(menu[0] == '1' && menu[1] == '1'){}
        if(menu[0] == '1' && menu[1] == '2'){}
        if(menu[0] == '1' && menu[1] == '3'){}
        if(menu[0] == '1' && menu[1] == '4'){}

    }while(menu[0] != '0');
    return 0;
}