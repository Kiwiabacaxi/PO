#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ---------------------------------------- // STRUCTS // ---------------------------------------- //
struct nod
{
    void *info;
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

Listad *cria_listad();
Nod *cria_nod(void *valor);
Listad *insere_inicio_listad(Listad *L, void *valor);
Listad *insere_fim_listad(Listad *L, void *valor);
void *remove_fim_listas(Listad *L);
void *remove_inicio_listad(Listad *L);
Listad *libera_listad(Listad *L);
int eh_vazia_listad(Listad *L);

struct nob
{
    int folha; // 1 se for folha, 0 caso contrario
    int qtd_chaves;
    struct nob *pai;
    Listad *lista_chaves;
};

typedef struct nob Nob;

typedef struct arvoreb
{
    Nob *raiz;
    int ordem;
    int altura;
} Arvoreb;

typedef struct chave
{
    int valor_chave;
    Nob *filho;
} Chave;

Arvoreb *cria_arvoreb(int ordem);
Nob *cria_nob();
// void divide(Arvoreb *tree);
Listad *insere_ordenado_listad(Listad *lista_nos,
                               Chave *chave_nova);

// ---------------------------------------- // LISTA DUPLAMENTE ENCADEADA // ---------------------------------------- //

int *cria_inteiro(int n)
{
    int *a = malloc(sizeof(int));
    *a = n;
    return a;
}

Listad *cria_listad()
{
    Listad *novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod *cria_nod(void *valor)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}

Listad *insere_inicio_listad(Listad *L, void *valor)
{
    Nod *novo = cria_nod(valor);

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

Listad *insere_fim_listad(Listad *L, void *valor)
{
    Nod *novo = cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {

        if (L->ini == NULL)
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

void *remove_inicio_listad(Listad *L)
{
    Nod *aux;
    void *resposta = NULL; // quando nao tem nada pra remover
    if (L != NULL)
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

void *remove_fim_listad(Listad *L)
{
    Nod *aux;
    void *resposta = NULL;

    if (L != NULL && L->fim != NULL)
    {
        aux = L->fim;
        if (L->ini != L->fim) // mais de um elemento na lista
        {
            L->fim->ant->prox = NULL;
            L->fim = L->fim->ant;
        }
        else // s� tem um elemento na lista
            L->ini = L->fim = NULL;

        resposta = aux->info;
        free(aux);
    }
    return resposta;
}

Listad *libera_listad(Listad *L)
{
    Nod *aux = L->ini;

    while (aux != NULL)
    {
        L->ini = L->ini->prox;
        free(aux->info);
        free(aux);
        aux = L->ini;
    }

    free(L);
    return NULL;
}

int eh_vazia_listad(Listad *L)
{
    if (L == NULL || L->ini == NULL)
        return 1;
    else
        return 0;
}

// ---------------------------------------- // ARVORE B // ---------------------------------------- //

Arvoreb *cria_arvoreb(int ordem)
{
    Arvoreb *nova = (Arvoreb *)malloc(sizeof(Arvoreb));

    nova->raiz = NULL;
    nova->ordem = ordem;
    nova->altura = 0;
    return nova;
}

Nob *cria_nob()
{
    Nob *novo = (Nob *)malloc(sizeof(Nob)), novo2;

    novo->folha = 1;
    novo->pai = NULL;
    novo->qtd_chaves = 0;
    novo->lista_chaves = cria_listad();

    return novo;
}

Chave *cria_chave(int valor)
{
    Chave *ch = (Chave *)malloc(sizeof(Chave));
    ch->filho = NULL;
    ch->valor_chave = valor;
    return ch;
}

Listad *divide_lista(Listad *L, int n)
{
    Listad *L2 = cria_listad();
    Nod *aux = L->ini;
    while (n > 1)
    {
        aux = aux->prox;
        n--;
    }
    L2->fim = L->fim;
    L->fim = aux;
    L2->ini = aux->prox;
    L2->ini->ant = NULL;
    L->fim->prox = NULL;
    return L2;
}

Listad *insere_ordenado_listad(Listad *lista_nos,
                               Chave *chave_nova)
{

    Nod *aux = lista_nos->ini;

    while (aux != NULL && chave_nova->valor_chave > get_valor_chave(aux))
    {
        aux = aux->prox;
    }
    if (aux == lista_nos->ini)
    {
        lista_nos = insere_inicio_listad(lista_nos, (void *)chave_nova);
    }
    else
    {
        if (aux == NULL)
            lista_nos = insere_fim_listad(lista_nos, (void *)chave_nova);
        else
        {
            Nod *novo = cria_nod((void *)chave_nova);
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
    }
    return lista_nos;
}

int get_valor_chave(Nod *aux)
{
    return ((Chave *)aux->info)->valor_chave;
}

Nob *get_filho(Nod *aux)
{
    return ((Chave *)aux->info)->filho;
}

void set_filho(Nod *aux, Nob *novo_filho)
{
    ((Chave *)aux->info)->filho = novo_filho;
}

/*
inicio
  encontre uma folha para inserir a chave  K
  enquanto tem valor para inserir
  insira K na folha encontrada (insere ordenado na lista)
  se (nó não está cheio) entao
         marque que não tem mais valor para inserir
  senão
        divida o nó em nó1 e nó2; //nó1 == nó, nó2 eh novo
     K = ultima chave de nó1; //a qual é retirada de nó1
        se (nó era a raiz) entao
            crie uma nova raiz como ascendente de nó1 e nó2;
            coloque K e ponteiros para nó1 e nó2 na raiz e
            marque que não tem mais valor para inserir
        senao
            folha = seu pai;
        fimse
  fimse
  fimenquanto
fim
*/

void insercao_arvoreb(Arvoreb *tree, int chave)
{

    Chave *ch = cria_chave(chave);
    Nob *folha = localiza_folha(tree, chave);
    int tem_valor = 1;
    Nob *novo = NULL;
    if (tree->raiz == NULL)
    {
        tree->raiz->lista_chaves = insere_inicio_listad(tree->raiz->lista_chaves, (void *)ch);
    }
    else
    {
        while (tem_valor)
        {
            folha->lista_chaves = insere_ordenado_listad(folha->lista_chaves, ch);
            folha->qtd_chaves++;
            if (folha->qtd_chaves < tree->ordem)
            {
                tem_valor = 0;
            }
            else
            {
                novo = divide_no(folha);
                ch = get_ultima_chave(folha);
                if (folha == tree->raiz)
                {
                    tree->raiz = cria_nova_raiz(ch, folha, novo);
                    tem_valor = 0;
                }
                else
                {
                    folha = folha->pai;
                }
            }
        }
    }
}

Nob *localiza_folha(Arvoreb *tree, int chave)
{
    Nob *aux = tree->raiz; // auxiliar para percorrer a arvore

    while (aux->folha == 0) // se nao for folha
    {
        Nod *aux_lista = aux->lista_chaves->ini; // auxiliar para percorrer a lista de chaves
        while (aux_lista->prox != NULL &&
               chave > get_valor_chave(aux_lista)) // enquanto a chave for maior que a chave atual
        {
            aux_lista = aux_lista->prox;
        }
        aux = get_filho(aux_lista); //((Chave*)aux_lista->info)->filho; //auxiliar passa a ser o filho da chave atual
    }
    return aux;
}

Nob *divide_no(Nob *no_dividir)
{
    Chave *ch_subir;
    Nod *aux;
    Nob *novo = cria_nob();
    int n = ceil(no_dividir->qtd_chaves / 2.0);
    /*
    if (no_dividir->qtd_chaves % 2 != 0)
       n = no_dividir->qtd_chaves/2 + 1;
    else
       n = no_dividir->qtd_chaves/2;
    */
    novo->lista_chaves = divide_lista(
        no_dividir->lista_chaves, n);
    // colocar -1 no final do nó que dividiu
    no_dividir->lista_chaves = insere_fim_listad(
        no_dividir->lista_chaves, (void *)cria_chave(-1));
    no_dividir->qtd_chaves = n;

    novo->folha = no_dividir->folha;
    novo->qtd_chaves = no_dividir->qtd_chaves - n;
    novo->pai = no_dividir->pai;

    if (no_dividir->folha != 0) // for folha
    {
        ch_subir = get_ultima_chave(no_dividir);
        ch_subir->filho = no_dividir;

        // localiza o apontador do no_dividir
        if (no_dividir->pai != NULL)
        {
            aux = no_dividir->pai->lista_chaves->ini;

            while (get_filho(aux) != no_dividir)
                aux = aux->prox;

            set_filho(aux, novo);
        }
    }
    else
    {
        aux = novo->lista_chaves->ini;
        while (aux->prox != NULL)
        {
            get_filho(aux)->pai = novo;
            aux = aux->prox;
        }
        set_filho(aux, get(novo->lista_chaves->ini));
    }

    return novo;
}

// criar nova raiz
Nob *cria_nova_raiz(Chave *ch, Nob *no1, Nob *no2)
{
    Nob *raiz = cria_nob();
    raiz->lista_chaves = insere_inicio_listad(raiz->lista_chaves, (void *)ch);
    raiz->qtd_chaves = 1;
    raiz->folha = 0;
    raiz->pai = NULL;
    no1->pai = raiz;
    no2->pai = raiz;
    set_filho(raiz->lista_chaves->ini, no1);
    set_filho(raiz->lista_chaves->ini->prox, no2);
    return raiz;
}

// imprime a arvore
void imprime_arvoreb(Arvoreb *tree)
{
    if (tree->raiz != NULL)
    {
        imprime_nob(tree->raiz);
    }
}

// imprime o nó
void imprime_nob(Nob *no)
{
    Nod *aux = no->lista_chaves->ini;
    while (aux->prox != NULL)
    {
        printf("%d ", get_valor_chave(aux));
        aux = aux->prox;
    }
    printf("%d ", get_valor_chave(aux));
    printf(" | ");
    if (no->folha == 0)
    {
        aux = no->lista_chaves->ini;
        while (aux->prox != NULL)
        {
            imprime_nob(get_filho(aux));
            aux = aux->prox;
        }
        imprime_nob(get_filho(aux));
    }
}

// ---------------------------------------- // MAIN // ---------------------------------------- //

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
            84, 99, 105, 110};

    int i = 0;
    int tam = 34;
    tree = cria_arvoreb(4);

    // for para inserir os elementos na arvore
    for (i = 0; i < tam; i++)
    {
        tree = insercao_arvoreb(tree, vet[i]);
    }

    // imprime a arvore
    imprime_arvoreb(tree);

    // tree=libera_arvoreb(tree);

    return 0;
}