#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

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

// --------------------------// FILA // --------------------------//
typedef Listad Fila;

Fila *cria_fila();

Fila *enqueue(Fila *f, void *elemento);
void *dequeue(Fila *f);
int eh_vazia_fila(Fila *f);

Fila *cria_fila()
{
    return cria_listad();
}

Fila *enqueue(Fila *f, void *elemento)
{
    return insere_fim_listad(f, elemento);
}

void *dequeue(Fila *f)
{
    return remove_inicio_listad(f);
}

int eh_vazia_fila(Fila *f)
{
    return eh_vazia_listad(f);
}

// --------------------------// FILA // --------------------------//

// -------------------------// LISTA DUPLAMENTE ENCADEADA // -------------------------//

/*
para testar a lista generica com inteiros

   L = insere_inicio_listad(L, cria_inteiro(5));
*/
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

// -------------------------// LISTA DUPLAMENTE ENCADEADA // -------------------------//

// -------------------------// ARVORE B // -------------------------//

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
    void *ch;

    while (aux->prox != NULL && chave_nova->valor_chave > get_valor_chave(aux))
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
        {
            ch = remove_fim_listad(lista_nos);
            lista_nos = insere_fim_listad(lista_nos, (void *)chave_nova);
            lista_nos = insere_fim_listad(lista_nos, ch);
        }
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
        tree->raiz = cria_nob();
        tree->raiz->lista_chaves = insere_primeira_chave(tree->raiz->lista_chaves, (void *)ch);
        tree->raiz->qtd_chaves++;
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
                ch = remove_ultima_chave(folha);
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

Chave *remove_ultima_chave(Nob *folha)
{
    void *ch = remove_fim_listad(folha->lista_chaves);
    Chave *ult = (Chave *)remove_fim_listad(folha->lista_chaves);
    folha->lista_chaves = insere_fim_listad(folha->lista_chaves, ch);
    return ult;
}

Listad *insere_primeira_chave(Listad *L, void *ch)
{
    L = insere_inicio_listad(L, ch);
    L = insere_fim_listad(L, (void *)cria_chave(-1));
    return L;
}

Nob *localiza_folha(Arvoreb *tree, int chave)
{
    Nob *aux = tree->raiz;

    while (aux != NULL && aux->folha == 0) // nao for folha
    {
        Nod *aux_lista = aux->lista_chaves->ini;
        while (aux_lista->prox != NULL &&
               chave > get_valor_chave(aux_lista)) // para em cima do -1
        {
            aux_lista = aux_lista->prox;
        }
        aux = get_filho(aux_lista); //((Chave*)aux_lista->info)->filho;
    }
    return aux;
}
Chave *get_ultima_chave(Nob *aux)
{
    return ((Chave *)aux->lista_chaves->fim->ant->info);
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
        set_filho(aux, novo);
    }

    return novo;
}

Nob *cria_nova_raiz(Chave *chave_a_subir, Nob *no_insercao, Nob *novo)
{
    Nob *nova_raiz = cria_nob();

    nova_raiz->folha = 0;
    nova_raiz->lista_chaves = insere_primeira_chave(nova_raiz->lista_chaves, chave_a_subir);
    nova_raiz->pai = NULL;
    nova_raiz->qtd_chaves = 1;
    set_filho(nova_raiz->lista_chaves->fim, novo);
    chave_a_subir->filho = no_insercao;
    novo->pai = nova_raiz;
    no_insercao->pai = nova_raiz;
    return nova_raiz;
}

Nob *libera_nob(Nob *raiz)
{
    Nod *aux;
    if (raiz != NULL)
    {
        aux = raiz->lista_chaves->ini;
        while (aux != NULL)
        {
            ((Chave *)aux->info)->filho = libera_nob(((Chave *)aux->info)->filho);
            aux = aux->prox;
        }

        free(raiz);
    }
    return NULL;
}

Arvoreb *libera_arvoreb(Arvoreb *T)
{
    T->raiz = libera_nob(T->raiz);
    free(T);
    return NULL;
}

void mostra_nob(Nob *raiz, int detalhe)
{
    Listad *l = raiz->lista_chaves;
    Nod *aux = l->ini;

    if (detalhe)
    {

        // pai
        if (raiz->pai == NULL)
            printf("pai: nulo-");
        else
            printf("pai:%d-", ((Chave *)raiz->pai->lista_chaves->ini->info)->valor_chave);

        // se é folha
        printf("(%d)Folha:%d ", raiz->qtd_chaves, raiz->folha);
        // qtde de chaves
    }
    // valores
    printf("[");
    while (aux != NULL)
    {
        // filho
        //   printf("-%p ",((Chave*)aux->info)->filho);

        printf("%d ", ((Chave *)aux->info)->valor_chave);

        aux = aux->prox;
    }
    printf("]");
}

void em_ordem(Nob *raiz)
{
    Nod *aux;
    if (raiz != NULL)
    {
        aux = raiz->lista_chaves->ini;
        while (aux != NULL)
        {
            em_ordem(get_filho(aux));
            printf("%d ", get_valor_chave(aux));
            aux = aux->prox;
        }
    }
}

void percurso_em_nivel_posicionado(Arvoreb *T)
{
    int largura = 250;//pow(2, T->altura)*T->ordem*2;
    Fila *f = cria_fila();
    enqueue(f, (void*)T->raiz);

    em_nivel_posicionado(f,0, largura);
}

void em_nivel_posicionado(Fila *f, int nivel, int largura_tela)
{
    Fila *f_nova = cria_fila();
    Nob *auxb=NULL;
    Nod *aux=NULL;
    int nro_elementos = pow(2, nivel);
    int intervalo = largura_tela /(nro_elementos+1);
    int x = 3;
    while (eh_vazia_fila(f) != 1)
    {
        auxb = (Nob*)dequeue(f);

        gotoxy(intervalo+x, nivel+1);
        mostra_nob(auxb,1);

      //  if (auxb != NULL)
        {
            aux = auxb->lista_chaves->ini;
            while(aux != NULL)
            {
                if (((Chave*)aux->info)->filho != NULL)
                    enqueue(f_nova, (void*)((Chave*)aux->info)->filho);
                aux=aux->prox;
            }
        }
        x = x+intervalo;
    }
    printf ("\n");
    if(!eh_vazia_fila(f_nova))
        em_nivel_posicionado(f_nova, nivel+1,largura_tela);
}

// Função gotoxy
void gotoxy(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// -------------------------// ARVORE B // -------------------------//

// -------------------------// ARVORE B+ // -------------------------//
typedef struct registro
{
    int valor;
} Registro;

// Node
typedef struct node
{
    void **ponteiro;
    int *chave;
    struct node *pai;
    int eh_folha;
    int num_chave;
    struct node *prox;
} Node;

void inserir_fila(Node *new_node);
Node *desenfileirar(void);

int caminhoFolha(Node *const raiz, Node *filho);

void printArvore(Node *const raiz);
Node *encontrarFolha(Node *const raiz, int chave, int verbose);
Registro *encontrar(Node *raiz, int chave, int verbose, Node **fora_folha);
int cut(int length);

Registro *criarRegistro(int valor);
Node *criaNode(void);
Node *criaFolha(void);
int getIndiceEsquerda(Node *pai, Node *esquerda);
Node *inserirFolha(Node *folha, int chave, Registro *ponteiro);
Node *inserirFolhaAposDivisao(Node *raiz, Node *folha, int chave, Registro *ponteiro);
Node *inserirNode(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita);
Node *inserirNodeAposDivisao(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita);
Node *inserirPai(Node *raiz, Node *esquerda, int chave, Node *direita);
Node *inserirNovaRaiz(Node *esquerda, int chave, Node *direita);
Node *iniciarNovaArvore(int chave, Registro *ponteiro);
Node *inserir(Node *raiz, int chave, int valor);

#define ORDER 3
Node *queue = NULL;

void inserir_fila(Node *novo_no)
{
    Node *c;
    if (queue == NULL)
    {
        queue = novo_no;
        queue->prox = NULL;
    }
    else
    {
        c = queue;
        while (c->prox != NULL)
        {
            c = c->prox;
        }
        c->prox = novo_no;
        novo_no->prox = NULL;
    }
}

Node *desenfileirar(void)
{
    Node *n = queue;
    queue = queue->prox;
    n->prox = NULL;
    return n;
}

int caminhoFolha(Node *const raiz, Node *filho)
{
    int tamanho = 0;
    Node *c = filho;
    while (c != raiz)
    {
        c = c->pai;
        tamanho++;
    }
    return tamanho;
}

void printArvore(Node *const raiz)
{

    Node *n = NULL;
    int i = 0;
    int ranque = 0;
    int novo_ranque = 0;

    if (raiz == NULL)
    {
        printf("Arvore vazia\n");
        return;
    }

    queue = NULL;
    inserir_fila(raiz);

    while (queue != NULL)
    {
        n = desenfileirar();
        if (n->pai != NULL && n == n->pai->ponteiro[0])
        {
            novo_ranque = caminhoFolha(raiz, n);
            if (novo_ranque != ranque)
            {
                ranque = novo_ranque;
                printf("\n");
            }
        }
        for (i = 0; i < n->num_chave; i++)
        {
            printf("%d ", n->chave[i]);
        }
        if (!n->eh_folha == 1)
        {
            for (i = 0; i <= n->num_chave; i++)
            {
                inserir_fila(n->ponteiro[i]);
            }
        }
        printf("| ");
    }
    printf("\n");
}

Node *encontrarFolha(Node *const raiz, int chave, int verbose)
{

    if (raiz == NULL)
    {

        if (verbose == 1)
        {
            printf("Arvore vazia.\n");
        }

        return raiz;
    }

    int i = 0;
    Node *c = raiz;

    while (!c->eh_folha)
    {
        if (verbose == 1)
        {
            printf("[");
            for (i = 0; i < c->num_chave - 1; i++)
            {
                printf("%d ", c->chave[i]);
            }
            printf("%d] ", c->chave[i]);
        }

        i = 0;
        while (i < c->num_chave)
        {
            if (chave >= c->chave[i])
            {
                i++;
            }
            else
            {
                break;
            }
        }

        if (verbose == 1)
        {
            printf("%d ->\n", i);
        }

        c = (Node *)c->ponteiro[i];
    }

    if (verbose == 1)
    {
        printf("Folha [");
        for (i = 0; i < c->num_chave - 1; i++)
        {
            printf("%d ", c->chave[i]);
        }
        printf("%d] ->\n", c->chave[i]);
    }

    return c;
}

Registro *encontrar(Node *raiz, int chave, int verbose, Node **fora_folha)
{

    if (raiz == NULL)
    {
        if (fora_folha != NULL)
        {
            *fora_folha = NULL;
        }
        return NULL;
    }

    int i = 0;
    Node *folha = NULL;

    folha = encontrarFolha(raiz, chave, verbose);

    for (i = 0; i < folha->num_chave; i++)
    {
        if (folha->chave[i] == chave)
        {
            break;
        }
    }

    if (fora_folha != NULL)
    {
        *fora_folha = folha;
    }

    if (i == folha->num_chave)
    {
        return NULL;
    }
    else
    {
        return (Registro *)folha->ponteiro[i];
    }
}

int cut(int length)
{

    if (length % 2 == 0)
    {
        return (length / 2);
    }
    else
    {
        return (length / 2 + 1);
    }
}

Registro *criarRegistro(int valor)
{
    Registro *novo_registro = (Registro *)malloc(sizeof(Registro));
    if (novo_registro == NULL)
    {
        perror("Record creation.");
        exit(EXIT_FAILURE);
    }
    else
    {
        novo_registro->valor = valor;
    }
    return novo_registro;
}

Node *criaNode(void)
{
    Node *novo_node;
    novo_node = malloc(sizeof(Node));
    if (novo_node == NULL)
    {
        perror("Node creation.");
        exit(EXIT_FAILURE);
    }
    novo_node->chave = malloc((ORDER - 1) * sizeof(int));
    if (novo_node->chave == NULL)
    {
        perror("New node keys array.");
        exit(EXIT_FAILURE);
    }
    novo_node->ponteiro = malloc(ORDER * sizeof(void *));
    if (novo_node->ponteiro == NULL)
    {
        perror("New node pointers array.");
        exit(EXIT_FAILURE);
    }
    novo_node->eh_folha = 0;
    novo_node->num_chave = 0;
    novo_node->pai = NULL;
    novo_node->prox = NULL;
    return novo_node;
}

Node *criaFolha(void)
{
    Node *folha = criaNode();
    folha->eh_folha = 1;
    return folha;
}

int getIndiceEsquerda(Node *pai, Node *esquerda)
{
    int indice_esquerda = 0;
    while (indice_esquerda <= pai->num_chave && pai->ponteiro[indice_esquerda] != esquerda)
        indice_esquerda++;
    return indice_esquerda;
}

Node *inserirFolha(Node *folha, int chave, Registro *ponteiro)
{
    int i, inserir_ponto;

    inserir_ponto = 0;
    while (inserir_ponto < folha->num_chave && folha->chave[inserir_ponto] < chave)
        inserir_ponto++;

    for (i = folha->num_chave; i > inserir_ponto; i--)
    {
        folha->chave[i] = folha->chave[i - 1];
        folha->ponteiro[i] = folha->ponteiro[i - 1];
    }
    folha->chave[inserir_ponto] = chave;
    folha->ponteiro[inserir_ponto] = ponteiro;
    folha->num_chave++;
    return folha;
}

Node *inserirFolhaAposDivisao(Node *raiz, Node *folha, int chave, Registro *ponteiro)
{

    Node *nova_folha;
    int *temp_chave;
    void **temp_ponteiros;
    int indice_insercao, dividir, nova_chave, i, j;

    nova_folha = criaFolha();

    temp_chave = malloc(ORDER * sizeof(int));

    if (temp_chave == NULL)
    {
        perror("Temporary keys array");
        exit(EXIT_FAILURE);
    }

    temp_ponteiros = malloc(ORDER * sizeof(void *));

    if (temp_ponteiros == NULL)
    {
        perror("Temporary pointers array.");
        exit(EXIT_FAILURE);
    }

    indice_insercao = 0;
    while (indice_insercao < ORDER - 1 && folha->chave[indice_insercao] < chave)
    {
        indice_insercao++;
    }

    for (i = 0, j = 0; i < folha->num_chave; i++, j++)
    {
        if (j == indice_insercao)
        {
            j++;
        }

        temp_chave[j] = folha->chave[i];
        temp_ponteiros[j] = folha->ponteiro[i];
    }

    temp_chave[indice_insercao] = chave;
    temp_ponteiros[indice_insercao] = ponteiro;

    folha->num_chave = 0;

    dividir = cut(ORDER - 1);

    for (i = 0; i < dividir; i++)
    {
        folha->ponteiro[i] = temp_ponteiros[i];
        folha->chave[i] = temp_chave[i];
        folha->num_chave++;
    }

    for (i = dividir, j = 0; i < ORDER; i++, j++)
    {
        nova_folha->ponteiro[j] = temp_ponteiros[i];
        nova_folha->chave[j] = temp_chave[i];
        nova_folha->num_chave++;
    }

    free(temp_ponteiros);
    free(temp_chave);

    nova_folha->ponteiro[ORDER - 1] = folha->ponteiro[ORDER - 1];
    folha->ponteiro[ORDER - 1] = nova_folha;

    for (i = folha->num_chave; i < ORDER - 1; i++)
    {
        folha->ponteiro[i] = NULL;
    }
    for (i = nova_folha->num_chave; i < ORDER - 1; i++)
    {
        nova_folha->ponteiro[i] = NULL;
    }

    nova_folha->pai = folha->pai;
    nova_chave = nova_folha->chave[0];

    return inserirPai(raiz, folha, nova_chave, nova_folha);
}

Node *inserirNode(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita)
{

    int i;

    for (i = pai->num_chave; i > indice_esquerda; i--)
    {
        pai->ponteiro[i + 1] = pai->ponteiro[i];
        pai->chave[i] = pai->chave[i - 1];
    }

    pai->ponteiro[indice_esquerda + 1] = direita;
    pai->chave[indice_esquerda] = chave;
    pai->num_chave++;
    return raiz;
}

Node *inserirNodeAposDivisao(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita)
{

    int i, j, dividir, k;
    Node *novo_node, *filho;
    int *temp_chave;
    Node **temp_ponteiro;

    temp_ponteiro = malloc((ORDER + 1) * sizeof(Node *));

    if (temp_ponteiro == NULL)
    {
        exit(EXIT_FAILURE);
    }

    temp_chave = malloc(ORDER * sizeof(int));

    if (temp_chave == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (i = 0, j = 0; i < pai->num_chave + 1; i++, j++)
    {
        if (j == indice_esquerda + 1)
        {
            j++;
        }
        temp_ponteiro[j] = pai->ponteiro[i];
    }

    for (i = 0, j = 0; i < pai->num_chave; i++, j++)
    {
        if (j == indice_esquerda)
        {
            j++;
        }

        temp_chave[j] = pai->chave[i];
    }

    temp_ponteiro[indice_esquerda + 1] = direita;
    temp_chave[indice_esquerda] = chave;

    dividir = cut(ORDER);
    novo_node = criaNode();
    pai->num_chave = 0;

    for (i = 0; i < dividir - 1; i++)
    {

        pai->ponteiro[i] = temp_ponteiro[i];
        pai->chave[i] = temp_chave[i];
        pai->num_chave++;
    }

    pai->ponteiro[i] = temp_ponteiro[i];
    k = temp_chave[dividir - 1];

    for (++i, j = 0; i < ORDER; i++, j++)
    {
        novo_node->ponteiro[j] = temp_ponteiro[i];
        novo_node->chave[j] = temp_chave[i];
        novo_node->num_chave++;
    }

    novo_node->ponteiro[j] = temp_ponteiro[i];

    free(temp_ponteiro);
    free(temp_chave);

    novo_node->pai = pai->pai;

    for (i = 0; i <= novo_node->num_chave; i++)
    {

        filho = novo_node->ponteiro[i];
        filho->pai = novo_node;
    }

    return inserirPai(raiz, pai, k, novo_node);
}

Node *inserirPai(Node *raiz, Node *esquerda, int chave, Node *direita)
{

    int indice_esquerda;
    Node *pai;

    pai = esquerda->pai;

    if (pai == NULL)
    {
        return inserirNovaRaiz(esquerda, chave, direita);
    }

    indice_esquerda = getIndiceEsquerda(pai, esquerda);

    if (pai->num_chave < ORDER - 1)
    {
        return inserirNode(raiz, pai, indice_esquerda, chave, direita);
    }

    return inserirNodeAposDivisao(raiz, pai, indice_esquerda, chave, direita);
}

Node *inserirNovaRaiz(Node *esquerda, int chave, Node *direita)
{

    Node *raiz = criaNode();
    raiz->chave[0] = chave;
    raiz->ponteiro[0] = esquerda;
    raiz->ponteiro[1] = direita;
    raiz->num_chave++;
    raiz->pai = NULL;
    esquerda->pai = raiz;
    direita->pai = raiz;
    return raiz;
}

Node *iniciarNovaArvore(int chave, Registro *ponteiro)
{

    Node *raiz = criaFolha();
    raiz->chave[0] = chave;
    raiz->ponteiro[0] = ponteiro;
    raiz->ponteiro[ORDER - 1] = NULL;
    raiz->pai = NULL;
    raiz->num_chave++;
    return raiz;
}

Node *inserir(Node *raiz, int chave, int valor)
{

    Registro *registo_ponteiro = NULL;
    Node *folha = NULL;

    registo_ponteiro = encontrar(raiz, chave, 0, NULL);
    if (registo_ponteiro != NULL)
    {
        registo_ponteiro->valor = valor;
        return raiz;
    }

    registo_ponteiro = criarRegistro(valor);

    if (raiz == NULL)
    {
        return iniciarNovaArvore(chave, registo_ponteiro);
    }

    folha = encontrarFolha(raiz, chave, 0);

    if (folha->num_chave < ORDER - 1)
    {
        folha = inserirFolha(folha, chave, registo_ponteiro);
        return raiz;
    }

    return inserirFolhaAposDivisao(raiz, folha, chave, registo_ponteiro);
}

// -------------------------// ARVORE B+ // -------------------------//


int main()
{
    Node *raiz;

    raiz = NULL;

    raiz = inserir(raiz, 5, 33);
    raiz = inserir(raiz, 15, 21);
    raiz = inserir(raiz, 25, 31);
    raiz = inserir(raiz, 25, 41);
    raiz = inserir(raiz, 45, 10);

    printArvore(raiz);

    return 0;
}
