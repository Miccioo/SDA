#include "src.h"

void CreateQueue(Queue *Q) {
    Q->front = Nil;
    Q->rear = Nil;
    Q->count = 0;
}

int isEmpty(Queue *Q) {
    return Q->front == Nil;
}

bool isFull(Queue *Q) {
    return Q->count == MAX_SIZE;
}

void EnQueue(Queue *Q, infotype x) {
    if (isFull(Q)) {
        printf("Antrian penuh!\n");
        return;
    }
    address P = Alokasi(x); // Menggunakan fungsi Alokasi dari list1.h
    if (P != Nil) {
        if (isEmpty(Q)) {
            Q->front = P;
        } else {
            Q->rear->next = P;
        }
        Q->rear = P;
        Q->count++;
    }
}

void deQueue(Queue *Q, infotype *x) {
    if (isEmpty(Q)) {
        printf("Antrian kosong!\n");
        return;
    }
    address P = Q->front;
    *x = P->info; // Simpan nilai info elemen yang dihapus
    Q->front = P->next; // Pindahkan front ke elemen berikutnya
    if (Q->front == Nil) {
        Q->rear = Nil; // Jika queue kosong, set rear ke Nil
    }
    DeAlokasi(P); // Dealokasi memori elemen yang dihapus
    Q->count--;
}

void displayQueue(Queue *Q) {
    if (isEmpty(Q)) {
        printf("Antrian kosong!\n");
        return;
    }
    address temp = Q->front;
    printf("Antrian: ");
    while (temp != Nil) {
        printf("%d ", temp->info); // Menggunakan temp->info sesuai definisi di list1.h
        temp = temp->next;
    }
    printf("\n");
}
