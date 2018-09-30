#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_{
	short int end;
	struct node_* kid[26];
};

typedef struct node_ NODE;

/*Esta função deverá receber cada palavra recebida a partir da leitura do 'livro'
  que serve de base para a criação do dicionário na função 'read_book' e inseri-la
  na estrutura de dados Trie*/
void insert_word(char word[]){
		
	}
/*enquanto o arquivo não acabar, nós leremos todo conjunto de caracteres
  encontrado até um diferente de a - Z e o chamamos de 'word'. Em seguida,
  lemos os caracteres individuais dessa palavra e o inserimos na estrutura 'trie'*/
NODE read_book(void){
	NODE trie;				
	char dictionary[200];
	scanf("%s", dictionary);
	FILE* fp;
	fp = fopen(dictionary, "r");
	char word[45];
	while(!feof(fp)){
		fscanf(fp, "%s[a-zA-Z]", word);
		insere_palavra(word);
	}
	return trie;
}

int main(int argc, char* argv[]){
	
	/*read_book();
	create_dictionary();
	read_tweets();
	check_and_print_error();*/
	
	return 0;
}
