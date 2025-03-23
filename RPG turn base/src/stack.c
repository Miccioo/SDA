#include "list1.h"
#include "stack.h"

void CreateStack(Stack *L){
	CreateList(&(L->Top));
}

void push(Stack *L, infotype data){
	InsVFirst(&L->Top, data);
}

int pop(Stack *L){
	infotype data;
	DelVFirst(&(L->Top), &data);	// Menggunakan DelVFirst dikarenakan kita tidak perlu menginvers hasil binarynya lagi.
	return data;
}

void Binary(Stack *L, infotype data){
	while(data != 0){
		push(L, data % 2);
		data = data / 2;
	}
}

int isEmpty(Stack *L){
	return ListEmpty(L->Top);
}

void display(Stack L){
	while(!isEmpty(&L)){
		printf("%d", pop(&L));
	}
}


