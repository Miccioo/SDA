#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list1.h" // Include list1.h which has our infotype definition

#define Nil NULL
#define MAX_SIZE 100

/* Queue Definition */
typedef struct {
    address front; // Pointer to front queue element
    address rear;  // Pointer to back queue element
    int count;     // Number of elements in queue
} Queue;

// Function to create an empty queue
void CreateQueue(Queue *Q);

// Function to check if queue is empty
int isEmptyQueue(Queue *Q);

// Function to check if queue is full
bool isFull(Queue *Q);

// Function to add element to queue
void EnQueue(Queue *Q, infotype x);

// Function to remove element from queue
void deQueue(Queue *Q, infotype *x);

// Function to display queue contents
void displayQueue(Queue *Q);

#endif
