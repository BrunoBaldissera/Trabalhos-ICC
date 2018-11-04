#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

typedef struct{
	int mes;
	int dia;
	int hora;
	int minuto;
}Data;

typedef struct{
	char titulo[32];
	char url[1024];
	Data data;
	//int pos;
}Aba;

typedef struct no{
	struct no* prox;
	Aba aba;
}No;

typedef struct{
	No* cabeca;
	No* fim;
	int tam;
}Lista;

No* cria_no(void){
	No* n = (No*) malloc(sizeof(No));
	n->prox = NULL;
	return n;
}  

Lista* cria_lista(void){
	Lista* L = (Lista*) malloc(sizeof(Lista));
	L->cabeca = cria_no();
	L->fim = L->cabeca;
	L->tam = 0;
	if (DEBUG) printf("Lista criada com sucesso\n");
	return L;
}
 
void abrir(Lista* L){
	if (DEBUG) printf ("operação de abrir nova aba inicializada\n");
	No* novo = cria_no();
	scanf("%[^\n]%*c", novo->aba.titulo);
	scanf("%[^\n]%*c", novo->aba.url);
	scanf("%d %d", &novo->aba.data.dia, &novo->aba.data.mes);
	scanf("%d %d", &novo->aba.data.hora, &novo->aba.data.minuto);
	
	L->fim->prox = novo;
	novo->prox = NULL;
	L->fim = novo;
	(L->tam)++;
	//novo->aba.pos = L->tam;
	if (DEBUG) printf ("operação de abrir nova aba finalizada\n");
}

void alterar(Lista* L){
	if (DEBUG) printf ("função \"alterar\" inicializada\n");
	char ver_titulo[32];
	scanf("%[^\n]%*c", ver_titulo);
	if (DEBUG) printf ("o novo titulo é \"%s\"\n", ver_titulo); 
	int nova_pos, pos_atual = 1;
	scanf("%d", &nova_pos);
	if (DEBUG) printf ("a nova posição é \"%d\"\n", nova_pos); 
	
	No* aux = L->cabeca->prox;
	while (aux->aba.titulo != ver_titulo && aux != NULL){
		aux = aux->prox;
		pos_atual++;
	}
}

void ordenar(Lista* L){
	if (DEBUG) printf ("função \"ordenar\" inicializada\n");
}

void exibir(Lista* L){
	if (DEBUG) printf ("função \"exibir\" inicializada\n");
	No* aux = L->cabeca->prox;
	while (aux != NULL){
		printf("%s %s %d/%d %d/%d\n", aux->aba.titulo, aux->aba.url, aux->aba.data.dia, aux->aba.data.mes, aux->aba.data.hora, aux->aba.data.minuto);
		aux = aux->prox;
	}
	printf("\n");
}

void sair(Lista* L){
	if (DEBUG) printf ("função \"sair\" inicializada\n");
	//free;
}

int main(int argc, char* argv[]){
	int escolha;
	Lista* L = cria_lista();
	do{
		if (DEBUG) printf("insira o valor correspondente à operação desejada\n");
		scanf("%d", &escolha);
		getchar();
		switch (escolha){
			case 1:
				abrir(L);
				break;
			case 2:
				alterar(L);
				break;
			case 3:
				ordenar(L);
				break;
			case 4:
				exibir(L);
		 }
	}while(escolha != 5);
	sair(L);
return 0;
}
