#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
//#include "calculadora.h"

void le_prioridades(char op1[], char op2[], char op3[], char op4[], char op5[]){
	scanf("%s", op1);
	scanf("%s", op2);
	scanf("%s", op3);
	scanf("%s", op4);
	scanf("%s", op5);
	if (DEBUG) printf("prioridade lida na ordem: %s\n%s\n%s\n%s\n%s\n", op1, op2, op3, op4, op5);
}

int verifica_validade(void){
	char expressao[1024];
	//loop que para em ';' e continua lendo caso linha termine em ','
}

int main(int argc, char* argv[]){
	
	char op1[4], op2[4], op3[4], op4[4], op5[4];
	le_prioridades(op1, op2, op3, op4, op5);
	verifica_validadde();
	
	return 0;
}
