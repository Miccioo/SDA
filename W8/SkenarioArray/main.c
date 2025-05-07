#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char namaBuku[49], namaPeminjam[49];
    int pilihan = 0, jumlahStok, levelPrioritas;

    do
    {
        displayMenu();
        pilihan = getPilihan();

        switch (pilihan)
        {
        case 1: // Tambah Buku
            inputString(namaBuku, sizeof(namaBuku), "Judul buku: ");
            jumlahStok = inputInt("Jumlah stok: ");
            insertBuku(namaBuku, jumlahStok);
            printf("Buku berhasil ditambahkan\n");
            break;

        case 2: // Lihat Buku dan Antrean
            tampilkanSeluruhBukuDanAntrean();
            break;

        case 3: // Daftar Peminjam
            inputString(namaPeminjam, sizeof(namaPeminjam), "Nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Judul buku yang ingin dipinjam: ");

            do {
                levelPrioritas = inputInt("Prioritas (1:DOSEN, 2:MAHASISWA, 3:UMUM): ");
                if (levelPrioritas < DOSEN || levelPrioritas > UMUM) {
                    printf("Prioritas tidak dikenali. Coba lagi.\n");
                }
            } while (levelPrioritas < DOSEN || levelPrioritas > UMUM);

            Buku* targetBuku = findBuku(namaBuku);
            if (targetBuku != NULL) {
                tambahAntreanPeminjam(targetBuku, namaPeminjam, levelPrioritas);
                printf("Pendaftaran antrean berhasil!\n");
            } else {
                printf("Buku tidak ditemukan.\n");
            }
            break;

        case 4: // Proses Peminjaman
            inputString(namaBuku, sizeof(namaBuku), "Judul buku: ");
            Buku* bukuUntukDiproses = findBuku(namaBuku);
            if (bukuUntukDiproses != NULL) {
                jalankanPeminjaman(bukuUntukDiproses);
            } else {
                printf("Buku tidak ditemukan.\n");
            }
            break;

        case 5: // Batalkan antrean
            inputString(namaBuku, sizeof(namaBuku), "Judul buku: ");
            inputString(namaPeminjam, sizeof(namaPeminjam), "Nama peminjam: ");

            Buku* bukuAntrean = findBuku(namaBuku);
            if (bukuAntrean != NULL) {
                hapusAntreanPeminjam(bukuAntrean, namaPeminjam);
            } else {
                printf("Buku tidak ditemukan.\n");
            }
            break;

        case 6: // Kembalikan Buku
            inputString(namaPeminjam, sizeof(namaPeminjam), "Nama peminjam: ");
            inputString(namaBuku, sizeof(namaBuku), "Judul buku: ");

            Buku* bukuKembali = findBuku(namaBuku);
            if (bukuKembali != NULL) {
                kembalikanBuku(bukuKembali, namaPeminjam);
            } else {
                printf("Buku tidak ditemukan.\n");
            }
            break;

        case 7: // Daftar Peminjaman Aktif
            tampilkanPeminjamanAktif();
            break;

        case 0: // Keluar
            printf("Program selesai. Terima kasih.\n");
            break;

        default:
            printf("Pilihan tidak dikenal. Silakan coba lagi.\n");
        }

    } while (pilihan != 0);

    clearListBuku();
    hapusSeluruhPeminjamanAktif();
    return 0;
}
