#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*Definisi akses komponen type, standard kuliah Algoritma dan pemrograman*/ 
#define info(P) (P)->info 
#define next(P) (P)->next 
#define Nil NULL 
 
/* Element list linier */ 
typedef int infotype; 
typedef struct tElmtlist *address; 
typedef struct tElmtlist { 
 infotype info; 
 address next; 
} ElmtList; 

void Quiz2();

#endif
