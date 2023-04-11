#ifndef arvoreb_h
#define arvoreb_h

#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h"
#include <math.h>
#include <windows.h>

struct nob
{
    int folha; //1 se for folha, 0 caso contrario
    int qtd_chaves;
    struct nob* pai;
    Listad *lista_chaves;
};

typedef struct nob Nob;

typedef struct arvoreb
{
    Nob *raiz;
    int ordem;
    int altura;
}Arvoreb;

typedef struct chave
{
    int valor_chave;
    Nob *filho;
} Chave;

Arvoreb* cria_arvoreb(int ordem);
Nob* cria_nob();
//void divide(Arvoreb *tree);
Listad* insere_ordenado_listad(Listad* lista_nos,
                     Chave *chave_nova);

#endif