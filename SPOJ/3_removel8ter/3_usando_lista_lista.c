/* Uma árvore é um grafo conexo sem ciclos. Uma árvore enraizada tem um vértice especial chamado raiz. O pai de um vértice v (diferente de raiz) é o vértice anterior a v no caminho mais curto da raiz ao vértice v. filhos do vértice v são todos os vértices para os quais v é o pai.

Você recebe uma árvore enraizada com n vértices. O vértice 1 é a raiz. Inicialmente, todos os vértices são saudáveis.

A cada segundo você faz duas operações, a operação de espalhamento e, depois disso, a operação de injeção:

    1- Espalhamento: para cada vértice v, se pelo menos um filho de v está infectado, você pode espalhar a doença infectando no máximo um outro filho de v da sua escolha.
    2 -Injeção: você pode escolher qualquer vértice saudável e infectá-lo.
    *********************** acontecem simultaneamente *******************************
Esse processo se repete a cada segundo até que toda a árvore esteja infectada. Você precisa encontrar o número mínimo de segundos necessários para infectar toda a árvore.

Entrada

A entrada consiste em vários casos de teste. 
A primeira linha contém um único inteiro t (1 ≤ t ≤ 104) — o número de casos de teste. Segue a descrição dos casos de teste.
A primeira linha de cada caso de teste contém um único inteiro n (2 ≤ n ≤ 2*105) — o número de vértices na árvore fornecida.
A segunda linha de cada caso de teste contém n – 1 inteiros p2, p3, …, pn (1 ≤ pi ≤n), onde pi é o ancestral do i-ésimo vértice na árvore.
É garantido que o grafo dado é uma árvore.
É garantido que a soma de n em todos os casos de teste não exceda 2*105.

Saída

Para cada caso de teste, você deve gerar um único inteiro — o número mínimo de segundos necessários para infectar toda a árvore.

Exemplo

entrada

5

7
1 1 1 2 2 4

5
5 5 1 4

2
1

3
3 1

6
1 1 1 1 1

saída

4
4
2
3
4

Observação

A imagem representa a árvore do primeiro caso de teste durante cada segundo.

Um vértice é preto se não estiver infectado. Um vértice é azul se for infectado por injeção durante o segundo anterior. 
Um vértice é verde se for infectado por propagação durante o segundo anterior. 
Um vértice é vermelho se for infectado antes do segundo anterior. 
*/


/* typedef struct no_N{
    int info;
    // quantidade de filhos
    int qtd;
    struct arvn *prim;
    struct arvn *prox;
}ArvN; */

/* struct t {
    int n;
    int numkids;
    struct t **kids;
} */

// ---------------------------// LISTA D

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Definição da estrutura de dados para um no da lista dupla encadeada genérica
/* typedef struct no {
    void *dado;
    // QUANTIDADE DE FILHOS
    int qtd;
    // se estiver infectado
    bool infectado; // 0 = não, 1 = sim
    
    // aponta para a lista
    lista *filhos;
} no; */



typedef struct nod {
    int info;
    struct nod *ant;
    struct nod *prox;
} Nod;


typedef struct listad{
    Nod *ini;
    Nod *fim;
} Listad;

// struct arvore n 
typedef struct arvn {
    int info; 
    int qtd; // quantidade de filhos
    bool infectado; // se estiver infectado 0 = não, 1 = sim
    Listad *filhos; // aponta para a lista
} ArvN;

// ---------------------------// LISTA D


Listad* cria_listad(){
    Listad* novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod* cria_nod(int valor){
    Nod* novo = (Nod*)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}

Listad* insere_inicio_listad(Listad *L, int valor){
    Nod *novo= cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;

    }
    else
    {
        if (L->ini == NULL)
            L->ini = L->fim = novo;
        else
        {
            novo->prox = L->ini;
            L->ini->ant = novo;
            L->ini = novo;
        }
    }
    return L;

}

void mostra_listad(Listad* L){
    Nod* aux = L->ini;

    while(aux != NULL)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n ");
}

Listad* insere_fim_listad(Listad* L, int valor){
    Nod *novo = cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {


        if(L->ini == NULL)
        {
            L->ini = L->fim = novo;
        }
        else
        {
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        }
    }
    return L;
}

Nod* localiza_elemento(Listad *L, int valor){

    Nod* aux = L->ini;

    while(aux!=NULL && aux->info != valor)
        aux = aux->prox;

    return aux;
}

void insere_apos_elemento(Listad* L, int valor, int elemento){
    Nod* novo =cria_nod(valor);

    Nod *aux2, *aux = localiza_elemento(L, elemento);

    if (aux != NULL)
    {
        aux2 = aux->prox;
        novo->prox = aux2;
        aux2->ant = novo;
        novo->ant = aux;
        aux->prox = novo;
        if (aux == L->fim)
            L->fim = novo;
    }
    else
        printf("elemento nao encontrado");
}

int remove_inicio_listad(Listad *L){
    Nod* aux;
    int resposta = -1;//quando nao tem nada pra remover
    if (L!=NULL)
        if (L->ini != NULL)
        {
            aux = L->ini;

            if (L->ini != L->fim)
            {
                L->ini->prox->ant = NULL;
                L->ini = L->ini->prox;
            }
            else
                L->ini = L->fim = NULL;

            resposta = aux->info;
            free(aux);
        }
    return resposta;
}

int remove_fim_listad(Listad *L){
    Nod* aux;
    int resposta = -1;

    if(L != NULL && L->fim != NULL)
    {
        aux = L->fim;
        if(L->ini != L->fim)//mais de um elemento na lista
        {
            L->fim->ant->prox = NULL;
            L->fim = L->fim->ant;
        }
        else//s� tem um elemento na lista
            L->ini = L->fim = NULL;

        resposta = aux->info;
        free(aux);
    }
    return resposta;
}

int remove_elemento_listad(Listad *L, int valor){
    Nod *aux = localiza_elemento(L,valor);
    int resposta = -1;

    if (aux != NULL)
    {
        if (aux == L->ini)
            resposta = remove_inicio_listad(L);
        else if(aux == L->fim)
            resposta = remove_fim_listad(L);
        else
        {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            resposta = aux->info;
            free(aux);
        }
    }
    return resposta;
}

// libera a lista
void libera_listad(Listad *L){
    Nod *aux = L->ini;
    Nod *aux2;

    while(aux != NULL)
    {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(L);
}

// insere_ordenado_listad
Listad *insere_ordenado_listad(Listad *lista_nos, int valor){
    Nod *novo = cria_nod(valor);
    Nod *aux = lista_nos->ini;

    if (lista_nos == NULL)
    {
        lista_nos = cria_listad();
        lista_nos->ini = lista_nos->fim = novo;
    }
    else
    {
        if (lista_nos->ini == NULL)
            lista_nos->ini = lista_nos->fim = novo;
        else
        {
            while(aux != NULL && aux->info < valor)
                aux = aux->prox;

            if (aux == NULL)
                lista_nos = insere_fim_listad(lista_nos, valor);
            else if (aux == lista_nos->ini)
                lista_nos = insere_inicio_listad(lista_nos, valor);
            else
                insere_apos_elemento(lista_nos, valor, aux->ant->info);
        }
    }
    return lista_nos;
}

// ---------------------------// operaçoes arvore

// compara
int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// ordenar um array
void ordena(int *vet, int tam){
    qsort(vet, tam, sizeof(int), cmp);
}

// cria arvore
ArvN* cria_arvN(int valor){
    ArvN* nova = (ArvN*)malloc(sizeof(ArvN));
    nova->info = valor;
    nova->qtd = 0;
    nova->infectado = false;
    nova->filhos = cria_listad();
    return nova;
}

// inserir na arvore, apartir do vetor ja ordenado, se o pai nao existir, cria,
// se o filho nao existir, cria, se o filho ja existir, nao cria
ArvN* insere_arvN(ArvN* raiz, int pai, int filho){
    ArvN* aux = raiz;
    ArvN* aux2 = raiz;
    Nod* aux3 = NULL;
    Nod* aux4 = NULL;
    int i = 0;

    // se a raiz for nula, cria a raiz
    if (raiz == NULL){
        raiz = cria_arvN(pai);
        raiz->filhos = insere_fim_listad(raiz->filhos, filho);
        raiz->qtd++;
    }
    else{
        // se o pai nao existir, cria o pai
        if (localiza_elemento(raiz->filhos, pai) == NULL){
            raiz->filhos = insere_fim_listad(raiz->filhos, pai);
            raiz->qtd++;
        }
        // se o filho nao existir, cria o filho
        if (localiza_elemento(raiz->filhos, filho) == NULL){
            raiz->filhos = insere_fim_listad(raiz->filhos, filho);
            raiz->qtd++;
        }
    }
    return raiz;
}



int *vetor;

// define MAX_INT
#define MAX_INT 250000

int main(){
    // leitura do número de casos de teste
    int t;
    scanf("%d", &t);

    // para cada caso de teste
    for(int k = 0; k < t; k++){
        // leitura do número de vértices
        int n;
        scanf("%d", &n);

        // leitura dos vértices
        vetor = (int*)malloc(MAX_INT*sizeof(int));

        for(int i = 0; i < n; i++){
            scanf("%d", &vetor[i]);
        }

        // ordena o vetor
        ordena(vetor, n);

        // cria a arvore
        ArvN* arvore = NULL;

        // insere ordenado na arvore
        for(int i = 0; i < n; i++){
            arvore = insere_arvN(arvore, vetor[i], vetor[i+1]);
            i++;
        }

        // mostra a arvore
        while(arvore->filhos->ini != NULL){
            printf("%d ", arvore->filhos->ini->info);
            arvore->filhos->ini = arvore->filhos->ini->prox;
        }

        // mostra a arvore
        //mostra_arvN(arvore);

        // libera a arvore
        //libera_arvN(arvore);

        // libera o vetor
        free(vetor);



    }
    return 0;
}
