#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
    void* info;
    struct nod *ant;
    struct nod *prox;
}Nod;

typedef struct listad{
        Nod *ini;
        Nod *fim;
        
} Listad;

typedef struct nob{
    int folha; //1 se for folha, 0 caso contrario
    int qtd_chaves;
    struct nob* pai;
    Listad *lista_chaves;
}Nob;

typedef struct chave{
    int valor_chave;
    Nob *filho;
} Chave;

typedef struct arvoreb{
    Nob *raiz;
    int ordem;
    int altura;
}Arvoreb;

// ----------------------------------------------------- LISTA DUPLA -----------------------------------------------------

Listad* cria_listad(){
    Listad* novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod* cria_nod(void* valor){
    Nod* novo = (Nod*)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}


Listad* insere_inicio_listad(Listad *L, void* valor){
    Nod *novo= cria_nod(valor);

    if (L == NULL){
        L = cria_listad();
        L->ini = L->fim = novo;

    }
    else{
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


Listad* insere_fim_listad(Listad* L, void* valor){
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



void* remove_inicio_listad(Listad *L){
    Nod* aux;
    void* resposta = NULL;//quando nao tem nada pra remover
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

void* remove_fim_listad(Listad *L){
    Nod* aux;
    void* resposta = NULL;

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

Listad* libera_listad(Listad *L){
    Nod *aux = L->ini;

    while (aux != NULL){
        L->ini = L->ini->prox;
        free(aux);
        aux = L->ini;
    }

    free(L);
    return NULL;
}

int eh_vazia_listad(Listad *L){
    if (L == NULL || L->ini == NULL)
        return 1;
    else
        return 0;
}

int tamanho_listad(Listad *L){
    Nod *aux = L->ini;
    int cont = 0;

    while (aux != NULL)
    {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

// funcao que imprime uma lista duplamente encadeada
void imprime_listad(Listad *L){
    Nod *aux = L->ini;

    while (aux != NULL){
        printf("%d ", *(int*)aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

// funcao que recebe uma lista , divide ela no meio e retorna a segunda metade
Listad* divide_listad(Listad *L){
    Listad *nova = cria_listad();
    Nod *aux = L->ini;
    int i, tam = tamanho_listad(L);
    

    for (i=0; i<tam/2; i++)
        aux = aux->prox;

    nova->ini = aux;        // atualiza o inicio da nova lista
    nova->fim = L->fim;     // atualiza o fim da nova lista
    
    L->fim = aux->ant;      // atualiza o fim da lista antiga
    L->fim->prox = NULL;    // atualiza o proximo do ultimo elemento da lista antiga
    aux->ant = NULL;        // redundante

    return nova;
}

// divide a lista sem usar o tamanho da lista
Listad* divide_lista2(Listad *L, int n){
    Listad *nova = cria_listad();
    Nod *aux = L->ini;
    int i;

    for (i=0; i<n; i++)
        aux = aux->prox;

    nova->ini = aux;        // atualiza o inicio da nova lista
    nova->fim = L->fim;     // atualiza o fim da nova lista
    
    L->fim = aux->ant;      // atualiza o fim da lista antiga
    L->fim->prox = NULL;    // atualiza o proximo do ultimo elemento da lista antiga
    aux->ant = NULL;        // redundante

    return nova;
    
}

// backup
/* Listad* insere_ordem_listad(Listad *L, void* valor){
    Nod *novo = cria_nod(valor);
    Nod *aux = L->ini;
    //(int*)aux->info = 0;
    //(chave*)aux->info = 0;
    Chave *chave = (Chave*)novo->info;

    // caso a lista esteja vazia
    if (L == NULL){
        L = cria_listad();
        L->ini = L->fim = novo;
    }

    // caso a lista nao esteja vazia
    else{

        // caso a lista tenha apenas um elemento
        if (L->ini == NULL)
            L->ini = L->fim = novo;

        // caso a lista tenha mais de um elemento
        else{
            // percorre a lista ate encontrar o elemento maior que o novo
            while (aux != NULL && *(int*)aux->info < *(int*)novo->info)
                aux = aux->prox;
            // caso o novo elemento seja o menor da lista
            if (aux == NULL){
                novo->ant = L->fim;
                L->fim->prox = novo;
                L->fim = novo;
            }
            // caso o novo elemento nao seja o menor da lista
            else{
                // caso o novo elemento seja o maior da lista
                if (aux->ant == NULL){
                    novo->prox = L->ini;
                    L->ini->ant = novo;
                    L->ini = novo;
                }
                // caso o novo elemento nao seja o maior da lista
                else{
                    novo->ant = aux->ant;
                    novo->prox = aux;
                    aux->ant->prox = novo;
                    aux->ant = novo;
                }
            }
        }
    }
    return L;
} */

// funcao que insere na lista em ordem
Listad* insere_ordem_listad(Listad* L, void* valor) {
    Nod* novo = cria_nod(valor);

    // caso a lista esteja vazia
    if (L == NULL) {
        L = cria_listad();
        L->ini = L->fim = novo;
        return L;
    }

    Nod* aux = L->ini;

    // caso a lista nao esteja vazia
    if (aux == NULL) {
        // caso a lista tenha apenas um elemento
        L->ini = L->fim = novo;
    } else {
        // caso a lista tenha mais de um elemento
        // percorre a lista ate encontrar o elemento maior que o novo
        //while (aux != NULL && *(int*)aux->info < *(int*)novo->info)
        while (aux != NULL && ((Chave*)aux->info)->valor_chave < ((Chave*)novo->info)->valor_chave)
            aux = aux->prox;
        // caso o novo elemento seja o menor da lista
        if (aux == NULL) {
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        } else {
            // caso o novo elemento nao seja o menor da lista
            if (aux->ant == NULL) {
                // caso o novo elemento seja o maior da lista
                novo->prox = L->ini;
                L->ini->ant = novo;
                L->ini = novo;
            } else {
                // caso o novo elemento nao seja o maior da lista
                novo->ant = aux->ant;
                novo->prox = aux;
                aux->ant->prox = novo;
                aux->ant = novo;
            }
        }
    }
    return L;
}

//
int get_valor_chave(Nod* aux){
    Chave *chave = (Chave*)aux->info;
    return chave->valor_chave;
}
// ----------------------------------------------------- ARVORE B -----------------------------------------------------
Arvoreb* cria_arvoreb(int ordem){
    Arvoreb *nova=(Arvoreb*)malloc(sizeof(Arvoreb));

    nova->raiz = NULL;
    nova->ordem = ordem;
    nova->altura = 0;
    return nova;
}

Nob* cria_nob(){
    Nob *novo=(Nob*)malloc(sizeof(Nob)), novo2;

    novo->folha = 1;
    novo->pai = NULL;
    novo->qtd_chaves = 0;
    novo->lista_chaves = cria_listad();
   
    return novo;
}

// funcao que insere na arvore
// funcao que insere uma chave na arvore
// insere_arvoreb(tree,vet[i])
void insere_arvoreb(Arvoreb *tree, int valor){
    Nob *raiz = tree->raiz;
    // caso a arvore esteja vazia
    if (raiz == NULL){
        raiz = cria_nob();
        raiz->folha = 1;
        raiz->pai = NULL;
        raiz->qtd_chaves = 1;
        Chave *chave = (Chave*)malloc(sizeof(Chave));
        chave->valor_chave = valor;
        chave->ponteiro = NULL;
        insere_ordem_listad(raiz->lista_chaves, chave);
        tree->raiz = raiz;
    }
    // caso a arvore nao esteja vazia
    else{
        // caso a raiz nao esteja cheia
        if (raiz->qtd_chaves < tree->ordem-1){
            Chave *chave = (Chave*)malloc(sizeof(Chave));
            chave->valor_chave = valor;
            chave->filho = NULL;
            insere_ordem_listad(raiz->lista_chaves, chave);
            raiz->qtd_chaves++;
        }
        // caso a raiz esteja cheia
        else{
            Nob *nova_raiz = cria_nob();
            nova_raiz->folha = 0;
            nova_raiz->pai = NULL;
            nova_raiz->qtd_chaves = 0;
            nova_raiz->lista_chaves = cria_listad();
            nova_raiz->filhos[0] = raiz;
            raiz->pai = nova_raiz;
            tree->raiz = nova_raiz;
            split_nob(tree, nova_raiz, 0);
            insere_nao_cheio(tree, nova_raiz, valor);
        }
    }
}

// libera_nob
void libera_nob(Nob *no){
    if (no != NULL){
        libera_listad(no->lista_chaves);
        free(no);
    }
}

// liberar a arvore
void libera_arvoreb(Arvoreb *tree){
    if (tree != NULL){
        libera_nob(tree->raiz);
        free(tree);
    }
}


// ----------------------------------------------------

Arvoreb* cria_arvoreb(int ordem);
Nob* cria_nob();


int main(){
    Arvoreb *tree;

    int vet[] ={
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

    for (i=0; i<tam; i++){
        tree=insere_arvoreb(tree,vet[i]);
    }


    // limpar a arvore
    libera_arvoreb(tree);

/*     
    // criar a lista
    Listad *lista = cria_listad();

    // loop for para preencher a lista
    for (i=0; i<7; i++){
        lista = insere_fim_listad(lista, &vet[i]);
    }

    imprime_listad(lista);

    // dividir lista
    //Listad *lista2 = divide_listad(lista);
    Listad *lista2 = divide_lista2(lista, 3);

    // imprimir lista
    imprime_listad(lista);
    imprime_listad(lista2);

    // limpar a lista
    libera_listad(lista); */

    return 0;
}
