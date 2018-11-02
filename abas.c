#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int mes;
  int dia;
}Data;

typedef struct{
  char titulo[32];
  char url[1024];
  Data data;
  int hora;
}Aba;

//Falta a struct NO

typedef struct{
  No inicio;
  // No fim;
  No tam;
}Lista;
  
void abrir(){

}

void alterar(){

}

void ordenar(){

}

void exibir(){

}

void sair(){

}

int main(int argc, char* argv[]){
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
