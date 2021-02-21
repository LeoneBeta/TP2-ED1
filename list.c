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
    }
    return l;
}
listDisc creatListDisc(){
    listDisc l = (listDisc)malloc(sizeof(TListDisc));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
    }
    return l;
}
listAv creatListAv(){
    listAv l = (listAv)malloc(sizeof(TListAv));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
    }
    return l;
}

int insertStartStudent(listStudent l, TElementStudent e){
    TNodoStudent *n;
    n = (TNodoStudent*)malloc(sizeof(TNodoStudent));
    if(n){
        n->info = e;
        n->next = l->first;
        n->prior = NULL;
        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        creatListDisc(n->ld);
        return 1;
    }else
        return 0;
}
int insertStartDisc(listDisc l,TElementDisc e){
    TNodoDisc *n;
    n = (TNodoDisc*)malloc(sizeof(TNodoDisc));
    if(n){
        n->info = e;
        n->next = l->first;
        n->prior = NULL;
        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        creatListAv(n->la);
        return 1;
    }else
        return 0;
}
int insertStartAv(listAv l,TElementAv e){
    TNodoAv *n;
    n = (TNodoAv*)malloc(sizeof(TNodoAv));
    if(n){
        n->info = e;
        n->next = l->first;
        n->prior = NULL;
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
        n->info = e;
        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        creatListDisc(n->ld);
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
        n->info = e;
        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        creatListAv(n->la);
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
        n->info = e;
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
                n->info = e;
                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                creatListDisc(n->ld);
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
                n->info = e;
                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                creatListAv(n->la);
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
                n->info = e;
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

int removeElementStudent(listStudent l,TElementStudent *e, TMatricula mat){
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
                    *e = n->info;
                    //deleteListDisc(n->ld);
                    free(n);
                    return 1;
        }else
            n = n->next;
    }
    return 0;
}
int removeElementDisc(listDisc l,TElementDisc *e, char nome[]){
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
                    *e = n->info;
                    //deleteListAv(n->la);
                    free(n);
                    return 1;
        }else
            n = n->next;
    }
    return 0;
}
int removeElementAv(listAv l,TElementAv *e, char nomeAv[]){
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
                    *e = n->info;
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
        //deleteListDisc(n->ld);
        free(n);
    }
    free(l);
}
int deleteListDisc(listDisc l){
    TNodoDisc *n;
    while(l->first){
        n = l->first;
        l->first = l->first->next;
        //deleteListAv(n->la);
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
    }else{
        for(i=l->size;i>position;i--)
            n = n->prior;
        *e = n->info;
    }
    return 1;
}
int getElementDisc(listDisc l, TElementDisc *e, int position){
    int i;
    TNodoDisc *n;
    if(position < 1 || position > l->size)
        return 0;
    if(position <= l->size/2){
        for(i=1;i<position;i++)
            n = n->next;
        *e = n->info;
    }else{
        for(i=l->size;i>position;i--)
            n = n->prior;
        *e = n->info;
    }
    return 1;
}
int getElementAv(listAv l, TElementAv *e, int position){
    int i;
    TNodoAv *n;
    if(position < 1 || position > l->size)
        return 0;
    if(position <= l->size/2){
        for(i=1;i<position;i++)
            n = n->next;
        *e = n->info;
    }else{
        for(i=l->size;i>position;i--)
            n = n->prior;
        *e = n->info;
    }
    return 1;
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






