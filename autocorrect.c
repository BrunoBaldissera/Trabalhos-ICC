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
	//printf("insert word function called\n");
	NODE* aux = root;
	int len = strlen(word);
	//printf("length of '%s' = %d\n", word, len);
	int pos = 0;
	for(int i = 0; i < len; i++){
		word[i] = tolower(word[i]); /*trataremos todas as letras como caracteres minúsculos*/
		pos = word[i] - 'a'; /*pos será um número entre 0 e 25 que representa uma letra do alfabeto*/
		//printf("value of letter '%c' is %d\n", word[i], pos);
		if (aux->kid[pos] == NULL) aux->kid[pos] = create_node(aux);
		if (i == len-1){
			aux->kid[pos]->end = 1;
			break;
		} 
		aux = aux->kid[pos];
	}
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
	//printf("root node created\n");
	char filename[512];
	scanf("%s", filename);
	//printf("filename read: %s\n", filename);
	FILE* fp;
	fp = fopen(filename, "r");
	//printf("book file opened\n");
	char word[46];

	while(!feof(fp)){
		fscanf(fp, "%[a-zA-Z]%*[^a-zA-Z]", word);
		//printf("word scanned: %s\n", word);
		insert_word(word, root);
	}
	fclose(fp);
	return root;
}
/*Aqui nós verificamos individualmente as palavras do tweet e a comparamos com a Trie já existente,
  com o auxílio de um nó 'aux'. Se uma palavra não for encontrada ou o seu fim não corresponder ao fim
  de uma parte da Trie dicionário a palavra recebida pela função é impressa, seguida de espaço.
  ----------------------------------------------------------------------------------------------------
  A função recebe como parâmetros a palavra a ser verificada 'tword' e o nó raiz da Trie.
  Não há retorno.*/
void check_and_print_error(char* tword, NODE* root){
	NODE* aux = root;
	int len = strlen(tword);
	char lowerword[len];
	strcpy(lowerword, tword);
	int pos = 0;
	for(int i = 0; i < len; i++){
        lowerword[i] = tolower(lowerword[i]);
        pos = lowerword[i] - 'a';
        if (aux->kid[pos] == NULL){
            printf("%s ", tword);
            break;
        }
        else if (i == (len-1) && aux->kid[pos]->end != 1){
            printf("%s ", tword);
            break;
        }
        aux = aux->kid[pos];
	}
}
/*A função a seguir tem o papel de ler o nome do arquivo de tweets pela stdin, abri-lo
  e iniciar a leitura do json. Assim que for identificado o trecho de texto < "text": >, a função
  guarda em uma string todo o corpo do texto do tweet, até o próximo caracter < " >, e em seguida
  utilizamos strtok para separar todas as palavras válidas em strings menores iterativamente.
  Caso não se encontre o trecho de texto que identifica o início do texto de um tweet, imprime-se
  uma mensagem de erro.
  A cada palavra lida, é chamada a função 'check_and_print_error' para verificar se esta palavra
  é encontrada na trie que serve de dicionário e imprimi-la caso não seja.
  ------------------------------------------------------------------------------------------------
  É recebido como parâmetro apenas o nó raiz da trie, e não há retorno.*/
void read_tweets(NODE* root){
	char jsonname[512];
	scanf("%s", jsonname);
	//printf("json name read: %s\n", jsonname);
	FILE* ft;
	ft = fopen(jsonname, "r");
	//printf("tweet file opened\n");
	char findtxt[512];
	char tweet[281];
	short int tweetexists = 0;
	while(!feof(ft)){
		fscanf(ft, "%s", findtxt);
		if (strncmp(findtxt, "\"text\":", 7) == 0){
			//printf("text was found: %s\n", findtxt);
			tweetexists = 1;
			fscanf(ft, " \"");
			fscanf(ft, " %[^\"]", tweet);
			//printf("%s\n", tweet);
			char* tword = strtok(tweet, ".,!?\"\n&… '’;@-“”#—1234567890+=*:()[]");
			while(tword != NULL){
				//printf("the word to be checked is '%s'\n", tword);
				check_and_print_error(tword, root);
				if(tword == NULL) break;
                tword = strtok(NULL, ".,!?\"\n&… '’;@-“”#—1234567890+=*:()[]");
			}
			printf("\n");
		}
	}
	fclose(ft);
	if (tweetexists != 1) printf("No tweets to check\n");
}

/*Essa função recursiva será responsável por liberar a memória alocada em toda a estrutura Trie implementada.
  Dentro da função há um loop que verifica se todos os ponteiros para nós filhos do nó atual são nulos, se não são,
  a função é chamada novamente para cada um deles, se o nó atual não tem filhos, o liberamos e retornamos a função.
  -----------------------------------------------------------------------------------------------------------------
  É recebido como parâmetro nó NODE* node (na primeira chamada este é o nó-raiz) e não há retorno para a main.*/
void freetrie(NODE* node){
	for(int i = 0; i < 26; i++){
		if(node->kid[i] != NULL) freetrie(node->kid[i]);
	}
	free(node);
	return;
}
int main(int argc, char* argv[]){
	NODE* root = NULL;
	root = read_book();
	read_tweets(root);
	freetrie(root);
	return 0;
}
