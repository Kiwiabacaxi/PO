#include <stdio.h>
#include <stdlib.h>
#include "arvoreb.h"

int main()
{
    Arvoreb *tree;

    int vet[] =
    {
        50, 30, 40, 44, 88, 95,
        25, 91, 31, 52, 20, 60,
        70, 74, 78, 79, 22, 28,
        33, 39, 98, 85, 86, 87,
        90, 92, 93, 94, 35, 32,
        84, 99, 105, 110
    };

    int i=0;
    int tam=34;
    tree = cria_arvoreb(4);
  
/*
    for (i=0; i<tam; i++)
    {
        tree=insere_arvoreb(tree,vet[i]);
    }


*/
   // tree=libera_arvoreb(tree);
   
   return 0;
}
