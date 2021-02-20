#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//Lista para armazenar os alunos
typedef int TMatricula;
typedef struct{
    TMatricula id;
    char nome[100];
    char birthDate[11];
    TListDisc *ld;
}TElementStudent;

typedef struct NodoStudent{
    TElementStudent info;
    struct NodoStudent *prior, *next;
}TNodoStudent;

typedef struct{
    TNodoStudent *first, *last;
    int size;
}TListSudent;
typedef TListSudent *listStudent;


//Lista para armazenar as disciplinas
typedef struct{
    char nome[20];
    int value;
    int note;
    TListAv *la;
}TElementDisc;

typedef struct NodoDisc{
    TElementDisc info;
    struct NodoDisc *prior, *next;
}TNodoDisc;

typedef struct{
    TNodoDisc *first, *last;
    int size;
}TListDisc;
typedef TListDisc *listDisc;


//Lista para armazenar as avaliações
typedef struct{
    int idAv;
}TElementAv;

typedef struct NodoAv{
    TElementAv info;
    struct NodoDisc *prior, *next;
}TNodoAv;

typedef struct{
    TNodoAv *first, *last;
    int size;
}TListAv;
typedef TListAv *listAv;

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
int removeElementAv(listAv,TElementStudent *,int);

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