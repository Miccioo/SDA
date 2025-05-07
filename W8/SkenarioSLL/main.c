#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main()
{
    char namaBuku[50], namaOrang[50];
    int pilihan = 0, stock, prioritas;
    Buku *bukuDipinjam;
    Buku *bukuProsesPinjam;
    Buku *bukuBatalkan;
    Buku *bukuDikembalikan;

    do
    {
        displayMenu();
        pilihan = getPilihan();

        switch (pilihan)
        {
        case 1:
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            stock = inputInt("Masukkan jumlah stock: ");
            insertBuku(namaBuku, stock);
            printf("Berhasil Menambahkan Buku\n");
            break;

        case 2:
            displayAllBukuAndAntrean();
            break;

        case 3:
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");

            do {
                prioritas = inputInt("Pilih prioritas (1:DOSEN, 2:MAHASISWA, 3:UMUM): ");
                if (prioritas < DOSEN || prioritas > UMUM) {
                    printf("Prioritas tidak valid! Masukkan angka 1, 2, atau 3.\n");
                }
            } while (prioritas < DOSEN || prioritas > UMUM);

            bukuDipinjam = findBuku(namaBuku);
            if (bukuDipinjam != NULL) {
                initialAntreanPeminjaman(bukuDipinjam, namaOrang, prioritas);
                printf("Berhasil mendaftar antrian peminjaman\n");
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;

        case 4:
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            bukuProsesPinjam = findBuku(namaBuku);
            if (bukuProsesPinjam != NULL) {
                prosesPeminjaman(bukuProsesPinjam);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;

        case 5:
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            bukuBatalkan = findBuku(namaBuku);
            if (bukuBatalkan != NULL) {
                batalkanAntrean(bukuBatalkan, namaOrang);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;

        case 6:
            inputString(namaOrang, sizeof(namaOrang), "Masukkan nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Masukkan nama buku: ");
            bukuDikembalikan = findBuku(namaBuku);
            if (bukuDikembalikan != NULL) {
                prosesPengembalian(bukuDikembalikan, namaOrang);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;

        case 7:
            lihatPeminjamanAktif();
            break;

        case 0:
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);

    clearListBuku();
    clearPeminjamanAktif();
    return 0;
}

