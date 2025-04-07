#include <stdio.h>
#include <stdlib.h>
#include "src.h"
#include "Display.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void tampilkanMenu()
{
    printf("\n=== SISTEM ANTRIAN BANK ===\n");
    printf("1. Ambil Antrian\n");
    printf("2. Proses Antrian\n");
    printf("3. Cetak Antrian\n");
    printf("4. Keluar\n");
    printf("Pilih Opsi: ");
}

int main() {
    int jml_teller, pilihan, teller, nomorAntrian[MAX_TELLER] = {0}, nomor;
    Queue antrian[MAX_TELLER];
    
    printf("Masukkan jumlah teller (max %d): ", MAX_TELLER);
    scanf("%d", &jml_teller);

    if (jml_teller > MAX_TELLER) {
        printf("Jumlah teller maksimal adalah %d. Menggunakan %d teller.\n", MAX_TELLER, MAX_TELLER);
        jml_teller = MAX_TELLER;
    } else if (jml_teller < 1) {
        printf("Jumlah teller minimal adalah 1. Menggunakan 1 teller.\n");
        jml_teller = 1;
    }
    
    for (int i = 0; i < jml_teller; i++) {
        CreateQueue(&antrian[i]);
    }
    
    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        
        switch (pilihan) {
        case 1: // Ambil Antrian
            printf("Pilih teller (1-%d): ", jml_teller);
            scanf("%d", &teller);
            if (teller < 1 || teller > jml_teller) {
                printf("Teller tidak valid!\n");
                break;
            }
            teller--; // Konversi ke indeks array
            if (!isFull(&antrian[teller])) {
                nomorAntrian[teller]++;
                EnQueue(&antrian[teller], nomorAntrian[teller]);
                printf("\nAnda mendapat nomor antrian: %d di Teller %d\n", nomorAntrian[teller], teller + 1);
            }
            break;
        
        case 2: // Proses Antrian
            printf("Pilih teller yang akan memproses (1-%d): ", jml_teller);
            scanf("%d", &teller);
            if (teller < 1 || teller > jml_teller) {
                printf("Teller tidak valid!\n");
                break;
            }
            teller--; // Konversi ke indeks array
            deQueue(&antrian[teller], &nomor);
            if (nomor != -1) {
                printf("\nMemproses nomor antrian: %d di Teller %d\n", nomor, teller + 1);
            }
            break;
        
        case 3: // Cetak Antrian
            for (int i = 0; i < jml_teller; i++) {
                printf("\nAntrian Teller %d: ", i + 1);
                displayQueue(&antrian[i]);
            }
            break;
        
        case 4: // Keluar
            printf("\nTerima kasih telah menggunakan sistem antrian bank.\n");
            break;
        
        default:
            printf("\nPilihan tidak valid!\n");
        }
    } while (pilihan != 4);
    
    return 0;
}
