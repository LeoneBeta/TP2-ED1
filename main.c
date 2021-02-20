#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "list.h"
#include "utilities.h"

int main(){
    setlocale(LC_ALL,"portuguese");
    char menu[3];
    FILE *Arqv;
    

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
    fgets(menu,3,stdin);
    retiraEnter(menu);

    if(menu == '1'){}
    if(menu == '2'){}
    if(menu == '3'){}
    if(menu == '4'){}
    if(menu == '5'){}
    if(menu == '6'){}
    if(menu == '7'){}
    if(menu == '8'){}
    if(menu == '9'){}
    if(menu == '10'){}
    if(menu == '11'){}
    if(menu == '12'){}
    if(menu == '13'){}
    if(menu == '14'){}

    return 0;
}