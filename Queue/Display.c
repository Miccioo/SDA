#include "Display.h"

void displayMenu(){
	banner();
	printf("1. Play\n");
	printf("2. Setting\n");
	printf("3. Exit");
}

void banner(){
	printf("===================\n");
	printf("|                  |\n");
	printf("|  BANK SIMULATOR  |\n");
	printf("|                  |\n");
	printf("===================\n\n");
}
