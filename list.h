#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct{  //Elemento Avaliação
    char nomeAv[20];
    int value;
    int note;
}TElementAv;

typedef struct NodoAv{  //Nodo Avaliação
    TElementAv info;
    struct NodoAv *prior, *next;
}TNodoAv;

typedef struct{  //Lista Avaliação
    TNodoAv *first, *last;
    int size;
}TListAv;


typedef struct{  //Elemento Disciplina
    char nome[20];
    TListAv *la;
}TElementDisc;

typedef struct NodoDisc{  //Nodo Disciplina
    TElementDisc info;
    struct NodoDisc *prior, *next;
}TNodoDisc;

typedef struct{  //Lista Disciplina
    TNodoDisc *first, *last;
    int size;
}TListDisc;


typedef int TMatricula;
typedef struct{ //Elemento Aluno
    TMatricula id;
    char nome[100];
    char birthDate[11];
    TListDisc *ld;
}TElementStudent;

typedef struct NodoStudent{  //Nodo Alunos
    TElementStudent info;
    struct NodoStudent *prior, *next;
}TNodoStudent;

typedef struct{  //Lista Aluno
    TNodoStudent *first, *last;
    int size;
}TListSudent;

//Ponteiro para tipo struct
typedef TListAv *listAv;
typedef TListDisc *listDisc;
typedef TListSudent *listStudent;

listStudent creatListStudent();
listDisc creatListDisc();
listAv creatListAv();

int insertStartStudent(listStudent,TElementStudent);
int insertStartDisc(listDisc,TElementDisc);
int insertStartAv(listAv,TElementAv);

int insertEndStudent(listStudent,TElementStudent);
int insertEndDisc(listDisc,TElementDisc);
int insertEndAv(listAv,TElementAv);

int insertPositionStudent(listStudent,TElementStudent,int);
int insertPositionDisc(listDisc,TElementDisc,int);
int insertPositionAv(listAv,TElementAv,int);

int removeElementStudent(listStudent,TElementStudent *,TMatricula);
int removeElementDisc(listDisc,TElementDisc *,char []);
int removeElementAv(listAv,TElementAv *,char []);

int deleteListStudent(listStudent);
int deleteListDisc(listDisc);
int deleteListAv(listAv);

int getElementStudent(listStudent,TElementStudent *,int);
int getElementDisc(listDisc,TElementDisc *,int);
int getElementAv(listAv,TElementAv *,int);

int emptyListStudent(listStudent );
int emptyListDisc(listDisc);
int emptyListAv(listAv );

int fullListStudent(listStudent);
int fullListDisc(listDisc);
int fullListAv(listAv);

int getSizeStudent(listStudent);
int getSizeDisc(listDisc);
int getSizeAv(listAv);


#endif