#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

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
}Aba;

typedef struct no{
	struct no* prox;
        struct no* ant;
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
	n->ant = NULL;
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

	novo->ant = L->fim;
	L->fim->prox = novo;
	novo->prox = NULL;
	L->fim = novo;
	(L->tam)++;
}

int alterar(Lista* L){
	char ver_titulo[32];
	scanf("%[^\n]%*c", ver_titulo);
	if (DEBUG) printf ("o titulo é \"%s\"\n", ver_titulo); 
	int nova_pos, pos_atual = 1;
	scanf("%d", &nova_pos);
	if (DEBUG) printf ("a nova posição é \"%d\"\n", nova_pos);
	int melhor_caso = 0;
	
	No* aux = L->cabeca->prox;
	No* aux_destino;

	while (strcmp(aux->aba.titulo, ver_titulo) != 0){
		if (pos_atual == L->tam) return 0;
		if (pos_atual == nova_pos){
	    		aux_destino = aux;
	    		melhor_caso = 1;
	  	}
		aux = aux->prox;
		pos_atual++;
	}
	if (nova_pos >= L->tam){
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		aux->prox = NULL;
		aux->ant = L->fim;
		L->fim->prox = aux;
		L->fim = aux;
		return 1;
	}
	if (melhor_caso == 1){
	        if (pos_atual == L->tam){
			L->fim = aux->ant;
			aux->ant->prox =aux->prox;
			aux->prox = aux_destino;
			aux->ant = aux_destino->ant;
			aux_destino->ant->prox = aux;
			aux_destino->ant = aux;
			return 2;
		}	
		aux->ant->prox = aux->prox;	
		aux->prox->ant = aux->ant;
		aux->prox = aux_destino;
		aux->ant = aux_destino->ant;
		aux_destino->ant->prox = aux;
		aux_destino->ant = aux;
		return 2;
	}
	if (nova_pos > pos_atual){
		aux_destino = aux;
		while (pos_atual != nova_pos){
			aux_destino = aux_destino->prox;
			pos_atual++;
		}
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		aux->prox = aux_destino->prox;
		aux->ant = aux_destino;
		aux_destino->prox->ant = aux;
		aux_destino->prox = aux;
		return 3;
	}
	return 4;
}

void ordenar(Lista* L){
	if (DEBUG) printf ("função \"ordenar\" inicializada\n");
}

void exibir(Lista* L){
	No* aux = L->cabeca->prox;
	for (int i = 0; i < L->tam; i++){
		printf("%s %s %02d/%02d %02d:%02d\n", aux->aba.titulo, aux->aba.url, aux->aba.data.dia, aux->aba.data.mes, aux->aba.data.hora, aux->aba.data.minuto);
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
