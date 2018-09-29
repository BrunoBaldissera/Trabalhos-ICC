#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

/*Esta struct armazena os 4 dados de medidas que ser�o usados para classificar as esp�cies de flores na forma de floats,
  al�m do nome j� classificado da esp�cie, na forma de uma string*/
typedef struct flower{
    double sl; /*Comprimento da s�pala*/
    double sw; /*Largura da s�pala*/
    double pl; /*Comprimento da p�tala*/
    double pw; /*Largura da p�tala*/
    char species[100]; /*Nome da esp�cie*/
    char guess[100]; /*Chute da esp�cie dado pelo programa*/
}flower;

typedef struct sdist{
    double d; /*Dist�ncia calculada da flor do teste para alguma flor do treino*/
    char s[100]; /*Nome da esp�cie*/
}sdist;

/*Esta fun��o � respons�vel por ler o arquivo de treino ou teste e contabilizar a quantidade de flores contidas nesses dados, com base na quantidade de linhas existentes.
  A fun��o retorna um inteiro n que representa essa quantidade de flores e recebe como par�metro o ponteiro do arquivo, bem como o nome deste, criado e lido na fun��o main*/
int count_flowers(FILE *file){

    int n = 0;
    while (!feof(file)){
        fscanf(file, "%*[^\n]\n");
        n++;
    }
    if (DEBUG) printf("%d", n);
 return (n-1); /*desconsiderando a primeira linha do arquivo*/
}

/*A fun��o a seguir rebobina o arquivo j� aberto pela fun��o que contabiliza as flores com o intuito de, j� se sabendo o n�mero n de flores, armazenar
  em um vetor de structs do tipo 'flor' as informa��es contidas no arquivo sobre cada exemplar de flor (comprimento e largura das p�talas e s�palas,
  al�m do nome da esp�cie).
  A fun��o n�o retorna nada pois efetua altera��es em vetores j� existentes por meio de ponteiro, e recebe como par�metros este ponteiro, o ponteiro do
  arquivo e a quantidade n de flores no arquivo atual, seja o de treino ou o de teste*/
void read_informations(FILE *file, int n, flower* array){

    rewind(file);
    int i = 0;
    char* headline;
    fscanf(file, "%m[^ \n]", &headline);

    for(i = 0; i < n; i++){
        fscanf(file, "%lf,%lf,%lf,%lf,", &array[i].sl, &array[i].sw, &array[i].pl, &array[i].pw);
        if (DEBUG) printf ("%lf %lf %lf %lf  ", array[i].sl, array[i].sw, array[i].pl, array[i].pw);
        fscanf(file, "\"%[^\"]\"", array[i].species);
        if (DEBUG) printf("%s\n", array[i].species);
    }
 free (headline);
}

/*Aqui usamos o algoritmo de insertion sort para ordenar o vetor de dist�ncias posteriormente.
  A fun��o n�o apresenta retorno e recebe como par�metros o vetor a ser ordenado e o tamanho n de elementos contidos nele*/
void insertion_sort(sdist* array, int n){

    sdist aux;
    int i, j;
    for(i = 0; i < n; i ++){

        aux = array[i];
        j = i - 1;

        while (j >= 0 && array[j].d > aux.d){
            array[j+1] = array[j];
            j--;
        }
       array[j+1] = aux;
    }
}

/*Esta fun��o � chamada na main nteste vezes, e para cada vez calcula a distancia euclidiana entre um dos elementos do teste com todos os elementos
  do treino. Em seguida, ordena as dist�ncias e, dentre as k menores, determina qual � a esp�cia predominante, e com base nessa decis�o,
  determina o chute a ser dado. Ao fim, imprime-se o chute e a classifica��o correta. A fun��o � do tipo void e recebe como par�metros
  o vetor do treino, o vetor do teste, a quantidade de elementos em cada, o inteiro k, o contador de qual elemento do teste est� sendo
  avaliado, o vetor de structs auxiliar que armazena as dist�ncias e nomes correspondentes e o contador de acertos do programa.*/
void calculate_distances(flower* trainarray, flower* testarray, int ntrain, int ntest, int k, int counter, sdist* distances, int* rightguesses){

    int virginicac, versicolorc, setosac;
    virginicac = 0;
    setosac = 0;
    versicolorc = 0;

    for(int i = 0; i < ntrain; i++){

        distances[i].d = pow((trainarray[i].sl - testarray[counter].sl),2) + pow((trainarray[i].sw - testarray[counter].sw),2) + pow((trainarray[i].pl - testarray[counter].pl),2) + pow((trainarray[i].pw - testarray[counter].pw),2);
        strcpy(distances[i].s, trainarray[i].species);
        if (DEBUG) printf("%lf  %s", distances[i].d, distances[i].s);
    }
    insertion_sort(distances, ntrain);

    if (DEBUG){
        for(int g = 0; g < ntrain; g++){
            printf("%lf\n", distances[g].d);
        }
    }

    for(int m = 0; m < k; m++){

        if (strcmp (distances[m].s, "virginica") == 0) virginicac++;
        else if (strcmp (distances[m].s, "setosa") == 0) setosac++;
        else if (strcmp (distances[m].s, "versicolor") == 0) versicolorc++;
    }

    if (virginicac > setosac && virginicac > versicolorc){
        strcpy(testarray[counter].guess, "virginica");
    }
    else if (setosac > virginicac && setosac > versicolorc){
        strcpy(testarray[counter].guess, "setosa");
    }
    else if (versicolorc > setosac && versicolorc > virginicac){
        strcpy(testarray[counter].guess, "versicolor");
    }
    else{
        strcpy(testarray[counter].guess, distances[0].s);
    }
 if (strcmp (testarray[counter].guess, testarray[counter].species) == 0) (*rightguesses)++;
 printf("%s %s\n", testarray[counter].guess, testarray[counter].species);
}

int main(int argc, char* argv[]){

    int k;
    char* trainname;
    char* testname;

    scanf("%m[^ ] %m[^ ] %d", &trainname, &testname, &k);
    if (DEBUG) printf("%s  %s  %d\n", trainname, testname, k);

    FILE *train;
    train = fopen(trainname, "r");
    int ntrain = count_flowers(train);

        if(k < 1 || k > ntrain){      /*Aqui tratamos os casos em que k � inv�lido, e/ou n�o � coerente com os dados do arquivo de treino*/
        printf("k is invalid\n");
        return 0;
        }

    flower* trainarray = malloc (sizeof(flower) * ntrain);
    read_informations(train, ntrain, trainarray);
    fclose(train);

    FILE *test;
    test = fopen(testname, "r");
    int ntest = count_flowers(test);
    flower* testarray = malloc (sizeof(flower) * ntest);
    read_informations(test, ntest, testarray);
    fclose(test);

    int counter = 0;
    int rightguesses = 0;
    sdist* distances = malloc (sizeof(sdist) * ntrain);
    for (counter = 0; counter < ntest; counter++){
        calculate_distances(trainarray, testarray, ntrain, ntest, k, counter, distances, &rightguesses);
    }
    double accuracy = (double) rightguesses / (double) ntest;
    printf("%.4lf\n", accuracy); /*Aqui imprimimos a acur�cia calculada pela raz�o entre acertos e chutes dados*/

    free(trainarray);
    free(testarray);
    free(distances);

 return 0;
}
