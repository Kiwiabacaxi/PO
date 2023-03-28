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
        free(aux->info);
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

// funcao que insere na lista em ordem
Listad* insere_ordem_listad(Listad *L, void* valor){
    Nod *novo = cria_nod(valor);
    Nod *aux = L->ini;

    if (L == NULL){
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else{
        if (L->ini == NULL)
            L->ini = L->fim = novo;
        else{
            while (aux != NULL && *(int*)aux->info < *(int*)novo->info)
                aux = aux->prox;

            if (aux == NULL){
                novo->ant = L->fim;
                L->fim->prox = novo;
                L->fim = novo;
            }
            else{
                if (aux->ant == NULL){
                    novo->prox = L->ini;
                    L->ini->ant = novo;
                    L->ini = novo;
                }
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

// funcao que insere n

// funcao que insere uma chave na arvore
// insere_arvoreb(tree,vet[i])
Arvoreb* insere_arvoreb(Arvoreb *tree, int chave){
    Nob *raiz = tree->raiz;
    Nob *novo = cria_nob();
    Listad *lista = cria_listad();
    int i, tam;

    if (raiz == NULL){
        insere_fim_listad(novo->lista_chaves, &chave);
        novo->qtd_chaves++;
        tree->raiz = novo;
        tree->altura++;
    }
    else{
        if (raiz->folha == 1){
            insere_fim_listad(raiz->lista_chaves, &chave);
            raiz->qtd_chaves++;
            if (raiz->qtd_chaves == tree->ordem){
                // dividir a raiz
                Nob *novo = cria_nob();
                Listad *lista = divide_listad(raiz->lista_chaves);
                novo->folha = 1;
                novo->qtd_chaves = tamanho_listad(lista);
                novo->lista_chaves = lista;
                novo->pai = raiz->pai;
                raiz->qtd_chaves = tamanho_listad(raiz->lista_chaves);
                raiz->folha = 1;
                raiz->pai = novo;
                insere_fim_listad(novo->lista_chaves, &chave);
                novo->qtd_chaves++;
                tree->raiz = novo;
                tree->altura++;
            }
        }
        else{
            Nob *aux = raiz;
            while (aux->folha != 1){
                tam = tamanho_listad(aux->lista_chaves);
                for (i=0; i<tam; i++){
                    if (chave < *(int*)aux->lista_chaves->ini->info){
                        aux = aux->lista_chaves->ini->info;
                        break;
                    }
                    else if (chave > *(int*)aux->lista_chaves->fim->info){
                        aux = aux->lista_chaves->fim->info;
                        break;
                    }
                    else if (chave > *(int*)aux->lista_chaves->ini->info && chave < *(int*)aux->lista_chaves->fim->info){
                        aux = aux->lista_chaves->ini->prox->info;
                        break;
                    }
                }
            }
            insere_fim_listad(aux->lista_chaves, &chave);
            aux->qtd_chaves++;
            if (aux->qtd_chaves == tree->ordem){
                // dividir o no
                Nob *novo = cria_nob();
                Listad *lista = divide_listad(aux->lista_chaves);
                novo->folha = 1;
                novo->qtd_chaves = tamanho_listad(lista);
                novo->lista_chaves = lista;
                novo->pai = aux->pai;
                aux->qtd_chaves = tamanho_listad(aux->lista_chaves);
                aux->folha = 1;
                aux->pai = novo;
                insere_fim_listad(novo->lista_chaves, &chave);
                novo->qtd_chaves++;
                tree->raiz = novo;
                tree->altura++;
            }
        }
    }
    return tree;
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
    //libera_listad(lista);



    //tree=libera_arvoreb(tree);
    return 0;
}
