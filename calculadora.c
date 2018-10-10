#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void verifica_validade(char expressao[]){
	int delim = 0;
	char atual = ' ';
	//strtok
	if (delim == 0) printf("delimitadores ok\n");
	else printf("expressao invalida: delimitadores incorretos\n"); 
}

int recebe_expressoes(void){
	char expressao[1024];
	char fim = ' ';
	while (fim != ';'){
		scanf(" %[^,;]", expressao);
		scanf(" %c", &fim);
		if (DEBUG) printf("a expressao lida foi \"%s\"\nO fim lido foi \"%c\"\n", expressao, fim);
		if (fim == ',') verifica_validade(expressao);	
	}
	return 0;
}

int main(int argc, char* argv[]){
	
	char op1[4], op2[4], op3[4], op4[4], op5[4];
	le_prioridades(op1, op2, op3, op4, op5);
	recebe_expressoes();
	
	return 0;
}
