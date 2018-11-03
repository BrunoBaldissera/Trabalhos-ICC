#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int mes;
	int dia;
	int hora;
	int minuto;
}Data;

typedef struct{
	char titulo[32];
	char url[1024];
	Data* data;
	int hora;
}Aba;

typedef struct no{
	struct no* prox;
	struct no* ante;
	Aba* aba;
}No;

typedef struct{
	No* cabeca;
	No* fim;
	int tam;
}Lista;
  
void abrir(){
	No* novo = (No*) malloc(sizeof(No));
	scanf("%");
	scanf("");
	scanf("");
	scanf("");
}

void alterar(){

}

void ordenar(){

}

void exibir(){

}

void sair(){
	//free;
}

int main(int argc, char* argv[]){
	int escolha;
	do{
		scanf("%d", &escolha);
		switch (escolha){
			case 1:
				abrir();
				break;
			case 2:
				alterar();
				break;
			case 3:
				ordenar();
				break;
			case 4:
				exibir();
		 }
	}while(escolha != 5);
	sair();
return 0;
}
