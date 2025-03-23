#include "queue.h"

void CreateQueue(Queue *Q) {
    Q->front = Nil;
    Q->rear = Nil;
    Q->count = 0;
}

int isEmptyQueue(Queue *Q) {
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
    
    // Create a new node using the list's Alokasi function
    address P = Alokasi(x);
    
    if (P != Nil) {
        // Set next to Nil since it will be the last node
        P->next = Nil;
        
        if (isEmptyQueue(Q)) {
            Q->front = P;
        } else {
            Q->rear->next = P;
        }
        
        Q->rear = P;
        Q->count++;
    } else {
        printf("Alokasi memori gagal!\n");
    }
}

void deQueue(Queue *Q, infotype *x) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong!\n");
        return;
    }
    
    address P = Q->front;
    *x = P->nilai; // Save the value of the deleted element
    
    Q->front = P->next; // Move the front to the next element
    
    if (Q->front == Nil) {
        Q->rear = Nil; // If queue becomes empty, set rear to Nil
    }
    
    DeAlokasi(P); // Free the memory of the deleted element
    Q->count--;
}

void displayQueue(Queue *Q) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong!\n");
        return;
    }
    
    address temp = Q->front;
    printf("Antrian: \n");
    int i = 1;
    
    while (temp != Nil) {
        printf("%d. %s (Turn)\n", i, temp->nilai.item.name);
        temp = temp->next;
        i++;
    }
    printf("\n");
}
