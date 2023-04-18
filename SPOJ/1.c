# include <stdlib.h>
# include <stdio.h>

//arvore binaria generica (sqn)
typedef struct no{
    int info;
    struct no *esquerda;
    struct no *direita;
}No;

typedef struct arvore{
    No *raiz;
}Arvore;

No* cria_no(No* raiz, int info)
{

    raiz=(No*)malloc(sizeof(No));
    raiz->info = info;
    raiz->esquerda = NULL;
    raiz->direita = NULL;

    return raiz;
}

No* abb_insere(No* raiz, int info)
{
    if(raiz==NULL)
    {
        raiz=cria_no(raiz,info);
    
    }
    else
    {
        if(info<raiz->info)
        {
            raiz->esquerda=abb_insere(raiz->esquerda,info);
        }
        else
        {
            raiz->direita=abb_insere(raiz->direita,info);
        }
    }
    return raiz;
}

void pos_ordem (No *raiz)
{
    if (raiz != NULL){
        pos_ordem (raiz->esquerda);
        pos_ordem (raiz->direita);
        printf("%d;", raiz->info);
    }
}

// exibir em ordem
void em_ordem (No *raiz){
    if (raiz != NULL){
        em_ordem (raiz->esquerda);
        printf("%d;", raiz->info);
        em_ordem (raiz->direita);
    }
}

// apagar arvore
void apagar_arvore(No *raiz){
    if(raiz != NULL)
    {
        apagar_arvore(raiz->esquerda);
        apagar_arvore(raiz->direita);
        free(raiz);
    }
}

// ------------------------ FILA DUPLAMENTE ENCADEADA -----------------------------
// implementação de uma lista dupla generica
typedef struct node {
    void *data;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
    int size;
} list;

// cria uma lista vazia
list *create_list() {
    list *l = (list *) malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

// insere um elemento no final da lista
void insert(list *l, void *data) {
    node *n = (node *) malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
    l->size++;
}

// remove um elemento da lista
int remove_element(list *l, void *data) {
    node *n = l->head;
    node *prev = NULL;
    while (n != NULL) {
        if (n->data == data) {
            if (prev == NULL) {
                l->head = n->next;
            } else {
                prev->next = n->next;
            }
            if (n == l->tail) {
                l->tail = prev;
            }
            free(n);
            l->size--;
            return 1;
        }
        prev = n;
        n = n->next;
    }
    return 0;
}

// retorna o tamanho da lista
int size(list *l) {
    return l->size;
}

// retorna o elemento na posição index
void *get(list *l, int index) {
    node *n = l->head;
    int i = 0;
    while (n != NULL) {
        if (i == index) {
            return n->data;
        }
        n = n->next;
        i++;
    }
    return NULL;
}

// retorna o indice do elemento data
int index_of(list *l, void *data) {
    node *n = l->head;
    int i = 0;
    while (n != NULL) {
        if (n->data == data) {
            return i;
        }
        n = n->next;
        i++;
    }
    return -1;
}

// retorna 1 se a lista contem o elemento data
int contains(list *l, void *data) {
    return index_of(l, data) != -1;
}

// retorna 1 se a lista está vazia
int is_empty(list *l) {
    return l->head == NULL;
}

// libera a memória alocada pela lista
void free_list(list *l) {
    node *n = l->head;
    while (n != NULL) {
        node *next = n->next;
        free(n);
        n = next;
    }
    free(l);
}


// em ordem ITERATIVO
void em_ordem_iterativo(No *raiz){
    list *pilha = create_list(); // lista
    No *aux = raiz;                             // auxiliar para percorrer a arvore
    while (aux != NULL || !is_empty(pilha)){    // enquanto a arvore não for vazia ou a pilha não for vazia
        while (aux != NULL){                    // enquanto a arvore não for vazia
            insert(pilha, aux);                 // insere na pilha
            aux = aux->esquerda;                // vai para a esquerda
        }
        aux = get(pilha, size(pilha)-1);        // pega o ultimo elemento da pilha, usando o size para pegar o ultimo e o -1 para pegar o ultimo elemento, usando o get como se fosse um vetor
        remove_element(pilha, aux);             // remove o elemento da pilha
        printf("%d;", aux->info);
        aux = aux->direita;                     // reseta o aux para a direita
    }
}

// em ordem iterativo que retorna uma lista
list *em_ordem_iterativo_lista(No *raiz){
    list *pilha = create_list(); // lista
    list *lista = create_list(); // lista
    No *aux = raiz;                             // auxiliar para percorrer a arvore
    while (aux != NULL || !is_empty(pilha)){    // enquanto a arvore não for vazia ou a pilha não for vazia
        while (aux != NULL){                    // enquanto a arvore não for vazia
            insert(pilha, aux);                 // insere na pilha
            aux = aux->esquerda;                // vai para a esquerda
        }
        aux = get(pilha, size(pilha)-1);        // pega o ultimo elemento da pilha, usando o size para pegar o ultimo e o -1 para pegar o ultimo elemento, usando o get como se fosse um vetor
        remove_element(pilha, aux);             // remove o elemento da pilha
        insert(lista, &aux->info);
        aux = aux->direita;                     // reseta o aux para a direita
    }
    return lista;
}

// arvore para lista de forma ITERATIVA
void arvore_para_lista_iterativo(No *raiz, list *list){
    No *aux = raiz;
    while (aux != NULL || !is_empty(list)){
        while (aux != NULL){
            insert(list, aux);
            aux = aux->esquerda;
        }
        aux = get(list, size(list)-1);
        remove_element(list, aux);
        insert(list, &aux->info);
        aux = aux->direita;
    }
}


// função que converte a arvore binaria em uma lista
void arvore_para_lista(No *raiz, list *list){
    if (raiz != NULL){
        arvore_para_lista (raiz->esquerda, list);
        insert(list, &raiz->info);
        arvore_para_lista (raiz->direita, list);
    }
}

int main(){
    //  lista de inteiros
    list *lista = create_list();
    // arvore binaria com 10 elementos
    Arvore *arvore = (Arvore*)malloc(sizeof(Arvore));

    arvore->raiz = NULL;
/*     for (int i=0; i<10; i++){
        arvore->raiz = abb_insere(arvore->raiz, i);
    }
 */

/*     arvore->raiz = abb_insere(arvore->raiz, 10);
    arvore->raiz = abb_insere(arvore->raiz, 5);
    arvore->raiz = abb_insere(arvore->raiz, 15);
    arvore->raiz = abb_insere(arvore->raiz, 3);
    arvore->raiz = abb_insere(arvore->raiz, 7);
    arvore->raiz = abb_insere(arvore->raiz, 12);
    arvore->raiz = abb_insere(arvore->raiz, 18);
    arvore->raiz = abb_insere(arvore->raiz, 1);
    arvore->raiz = abb_insere(arvore->raiz, 4);
    arvore->raiz = abb_insere(arvore->raiz, 6); */

    arvore->raiz = abb_insere(arvore->raiz, 6);
    arvore->raiz = abb_insere(arvore->raiz, 2);
    arvore->raiz = abb_insere(arvore->raiz, 3);
    arvore->raiz = abb_insere(arvore->raiz, 50);
    arvore->raiz = abb_insere(arvore->raiz, 5);
    arvore->raiz = abb_insere(arvore->raiz, 7);
    arvore->raiz = abb_insere(arvore->raiz, 8);

    // 10,5,15,3,7,12,18,1,4,6
/*     // exibir em ordem RECURSIVO
    printf(" \n");
    em_ordem(arvore->raiz);
    printf(" \n"); */

    // exibir em ordem ITERATIVO
    printf(" \n");
    em_ordem_iterativo(arvore->raiz);
    printf(" \n");

    // exibir em ordem ITERATIVO que retorna uma lista
    lista = em_ordem_iterativo_lista(arvore->raiz);

    // CONVERTER ARVORE PARA LISTA ITERATIVO
    //arvore_para_lista_iterativo(arvore->raiz, lista);

    // converter arvore para lista RECURSIVA
    //arvore_para_lista(arvore->raiz, lista);

    
    // exibir A lista
    for (int i=0; i<lista->size; i++){
        printf("%d ", *(int *)get(lista, i));
    }

    // apagar arvore
    apagar_arvore(arvore->raiz);
    free(arvore);

    // apagar lista
    free_list(lista);



    return 0;
}
