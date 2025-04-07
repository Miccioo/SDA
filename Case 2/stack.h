#ifndef STACK_H
#define STACK_H

#include "list1.h"
#include "boolean.h"
#include <stdio.h>

typedef struct {
	List Top;
} Stack;

void createStack(Stack *L);

int isEmpty(Stack *L);
void push(Stack *L, infotype data);
int pop(Stack *L);
void Binary(Stack *L, infotype data);
void display(Stack L);

#endif
