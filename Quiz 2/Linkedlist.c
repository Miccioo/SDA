#include "Linkedlist.h"
#include <stdio.h>

void Quiz2(){
	
	// Soal 1
	address First;
	address P, Q, R, S, temp;
	
	First = Nil;
	
	P = (address)malloc(sizeof(ElmtList));
	info(P) = 7;
	next(P) = First;
	First = P;
	printf("Soal 1: ");
	printf("F.S elemen List = {%d", info(First));
	printf("}");
	
	
	// Soal 2
	Q = (address)malloc(sizeof(ElmtList));
	
	temp = First;
	while(next(temp) != Nil){
		temp = next(temp);
	}
	info(Q) = 11;
	next(Q) = next(temp);
	next(temp) = Q;
	temp = First;
	printf("\nSoal 2: F.S elemen List = {");
	while((next(temp)) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	
	//Soal 3
	R = (address)malloc(sizeof(ElmtList));
	info(R) = 9;
	next(R) = Nil;
	
	int k = 0;
	temp = First;
	int i = 0;
	
	while(i < k){
		temp = next(temp);
		i++;
	}
	next(R) = next(temp);
	next(temp) = R;
	
	temp = First;
	printf("\nSoal 3: F.S elemen List = {");
	while((next(temp)) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	
	// Soal 4
	P = (address)malloc(sizeof(ElmtList));
	info(P) = 5;
	next(P) = First;
	First = P;
	
	temp = First;
	printf("\nSoal 4: F.S elemen List = {");
	while((next(temp)) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));

	
	// Soal 5
	S = (address)malloc(sizeof(ElmtList));
	
	temp = First;
	while(next(temp) != Nil){
		temp = next(temp);
	}
	info(S) = 13;
	next(S) = next(temp);
	next(temp) = S;
	
	temp = First;
	printf("\nSoal 5: F.S elemen List = {");
	while((next(temp)) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	// Soal 6
	temp = First;
	while(next(next(temp))!= Nil){
		temp = next(temp);
	}
	free(next(temp));
	next(temp)= Nil;
	
	temp = First;
	printf("\nSoal 6: F.S elemen List = {");
	while(next(temp) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	// Soal 7
	k = 0;
	i = 0;
	temp = First;
	while(i < k){
		temp = next(temp);
	}
	
	if (temp != Nil && next(temp) != Nil) {
	    address toDelete = next(temp);
	    next(temp) = next(toDelete);
	    free(toDelete);
	}
	
	temp = First;
	printf("\nSoal 7: F.S elemen List = {");
	while(next(temp) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	// Soal 8
	temp = First;
	First = next(First);
	free(temp);
	
	temp = First;
	printf("\nSoal 8: F.S elemen List = {");
	while(next(temp) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
	
	// Soal 9
	temp = First;
	while(temp != Nil){
		if(info(temp) % 2 == 1){
			free(temp);
		}
	}
	
	temp = First;
	printf("\nSoal 8: F.S elemen List = {");
	while(next(temp) != Nil){
		printf("%d, ", info(temp));
		temp = next(temp);
	}
	printf("%d}", info(temp));
}
