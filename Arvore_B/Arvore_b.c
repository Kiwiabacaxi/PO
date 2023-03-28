#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// arvore b usando deque (lista duplamente encadeada)
// tendo dentro da struct eh_folha, qtd_chaves, pai, lista_chaves e no lugar de direita temos uma info -1
// colocar deque e as 2 funçoes novas q pecisam

typedef struct no_b {
    int folha; // 1 se for folha 0 se for 
    int qtd_chaves;
    Listad *lista_chaves;
} No_b;

typedef struct arvore_b{
    No_b *raiz;
    int ordem;
    int altura;
}Arvore_b;

// criar arvore
Arvore_b *cria_arvore_b(int ordem){
    Arvore_b *arvore = (Arvore_b*)malloc(sizeof(Arvore_b));
    arvore->raiz = NULL;
    arvore->ordem = ordem;
    arvore->altura = 0;
    return arvore;
}

// criar no_b -> ta uma merda
No_b* cria_no_b(){
    No_b *no = (No_b*)malloc(sizeof(No_b));

}
