#ifndef LISTADUPLA_H_INCLUDED
#define LISTADUPLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

struct nod
{
    void* info;
    struct nod *ant;
    struct nod *prox;
};
typedef struct nod Nod;

struct listad
{
        Nod *ini;
        Nod *fim;
};
typedef struct listad Listad;

Listad* cria_listad();
Nod* cria_nod(void* valor);
Listad* insere_inicio_listad(Listad *L, void* valor);
Listad* insere_fim_listad(Listad *L, void* valor);
void* remove_fim_listas(Listad *L);
void* remove_inicio_listad(Listad *L);
Listad* libera_listad(Listad *L);
int eh_vazia_listad(Listad *L);

#endif // LISTADUPLA_H_INCLUDED
