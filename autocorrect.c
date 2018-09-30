#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node_{
	short int end;
	struct node_* kid[26];
};

typedef struct node_ NODE;
    
/*Aqui é criado um novo nó a ser inserido na trie,
  inicializando todos os seus ponteiros 'filhos' como NULO
  e atribuindo 0 ao valor 'fim' -que indica se o nó representa
  o fim de uma palara ou não - do nó*.
  ------------------------------------------------------------
  A função recebe como parâmetro apenas o ponteiro para o nó 'n'
  que será criado, e o retorna já alocado e com suas devidas
  alterações*/  
NODE* create_node(NODE* n){
	n = (NODE*) malloc(sizeof(NODE));
	n->end = 0;
	for(int i = 0; i < 26; i++){ /*Atribui todos os nós 'filhos' do nó criado para NULO*/
		n->kid[i] = NULL;
	}
	return n;
}

/*Esta função deverá receber cada palavra recebida a partir da leitura do livro
  que serve de base para a criação do dicionário na função 'read_book' e inseri-la
  na estrutura de dados Trie, efetuando todas as verificações necessárias para que não
  haja desperdício ou repetições de palavras.
  ------------------------------------------------------------------------------------
  A função recebe como parâmetro a string estática 'word' e o ponteiro para o 
  nó raíz da trie. Não se retorna nada.*/

void insert_word(char word[], NODE* root){
	NODE* aux = root;
	int len = strlen(word);
	int pos = 0;
	for(int i = 0; i < len; i++){
		word[i] = tolower(word[i]); /*trataremos todas as letras como caracteres minúsculos*/
		pos = word[i] - 'a'; /*pos será um número entre 0 e 25 que representa uma letra do alfabeto*/
		if (aux->kid[pos] == NULL) aux->kid[pos] = create_node(aux);
		aux = aux->kid[pos];
	}
	if (aux != root) aux->end = 1;
}
/*enquanto o arquivo não acabar, nós leremos todo conjunto de caracteres
  encontrado até um diferente de a - Z como string e a chamamos de 'word'. Em seguida,
  chamamos a função 'insert_word()' para inserir essa palavra na estrutura Trie, que
  servirá como o dicionário deste programa
  ------------------------------------------------------------------------------------
  A função não recebe parâmetros e tem como retorno o ponteiro para o nó raíz da trie*/
NODE* read_book(void){
	NODE* root = NULL;
	root = create_node(root);
	char filename[512];
	scanf("%s", filename);
	FILE* fp;
	fp = fopen(filename, "r");
	char word[46];
	
	while(!feof(fp)){
		fscanf(fp, "%s[a-zA-Z]", word);
		insert_word(word, root);
	}
	fclose(fp);
	return root;
}

void check_and_print_error(char tword[]){
	//verifica se a palavra atual existe na trie
	//se não existir, imprime a palavra do próprio tweet seguida de espaço
}

void read_tweets(void){
	char jsonname[512];
	scanf("%s", jsonname);
	FILE* ft;
	ft = fopen(jsonname, "r");
	char findtxt[512];
	char tword[281];
	while(!feof(ft)){	
		fscanf(ft, "%s", findtxt);
		if (strncmp(findtxt, "\"text\":", 7) == 0){
			fscanf(ft, " \"");
			while(/*condição de parada da parte 'text' de um tweet*/){
				fscanf(ft, "%s[a-zA-Z]", tword);
				check_and_print_error(tword);
			}
			printf("\n");
		}
	}
}
int main(int argc, char* argv[]){
	
	NODE* root = NULL;
	root = read_book();
	read_tweets();
	
	//FREE
	return 0;
}
