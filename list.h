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
    TListAv la;
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

void creatListStudent();
void creatListDisc();
void creatListAv();

int insertStartStudent(listStudent,TElementStudent);
int insertStartDisc(listDisc,TElementDisc);
int insertStartAv(listAv,TElementAv);

int insertEndStudent(listStudent,TElementStudent);
int insertEndDisc(listDisc,TElementDisc);
int insertEndAv(listAv,TElementAv);




#endif