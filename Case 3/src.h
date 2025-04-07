#ifndef SRC_H
#define SRC_H
#include "list1.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list1.h" // Menyertakan file header list1.h

#define Nil NULL
#define MAX_SIZE 100

/* Definisi Queue */
typedef struct {
    address front; // Pointer ke elemen depan queue
    address rear;  // Pointer ke elemen belakang queue
    int count;     // Jumlah elemen dalam queue
} Queue;

// Fungsi untuk membuat queue kosong
void CreateQueue(Queue *Q);

// Fungsi untuk mengecek apakah queue kosong
int isEmpty(Queue *Q);

// Fungsi untuk mengecek apakah queue penuh
bool isFull(Queue *Q);

// Fungsi untuk menambahkan elemen ke dalam queue
void EnQueue(Queue *Q, infotype x);

// Fungsi untuk menghapus elemen dari queue
void deQueue(Queue *Q, infotype *x);

// Fungsi untuk menampilkan isi queue
void displayQueue(Queue *Q);

#endif
