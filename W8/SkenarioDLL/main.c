#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char judulBuku[49], namaPeminjam[49];
    int opsi, jumlahStok, levelPrioritas;

    do {
        displayMenu();
        opsi = getPilihan();

        switch (opsi) {
        case 1: { // Tambah Buku
            inputString(judulBuku, sizeof(judulBuku), "Masukkan nama buku: ");
            jumlahStok = inputInt("Masukkan jumlah stok: ");
            insertBuku(judulBuku, jumlahStok);
            break;
        }
        case 2: { // Lihat Semua Buku
            displayAllBuku();
            break;
        }
        case 3: { // Tambah ke Antrean Peminjaman
            inputString(namaPeminjam, sizeof(namaPeminjam), "Masukkan nama peminjam: ");
            inputString(judulBuku, sizeof(judulBuku), "Masukkan nama buku: ");
            do {
                levelPrioritas = inputInt("Pilih prioritas (1:DOSEN, 2:MAHASISWA, 3:UMUM): ");
                if (levelPrioritas < DOSEN || levelPrioritas > UMUM)
                    printf("Prioritas tidak valid! Harus antara 1-3.\n");
            } while (levelPrioritas < DOSEN || levelPrioritas > UMUM);

            Buku *bukuPtr = findBuku(judulBuku);
            if (bukuPtr) {
                initialAntreanPeminjaman(bukuPtr, namaPeminjam, levelPrioritas);
                printf("Peminjam berhasil ditambahkan ke antrean.\n");
            } else {
                printf("Buku tidak ditemukan.\n");
            }
            break;
        }
        case 4: { // Proses Peminjaman
            inputString(judulBuku, sizeof(judulBuku), "Masukkan nama buku: ");
            Buku *bukuPtr = findBuku(judulBuku);
            if (bukuPtr)
                prosesPeminjaman(bukuPtr);
            else
                printf("Buku tidak ditemukan.\n");
            break;
        }
        case 5: { // Batalkan dari Antrean
            inputString(judulBuku, sizeof(judulBuku), "Masukkan nama buku: ");
            inputString(namaPeminjam, sizeof(namaPeminjam), "Masukkan nama peminjam: ");
            Buku *bukuPtr = findBuku(judulBuku);
            if (bukuPtr)
                batalkanAntrean(bukuPtr, namaPeminjam);
            else
                printf("Buku tidak ditemukan.\n");
            break;
        }
        case 6: { // Proses Pengembalian
            inputString(namaPeminjam, sizeof(namaPeminjam), "Masukkan nama peminjam: ");
            inputString(judulBuku, sizeof(judulBuku), "Masukkan nama buku: ");
            Buku *bukuPtr = findBuku(judulBuku);
            if (bukuPtr)
                prosesPengembalian(bukuPtr, namaPeminjam);
            else
                printf("Buku tidak ditemukan.\n");
            break;
        }
        case 7: { // Lihat Peminjaman Aktif
            lihatPeminjamanAktif();
            break;
        }
        case 0:
            printf("Terima kasih telah menggunakan sistem.\n");
            break;
        default:
            printf("Opsi tidak valid! Silakan pilih lagi.\n");
        }

    } while (opsi != 0);

    clearList();
    clearPeminjamanAktif();
    return 0;
}
