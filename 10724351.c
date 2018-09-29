#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCO 512

int main (int argc, char* argv[]){

	unsigned char entrada[BLOCO]; /*Aqui declaramos o vetor de 512 posi��es que receber� na forma de unsigned char 512 bytes do dump de cada vez*/
	char jpgnome[8]; /*Aqui criamos um vetor de 8 caracteres que ser� usado para gerar o nome de cada jpg criado, e posteriormente ser� impresso pela 'sprintf'*/
	int i, nimg;
	nimg = 0;
	int fimbloco; /*Este inteiro ser� �til para guardar o �ltimo byte lido a cada itera��o do loop com o 'scanf', a fim de identificar se o fim do dump (EOF) foi alcan�ado*/
	FILE *jpg = NULL; /*Aqui declaramos o ponteiro referente a cada arquivo que ser� aberto, escrito e fechado*/
	unsigned char reconheceimg[3] = {0xff, 0xd8, 0xff}; /*Este vetor de unsigned chars serve para efetuar o reconhecimento dos 3 primeiros bytes que caracterizam imagens a cada bloco de 512 bytes*/

	do {
			for(i = 0; i < BLOCO; i++) /*Nesse loop lemos 512 bytes e alocamos no vetor 'entrada'*/
			{
				fimbloco = scanf("%c", &entrada[i]);
			}
			if (fimbloco == EOF) break; /*Aqui checamos se foi atingido o fim do dump, e sa�mos do loop caso isso ocorra*/

			if ((entrada[0] == reconheceimg[0]) && (entrada[1] == reconheceimg[1]) && (entrada[2] == reconheceimg[2])) /*Aqui verificamos se o bloco sendo lido nessa itera��o do loop exterior cont�m uma imagem*/
			{
				if (jpg != NULL) fclose(jpg); /*Caso j� existisse um arquivo aberto, fechamos a fim de abrir um novo arquivo que conter� nova foto, j� que chegou o fim da anterior*/
				sprintf(jpgnome, "%03d.jpg", nimg++); /*Imprimimos o nome do jpg que est� sendo aberto em seguida*/
				jpg = fopen(jpgnome, "wb"); /*Abrimos o arquivo*/
			}
			if (jpg != NULL) fwrite(entrada, 1, 512, jpg); /*Caso haja um arquivo aberto, escrevemos os 512 bytes do bloco sendo lido na itera��o do loop exterior no arquivo aberto*/

	   } while (fimbloco != EOF); /*Esta condi��o do loop exterior permite que sejam lidos blocos de 512 em 512 bytes at� que se chegue ao fim do dump recebido*/

	   if (jpg == NULL) printf("Could not find pictures\n"); /*Caso n�o existam imagens no dump, imprimimos isto na tela*/
	   else fclose(jpg); /*Fechamos o arquivo caso haja um aberto*/

	return 0;
}
