#include "list1.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean ListEmpty(List L)
/* Mengirim true jika list kosong */
{
    return (L.First == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *L)
/* I.S. sembarang */
/* F.S. Terbentuk list kosong */
{
    L->First = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi(infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        P->nilai = X;
        P->next = Nil;
    }
    return P;
}

void DeAlokasi(address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search(List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    address P = L.First;
    while (P != Nil) {
        // For comparing infoItem structures, we should compare by item name
        if (strcmp(P->nilai.item.name, X.item.name) == 0) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

boolean FSearch(List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    address Pcek = L.First;
    boolean Found = false;
    while ((Pcek != Nil) && (!Found)) {
        if (Pcek == P) {
            Found = true;
        } else {
            Pcek = Pcek->next;
        }
    }
    return Found;
}

address SearchPrec(List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya = X */
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen sebelum elemen tersebut. */
/* Jika X adalah elemen pertama, mengirimkan Nil */
/* Jika tidak ada elemen list dengan Info(P) = X, mengirimkan Nil */
{
    address P;
    
    // Check if list is empty or if X is first element
    if (ListEmpty(L) || strcmp(L.First->nilai.item.name, X.item.name) == 0) {
        return Nil;
    }
    
    P = L.First;
    while (P->next != Nil) {
        if (strcmp(P->next->nilai.item.name, X.item.name) == 0) {
            return P;
        }
        P = P->next;
    }
    
    return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst(List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address P = Alokasi(X);
    if (P != Nil) {
        InsertFirst(L, P);
    }
}

void InsVLast(List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P = Alokasi(X);
    if (P != Nil) {
        InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst(List *L, infotype *X)
/* I.S. List L tidak kosong */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/* dan alamat elemen pertama di-dealokasi */
{
    address P;
    DelFirst(L, &P);
    *X = P->nilai;
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/* dan alamat elemen terakhir di-dealokasi */
{
    address P;
    DelLast(L, &P);
    *X = P->nilai;
    DeAlokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst(List *L, address P)
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    P->next = L->First;
    L->First = P;
}

void InsertAfter(List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/* P sudah dialokasi */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    P->next = Prec->next;
    Prec->next = P;
}

void InsertLast(List *L, address P)
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (ListEmpty(*L)) {
        InsertFirst(L, P);
    } else {
        address Last = L->First;
        while (Last->next != Nil) {
            Last = Last->next;
        }
        InsertAfter(L, P, Last);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst(List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = L->First;
    L->First = L->First->next;
}

void DelP(List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P) = X */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    address P, Prec;
    
    // Check if element is the first element
    if (!ListEmpty(*L)) {
        if (strcmp(L->First->nilai.item.name, X.item.name) == 0) {
            DelFirst(L, &P);
            DeAlokasi(P);
        } else {
            Prec = SearchPrec(*L, X);
            if (Prec != Nil) {
                DelAfter(L, &P, Prec);
                DeAlokasi(P);
            }
        }
    }
}

void DelLast(List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
    address Last, PrecLast;
    
    Last = L->First;
    PrecLast = Nil;
    
    while (Last->next != Nil) {
        PrecLast = Last;
        Last = Last->next;
    }
    
    *P = Last;
    
    if (PrecLast == Nil) {
        // List only has one element
        L->First = Nil;
    } else {
        PrecLast->next = Nil;
    }
}

void DelAfter(List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list */
/* F.S. Menghapus Next(Prec): */
/* Pdel adalah alamat elemen list yang dihapus */
{
    *Pdel = Prec->next;
    if (*Pdel != Nil) {
        Prec->next = (*Pdel)->next;
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo(List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, */
/* Semua info yg disimpan pada elemen list diprint */
/* Jika list kosong, hanya menuliskan "list kosong" */
{
    address P;
    
    if (ListEmpty(L)) {
        printf("Inventory kosong\n");
    } else {
        P = L.First;
        int i = 1;
        while (P != Nil) {
            printf("%d. %s x%d ", i, P->nilai.item.name, P->nilai.quantity);
            
            // Add additional info based on item type
            if (P->nilai.item.type == 0) {
                printf("(Heal +%d)", P->nilai.item.status);
            } else if (P->nilai.item.type == 1) {
                printf("(Attack +%d)", P->nilai.item.status);
            } else if (P->nilai.item.type == 2) {
                printf("(Defense +%d)", P->nilai.item.status);
            }
            
            printf("\n");
            P = P->next;
            i++;
        }
    }
}

int NbElmt(List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    address P;
    int count = 0;
    
    P = L.First;
    while (P != Nil) {
        count++;
        P = P->next;
    }
    
    return count;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max(List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    // For infoItem, let's define max as item with highest status value
    address P = L.First;
    infotype max = P->nilai;
    
    P = P->next;
    while (P != Nil) {
        if (P->nilai.item.status > max.item.status) {
            max = P->nilai;
        }
        P = P->next;
    }
    
    return max;
}

address AdrMax(List L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
    // For infoItem, find address with highest status value
    address P = L.First;
    address maxAddr = P;
    int maxStatus = P->nilai.item.status;
    
    P = P->next;
    while (P != Nil) {
        if (P->nilai.item.status > maxStatus) {
            maxStatus = P->nilai.item.status;
            maxAddr = P;
        }
        P = P->next;
    }
    
    return maxAddr;
}

infotype Min(List L)
/* Mengirimkan nilai Info(P) yang minimum */
{
    // For infoItem, let's define min as item with lowest status value
    address P = L.First;
    infotype min = P->nilai;
    
    P = P->next;
    while (P != Nil) {
        if (P->nilai.item.status < min.item.status) {
            min = P->nilai;
        }
        P = P->next;
    }
    
    return min;
}

address AdrMin(List L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
    // For infoItem, find address with lowest status value
    address P = L.First;
    address minAddr = P;
    int minStatus = P->nilai.item.status;
    
    P = P->next;
    while (P != Nil) {
        if (P->nilai.item.status < minStatus) {
            minStatus = P->nilai.item.status;
            minAddr = P;
        }
        P = P->next;
    }
    
    return minAddr;
}

infotype Average(List L)
/* Mengirimkan nilai rata-rata Info(P) */
{
    // For infoItem, calculate average based on status
    address P = L.First;
    int sum = 0;
    int count = 0;
    
    while (P != Nil) {
        sum += P->nilai.item.status;
        count++;
        P = P->next;
    }
    
    // Create a dummy infotype with the average
    infotype avg;
    strcpy(avg.item.name, "Average");
    avg.item.status = (count > 0) ? sum / count : 0;
    avg.quantity = 1;
    
    return avg;
}
