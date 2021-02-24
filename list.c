#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/*Funções para Manipulação das 3 diferentes listas, Aluno, Disciplina e Avaliação*/

listStudent creatListStudent(){
    listStudent l = (listStudent)malloc(sizeof(TListSudent));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
        l->current = NULL;
    }
    return l;
}
listDisc creatListDisc(){
    listDisc l = (listDisc)malloc(sizeof(TListDisc));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
        l->current = NULL;
    }
    return l;
}
listAv creatListAv(){
    listAv l = (listAv)malloc(sizeof(TListAv));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
        l->current = NULL;
    }
    return l;
}

int insertStartStudent(listStudent l, TElementStudent e){
    TNodoStudent *n;
    n = (TNodoStudent*)malloc(sizeof(TNodoStudent));
    if(n){
        n->info.id = e.id;
        strcpy(n->info.nome,e.nome);
        strcpy(n->info.birthDate,e.birthDate);
        n->info.ld = creatListDisc();

        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        return 1;
    }else
        return 0;
}
int insertStartDisc(listDisc l,TElementDisc e){
    TNodoDisc *n;
    n = (TNodoDisc*)malloc(sizeof(TNodoDisc));
    if(n){
        strcpy(n->info.nome,e.nome);
        n->info.la = creatListAv();

        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        return 1;
    }else
        return 0;
}
int insertStartAv(listAv l,TElementAv e){
    TNodoAv *n;
    n = (TNodoAv*)malloc(sizeof(TNodoAv));
    if(n){
        strcpy(n->info.nomeAv,e.nomeAv);
        n->info.value = e.value;
        n->info.note = e.note;

        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        return 1;
    }else
        return 0;
}

int insertEndStudent(listStudent l, TElementStudent e){
    TNodoStudent *n;
    if(!l->first)
        return insertStartStudent(l,e);
    n = (TNodoStudent*)malloc(sizeof(TNodoStudent));
    if(n){
        n->info.id = e.id;
        strcpy(n->info.nome,e.nome);
        strcpy(n->info.birthDate,e.birthDate);
        n->info.ld = creatListDisc();

        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        return 1;
    }else
        return 0;
}
int insertEndDisc(listDisc l, TElementDisc e){
    TNodoDisc *n;
    if(!l->first)
        return insertStartDisc(l,e);
    n = (TNodoDisc*)malloc(sizeof(TNodoDisc));
    if(n){
        strcpy(n->info.nome,e.nome);
        n->info.la = creatListAv();

        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        return 1;
    }else
        return 0;
}
int insertEndAv(listAv l, TElementAv e){
    TNodoAv *n;
    if(!l->first)
        return insertStartAv(l,e);
    n = (TNodoAv*)malloc(sizeof(TNodoAv));
    if(n){
        strcpy(n->info.nomeAv,e.nomeAv);
        n->info.value = e.value;
        n->info.note = e.note;

        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        return 1;
    }else
        return 0;
}

int insertPositionStudent(listStudent l, TElementStudent e, int position){
    TNodoStudent *n, *nAux;
    int i;

    if(position == 1)
        return insertStartStudent(l,e);
    else
        if(position == l->size+1)
            return insertEndStudent(l,e);
        else
            if(position < 1 || position > l->size +1)
                return 0;
            else{
                n = (TNodoStudent*)malloc(sizeof(TNodoStudent));
                if(!n)
                    return 0;

                n->info.id = e.id;
                strcpy(n->info.nome,e.nome);
                strcpy(n->info.birthDate,e.birthDate);
                n->info.ld = creatListDisc();

                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                return 1;
            }
}
int insertPositionDisc(listDisc l, TElementDisc e, int position){
    TNodoDisc *n, *nAux;
    int i;

    if(position == 1)
        return insertStartDisc(l,e);
    else
        if(position == l->size+1)
            return insertEndDisc(l,e);
        else
            if(position < 1 || position > l->size +1)
                return 0;
            else{
                n = (TNodoDisc*)malloc(sizeof(TNodoDisc));
                if(!n)
                    return 0;
               
                strcpy(n->info.nome,e.nome);
                n->info.la = creatListAv();
                
                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                return 1;
            }
}
int insertPositionAv(listAv l, TElementAv e, int position){
    TNodoAv *n, *nAux;
    int i;

    if(position == 1)
        return insertStartAv(l,e);
    else
        if(position == l->size+1)
            return insertEndAv(l,e);
        else
            if(position < 1 || position > l->size +1)
                return 0;
            else{
                n = (TNodoAv*)malloc(sizeof(TNodoAv));
                if(!n)
                    return 0;
                
                strcpy(n->info.nomeAv,e.nomeAv);
                n->info.value = e.value;
                n->info.note = e.note;
                
                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                return 1;
            }
}

int removeElementStudent(listStudent l, TMatricula mat){
    TNodoStudent *n;
    n = l->first;
    while(n){
        if(n->info.id == mat){
            if(l->size == 1){
                l->first = NULL;
                l->last = NULL;
            }else
                if(n == l->first){
                    l->first = l->first->next;
                    l->first->prior = NULL;
                }else
                    if(n == l->last){
                        l->last = l->last->prior;
                        l->last->next = NULL;
                    }else{
                        n->prior->next = n->next;
                        n->next->prior = n->prior;
                    }
                    deleteListDisc(n->info.ld);
                    free(n);
                    return 1;
        }else
            n = n->next;
    }
    return 0;
}
int removeElementDisc(listDisc l, char nome[]){
    TNodoDisc *n;
    n = l->first;
    while(n){
        if(strcmp(n->info.nome,nome) == 0){
            if(l->size == 1){
                l->first = NULL;
                l->last = NULL;
            }else
                if(n == l->first){
                    l->first = l->first->next;
                    l->first->prior = NULL;
                }else
                    if(n == l->last){
                        l->last = l->last->prior;
                        l->last->next = NULL;
                    }else{
                        n->prior->next = n->next;
                        n->next->prior = n->prior;
                    }
                    deleteListAv(n->info.la);
                    free(n);
                    return 1;
        }else
            n = n->next;
    }
    return 0;
}
int removeElementAv(listAv l, char nomeAv[]){
    TNodoAv *n;
    n = l->first;
    while(n){
        if(strcmp(n->info.nomeAv,nomeAv)){
            if(l->size == 1){
                l->first = NULL;
                l->last = NULL;
            }else
                if(n == l->first){
                    l->first = l->first->next;
                    l->first->prior = NULL;
                }else
                    if(n == l->last){
                        l->last = l->last->prior;
                        l->last->next = NULL;
                    }else{
                        n->prior->next = n->next;
                        n->next->prior = n->prior;
                    }
                    free(n);
                    return 1;
        }else
            n = n->next;
    }
    return 0;
}

int deleteListStudent(listStudent l){
    TNodoStudent *n;
    while(l->first){
        n = l->first;
        l->first = l->first->next;
        deleteListDisc(n->info.ld);
        free(n);
    }
    free(l);
}
int deleteListDisc(listDisc l){
    TNodoDisc *n;
    while(l->first){
        n = l->first;
        l->first = l->first->next;
        deleteListAv(n->info.la);
        free(n);
    }
    free(l);
}
int deleteListAv(listAv l){
    TNodoAv *n;
    while(l->first){
        n = l->first;
        l->first = l->first->next;
        free(n);
    }
    free(l);
}

int getElementStudent(listStudent l, TElementStudent *e, int position){
    int i;
    TNodoStudent *n;
    if(position < 1 || position > l->size)
        return 0;
    if(position <= l->size/2){
        for(i=1;i<position;i++)
            n = n->next;
        *e = n->info;
        return 1;
    }else{
        for(i=l->size;i>position;i--)
            n = n->prior;
        *e = n->info;
        return 1;
    }
    return 0;
}
int getElementDisc(listDisc l, TElementDisc *e, char nomeDisc[]){
    int i;
    TNodoDisc *n;

    for(i=0;i<l->size;i++){
        for(i=0;i<l->size;i++)
        if(strcmp(nomeDisc,l->current->info.nome) == 0){
            *e = n->info;
            return 1;
        }else
            l->current = l->current->next;
    }
    return 0;
}
int getElementAv(listAv l, TElementAv *e, char nomeAv[]){
    int i;
    TNodoAv *n;
    for(i=0;i<l->size;i++){
        for(i=0;i<l->size;i++)
        if(strcmp(nomeAv,l->current->info.nomeAv) == 0){
            *e = n->info;
            return 1;
        }else
            l->current = l->current->next;
    }
    return 0;
}

int emptyListStudent(listStudent l){
    return l->first == NULL;
}
int emptyListDisc(listDisc l){
    return l->first == NULL;
}
int emptyListAv(listAv l){
    return l->first == NULL;
}

int fullListStudent(listStudent l){
    TNodoStudent *n;
    n = (TNodoStudent*)malloc(sizeof(TNodoStudent));
    if(n){
        free(n);
        return 0;
    }else 
        return 1;
}
int fullListDisc(listDisc l){
    TNodoDisc *n;
    n = (TNodoDisc*)malloc(sizeof(TNodoDisc));
    if(n){
        free(n);
        return 0;
    }else 
        return 1;
}
int fullListAv(listAv l){
    TNodoAv *n;
    n = (TNodoAv*)malloc(sizeof(TNodoAv));
    if(n){
        free(n);
        return 0;
    }else 
        return 1;
}

int getSizeStudent(listStudent l){
    return l->size;
}
int getSizeDisc(listDisc l){
    return l->size;
}
int getSizeAv(listAv l){
    return l->size;
}

int setCurrentStudent(listStudent l, int position){
    int i;
    if(position < 1 | position > l->size)
        return 0;
    if(position < l->size/2){
        l->current = l->first;
        for(i=1;i<position;i++){
            l->current = l->current->next;
            if(l->current->info.id == position)
                return 1;
        }
    }else{
        l->current = l->last;
        for(i=l->size;i>position;i--){
            l->current = l->current->prior;
            if(l->current->info.id == position)
                return 1;
        }
    }
    return 0;
}
int setCurrentDisc(listDisc l, char string[]){
    int i;
    l->current = l->first;

    for(i=0;i<l->size;i++)
        if(strcmp(string,l->current->info.nome) == 0)
            return 1;
        else
            l->current = l->current->next;
    return 0;
    
}
int setCurrentAv(listAv l, char string[]){
    int i;
    l->current = l->first;

    for(i=0;i<l->size;i++)
        if(strcmp(string,l->current->info.nomeAv) == 0)
            return 1;
        else
            l->current = l->current->next;
    return 0;
}



