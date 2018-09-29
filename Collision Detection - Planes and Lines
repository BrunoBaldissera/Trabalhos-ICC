#include <stdio.h>
#include <stdlib.h>

typedef struct{  // struct responsável por guardar os coeficientes racionais de cada equação
    int num;     // da matriz na forma de um numerador inteiro e um denominador inteiro
    int den;
}Coef;

void imprimematriz(Coef** eqmat, int neq, int ncoef) // esta função percorre os elementos da matriz e imprime-os formatados
                                                     //com a divisão do numerador pelo denominador representada por uma barra, exceto quando o número pode ser simplificado.
{
	for (int i = 0; i < neq; i++)
		{
			for(int j = 0; j < ncoef; j++)
				{
					if (eqmat[i][j].num % eqmat[i][j].den != 0)
					{
						printf("%d/%d", eqmat[i][j].num, eqmat[i][j].den);
					}
					else
					{
						printf("%d", eqmat[i][j].num / eqmat[i][j].den);
					}
					if (j != ncoef-1) printf("\t");
				}
			printf("\n");
		}
}

Coef** scaneq(Coef** matcoef, int neq, int ncoef) // esta função recebe a matriz alocada dinamicamente e, conforme lê os objetos a serem analisados,
{  	                                              // atribui valores fornecidos pelo usuário nas posições corretas para cada coeficiente de cada equação
   char obj1;
   scanf(" %c", &obj1);

	if (obj1 == 'p')
		{
			for(int j = 0; j < ncoef; j++)
				{
					scanf("%d", &matcoef[0][j].num);
					scanf("%d", &matcoef[0][j].den);
				}
		}
	else
		{
			for(int j = 0; j < ncoef; j++)
				{
					scanf("%d", &matcoef[0][j].num);
					scanf("%d", &matcoef[0][j].den);
				}

			for(int k = 0; k < ncoef; k++)
				{
					scanf("%d", &matcoef[1][k].num);
					scanf("%d", &matcoef[1][k].den);
				}
		}
	char obj2;
	scanf(" %c", &obj2);

	if (obj1 == 'p')
		{
			if (obj2 == 'p')
				{
					for(int j = 0; j < ncoef; j++)
					{
						scanf("%d", &matcoef[1][j].num);
						scanf("%d", &matcoef[1][j].den);
					}
				  return matcoef;
				}
			else
				{
					for(int j = 0; j < ncoef; j++)
					{
						scanf("%d", &matcoef[1][j].num);
						scanf("%d", &matcoef[1][j].den);
					}

					for(int k = 0; k < ncoef; k++)
					{
						scanf("%d", &matcoef[2][k].num);
						scanf("%d", &matcoef[2][k].den);
					}
				  return matcoef;
				}
		}
	else
		{
			if (obj2 == 'p')
				{
					for(int j = 0; j < ncoef; j++)
					{
						scanf("%d", &matcoef[2][j].num);
						scanf("%d", &matcoef[2][j].den);
					}
				  return matcoef;
				}
			else
				{
					for(int j = 0; j < ncoef; j++)
					{
						scanf("%d", &matcoef[2][j].num);
						scanf("%d", &matcoef[2][j].den);
					}

					for(int k = 0; k < ncoef; k++)
					{
						scanf("%d", &matcoef[3][k].num);
						scanf("%d", &matcoef[3][k].den);
					}
				  return matcoef;
				}
		}
}

void swapfun(Coef** eqmat, int neq, int ncoef, int contpivo) // esta função é responsável por realizar o "swap", ou a troca entre a posição das linhas da matriz conforme
{		                                                     // a necessidade durante o processo de escalonamento
	Coef structaux;
			if(eqmat[contpivo][contpivo].num == 0)
				{
					for(int i = (contpivo+1); i < neq; i++)
						{
						  if (eqmat[i][contpivo].num != 0)
						   {
							for (int j = contpivo; j < ncoef; j++)
								{
									structaux.num = eqmat[contpivo][j].num;
									structaux.den = eqmat[contpivo][j].den;

									eqmat[contpivo][j].num = eqmat[i][j].num;
									eqmat[contpivo][j].den = eqmat[i][j].den;

									eqmat[i][j].num = structaux.num;
									eqmat[i][j].den = structaux.den;
								}
							  break;
							}
						}
				}
}

long int funmdc(int a, int b) // esta função calcula o MDC entre dois números de forma recursiva, para posteriormente encontrar o MMC, útil no processo
{				              // de escalonamento, na etapa da subtração entre duas equações
	if (b == 0) return a;
	return funmdc(a, (b % a));
}
long int funmmc(int mdc, int a, int b) // esta função utiliza o valor do MDC calculado anteriormente para encontrar o MMC, usado
{	                                   // no escalonamento
	long int mmc;
	mmc = (a * b)/mdc;
	return mmc;
}

void escalonamento(Coef** eqmat, int neq, int ncoef, int cont) // esta função recursiva chama a função swap quando necessário e efetua o processo
{                                                              // de subtração entre duas equações, multiplicando uma por um fator e chamando o valor
	if (cont == (neq - 1) || cont == (ncoef - 1)) return;      // do MMC para fazer com que se zere o primeiro coeficiente da equação alvo. É chamada
	else                                                       // de forma recursiva até que se chegue ao caso base em que o pivô está na última linha da matriz
	{                                                          // ou na penúltima coluna
		swapfun(eqmat, neq, ncoef, cont);
		Coef lambda, aux;
		int mmc, mdc;

		for (int i = cont + 1; i < neq; i++)
			{
				lambda.num = eqmat[cont][cont].den * eqmat[i][cont].num;
			    lambda.den = eqmat[cont][cont].num * eqmat[i][cont].den;

				for (int j = cont; j < ncoef; j++)
					{
								aux.num =  eqmat[cont][j].num * lambda.num;
								aux.den =  eqmat[cont][j].den * lambda.den;

								if ((aux.den) < eqmat[i][j].den)
								{
								 mdc = funmdc ((aux.den), eqmat[i][j].den);
								}
								if (aux.den >= eqmat[i][j].den)
								{
								 mdc = funmdc (eqmat[i][j].den, (aux.den));
								}

								mmc = funmmc (mdc, (aux.den), eqmat[i][j].den);

								aux.num *= (mmc/aux.den);
								eqmat[i][j].num *= mmc/eqmat[i][j].den;

								aux.den = mmc;

								eqmat[i][j].den = mmc;
								eqmat[i][j].num -= aux.num;

					}
			}
		cont++;

		return escalonamento(eqmat, neq, ncoef, cont);
	}
}

int verificacolisao(Coef** eqmat, int neq, int ncoef) // esta função desempenha o papel de checar inconsistências matemáticas na matriz final escalonada,
{                                                     // a fim de verificar se o sistema permite ou não a colisão entre os dois objetos em estudo.
	for(int i = 0; i < neq; i++)                      // A função retorna 1 caso não haja colisão e retorna 0 quando há
		{
			if (eqmat[i][0].num == 0 && eqmat[i][1].num == 0 && eqmat[i][2].num == 0 && eqmat[i][3].num != 0) return 1;
		}
	return 0;
}

int main (int argc, char* argv[])
{
    int neq, ncoef;
    int colisao;

    scanf("%d", &neq); // aqui escaneamos o número de equações da matriz
    scanf("%d", &ncoef); // aqui escaneamos o número de coeficientes de cada equação

	Coef** eqmat = (Coef**) malloc(sizeof(Coef*) * neq);
    for(int i = 0; i < neq; i++)
		{
			eqmat[i] = (Coef*) malloc(sizeof(Coef) * ncoef);
        }

    eqmat = scaneq(eqmat, neq, ncoef); // chamamos a função que lerá os inouts dos objetos a serem trabalhados

	escalonamento(eqmat, neq, ncoef, 0); // chamamos a importante função de escalonamento que preparará a matriz para verificar enfim a colisão
                                         // dos objetos. Dentro desta função chama-se a função swap, a que calcula o MDC e a que calcula o MMC.

	colisao = verificacolisao(eqmat, neq, ncoef); // Aqui verificamos se há colisão

	if (colisao == 1) printf("nao\n"); //imprimimos conforme o resultado da função
	else printf("sim\n");

	imprimematriz(eqmat, neq, ncoef); // imprimimos a matriz escalonada, formatada e simplificada

	for (int f = 0; f < neq; f++) //efetuamos os devidos 'frees'
		{
			free (eqmat[f]);
		}
	free (eqmat);

  return 0;
}
