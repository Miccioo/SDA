#ifndef SRC_H
#define SRC_H

/*Definisi akses komponen type, standard kuliah Algoritma dan pemrograman*/ 
#define info(P) (P)->info 
#define next(P) (P)->next 
#define nama(P) (P)->info.nama
#define nilai(P) (P)->info.nilai
#define Nil NULL
#define MAXCHAR 30

typedef int infotype; 

typedef struct {
	char nama[MAXCHAR];
	infotype nilai;
} mahasiswa;

typedef struct tElmtlist *address; 
typedef struct tElmtlist { 
 mahasiswa info; 
 address next; 
} ElmtList; 

typedef struct {
	address First;
	address Last;
} List;

// Konstraktor
void createList(List *First);
address createNode(char nama[], infotype nilaiUTS);
address insertSort(address *list, char nama[], infotype nilaiUTS);

// Destructor
void deleteList(List *L);


// Validator
int isEmpty(address list);

// Getter dan Setter
char* getNama(address list);
infotype getNilaiUTS(address list);
void setMahasiswa(address list, char nama[], infotype nilaiUTS);

// Tampilkan objek
void printObject(address list);
void printObjectByNilai(address list);

// Lainnya
void DescendingByNilai(address list);
int countElements(List L);
void removeDuplicates(List *L);

#endif
