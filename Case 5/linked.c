#include <limits.h>
#include <stdlib.h>
#include "linked.h"

boolean ListEmpty(List L)
/* Mengirim true jika List Kosong */
{
    return (First(L) == Nil);
}

void CreateList(List *L)
/* IS : L sembarang */
/* FS : Terbentuk List Kosong */
{
    First(*L) = Nil;
}

address Alokasi(infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address != Nil, */
/* dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) /* Alokasi berhasil */
    {
        Info(P) = X;
        Next(P) = Nil;
    }
    return (P);
}

void DeAlokasi(address P)
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */
{
    if (P != Nil)
    {
        free(P);
    }
}

address Search(List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen tsb. */
/* Jika tidak ada, mengirimkan Nil */
/* Menggunakan variabel bertype boolean */
{
    /* Kamus Lokal */
    address P;
    boolean found = false;
    /* algoritma */
    P = First(L);
    while ((P != Nil) && (!found))
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            P = Next(P);
        }
    } /* P = Nil atau Ketemu */
    return (P);
}

void InsVFirst(List *L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    /* Kamus Lokal */
    address P;
    /* Aloritma */
    P = Alokasi(X);
    if (P != Nil)
    {
        InsertFirst(&(*L), P);
    }
}

void InsVLast(List *L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = Alokasi(X);
    if (P != Nil)
    {
        InsertLast(&(*L), P);
    }
}

void DelVFirst(List *L, infotype *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* dan alamat elemen pertama di dealokasi */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = First(*L);
    *X = Info(P);
    First(*L) = Next(First(*L));
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen terakhir list dihapus : nilai info disimpan pada X */
/* dan alamat elemen terakhir di dealokasi */
{
    /* Kamus Lokal */
    address PDel;
    /* Algoritma */
    PDel = First(*L);
    DelLast(&(*L), &PDel);
    (*X) = Info(PDel);
    DeAlokasi(PDel);
}

void InsertFirst(List *L, address P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-address P sebagai elemen pertama */
{
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter(List *L, address P, address Prec)
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/* P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast(List *L, address P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */
{
    /* Kamus Lokal */
    address Last;
    /* Algoritma */
    if (First(*L) != Nil)
    {
        Last = First(*L);
        while (Next(Last) != Nil)
        {
            Last = Next(Last);
        }
        Next(Last) = P;
    }
    else
    {
        First(*L) = P;
    }
}

void DelFirst(List *L, address *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/* elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama */

{
    *P = First(*L);
    First(*L) = Next(First(*L));
}

void DelP(List *L, infotype X)
/* IS : L sembarang */
/* FS : Jika ada elemen list beraddress P, dengan Info(P) = X */
/* Maka P dihapus dari list dan di dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    /* Kamus Lokal */
    address P, Prec;
    boolean found = false;
    /* Algoritma */
    Prec = Nil;
    P = First(*L);
    while ((P != Nil) && (!found))
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            Prec = P;
            P = Next(P);
        }
    } /* P = Nil Atau Ketemu */
    if (found)
    {
        if (Prec == Nil && Next(P) == Nil) /* Hanya 1 elemen */
        {
            First(*L) = Nil;
        }
        else if (Prec == Nil) /* Ketemu di elemen 1*/
        {
            First(*L) = Next(P);
        }
        else /* Ketemu di elemen list yang ditengah/akhir */
        {
            Next(Prec) = Next(P);
        }
        Next(P) = Nil;
        DeAlokasi(P);
    }
}

void DelLast(List *L, address *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last elemen baru adalah predesessor elemen terakhir yang lama, jika ada */
{
    /* Kamus Lokal */
    address Prec;
    /* Algoritma */
    *P = First(*L);
    Prec = Nil;
    while (Next(*P) != Nil)
    {
        Prec = *P;
        *P = Next(*P);
    }
    if (Prec == Nil) /* Hanya 1 elemen */
    {
        First(*L) = Nil;
    }

    else /* List Lebih dari 1 elemen */
    {
        Next(Prec) = Nil;
    }
}

void DelAfter(List *L, address *Pdel, address Prec)
/* IS : L TIDAK Kosong, Prec adalah anggota List */
/* FS : menghapus Next(Prec): Pdel adalah alamat elemen list yang dihapus */
{
    *Pdel = Next(Prec);
    if (Pdel != Nil)
    {
        Next(Prec) = Next(*Pdel);
        Next(*Pdel) = Nil;
    }
}

void PrintInfo(List L)
/* IS : L mungkin kosong */
/* FS : Jika List tidak kosong, semua info yang disimpan pada elemen list */
/* diprint. Jika list kosong, hanya menuliskan "List Kosong" */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    if (First(L) == Nil)
    {
        printf("List Kosong .... \a\n");
    }
    else /* List memiliki elemen */
    {
        P = First(L);
        for (;;)
        {
            if (P == Nil)
            {
                printf("\n");
                break;
            }
            else /* Belum berada di akhir List */
            {
                printf("%d ", Info(P));
                P = Next(P);
            }
        }
    }
}
