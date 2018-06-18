#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int num;
    int den;
}Coef;

Coef** scaneq(int obj, int neq, int ncoef)
{
    if (obj == 'p')
    {
        Coef** matcoef = (Coef**) malloc(sizeof(Coef*) * 2);
        for(int i = 0; i < ncoef; i++)
        {
            matcoef[i] = (Coef*) malloc(sizeof(Coef) * ncoef);
        }

        for(int j = 0; j < ncoef; j++)
        {
            scanf("%d", &matcoef[0][j].num);
            scanf("%d", &matcoef[0][j].den);
        }
    }

    else
    {
        Coef** matcoef = (Coef**) malloc(sizeof(Coef*) * 2);
        for(int i = 0; i < ncoef; i++)
        {
            matcoef[i] = (Coef*) malloc(sizeof(Coef) * ncoef);
        }
        for(int k = 0; k < 2; k++)
        {
            for(int j = 0; j < ncoef; j++)
            {
                scanf("%d", &matcoef[k][j].num);
                scanf("%d", &matcoef[k][j].den);
            }
        }
    }
  return matcoef;
}

int main (int argc, char* argv[])
{
    int neq, ncoef;
    scanf("%d", &neq);
    scanf("%d", &ncoef);

    char obj1,obj2;

    scanf("%c", &obj1);
      Coef** matobj1 = scaneq(obj1, neq, ncoef);

    scanf("%c", &obj2);
      Coef** matobj2 = scaneq(obj2, neq, ncoef);

   return 0;
}
