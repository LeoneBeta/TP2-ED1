#ifndef DATAMAINTENANCE_H_INCLUDED
#define DATAMAINTENANCE_H_INCLUDED

void loadFile(FILE *, listStudent);

void newStudent(listStudent);
void newDisc(listStudent);
void newAv(listStudent);

void removeStudent(listStudent);
void removeDisc(listStudent);
void removeAv(listStudent);

void approvedStudents(listStudent);
void failedStudents(listStudent);

void alterNote(listStudent);

void consultRegistration(listStudent);
void consultName(listStudent);


void printList(listStudent);


#endif