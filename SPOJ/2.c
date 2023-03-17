#include <stdio.h>
#include <stdlib.h>

typedef struct noavl{
    int info;
    int fb;
    struct noavl *esq, *dir;
    //struct noavl *pai;
}Noavl;

void libera_avl(Noavl* raiz);
void em_ordem(Noavl* raiz);
Noavl* rotacao_dir_esq(Noavl* candidato);
Noavl* rotacao_esq_dir(Noavl* candidato);
Noavl* rotacao_esq(Noavl* candidato);
Noavl* rotacao_dir(Noavl* candidato);
Noavl* rotacao_geral(Noavl* candidato);
void recalcula_fb(Noavl *candidato,int info);
Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato);
Noavl *insercao_geral(Noavl *tree,int info);
Noavl *cria_noavl(int info);

Noavl *cria_noavl(int info){
    Noavl *novo = (Noavl *)malloc(sizeof(Noavl));
    novo->dir = novo->esq = NULL;
    novo->info = info;
    novo->fb = 0;

    return novo;
}

Noavl *insercao_geral(Noavl *tree,int info){
    Noavl *candidato = NULL;
    Noavl *pai_candidato = NULL;

    if (tree == NULL){
        return cria_noavl(info);
    }
    else{
        candidato = insere_noavl(tree, info, &pai_candidato);
        recalcula_fb(candidato, info);
        if (candidato->fb == -2 || candidato->fb == +2){
            if (candidato == tree)
                tree = rotacao_geral(candidato);
            else 
                if (pai_candidato->esq == candidato)
                pai_candidato->esq = rotacao_geral(candidato);
            else
                pai_candidato->dir = rotacao_geral(candidato);
            }
    }
    return tree;
}

Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato){
    Noavl *aux = tree;
    Noavl *pai_aux = NULL;
    Noavl *novo = cria_noavl(info);
    Noavl *candidato = tree;

    while (aux != NULL){
        if (aux->fb != 0){
            candidato = aux;
            *pai_candidato = pai_aux;
        }

        pai_aux = aux;

        if (info < aux->info)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    if (info < pai_aux->info)
        pai_aux->esq = novo;
    else
        pai_aux->dir = novo;

    return candidato;
}

void recalcula_fb(Noavl *candidato,int info){
    Noavl *aux = candidato;
    while (aux->info != info){
        if (info < aux->info){
            aux->fb++;
            aux = aux->esq;
        }
        else{
            aux->fb--;
            aux = aux->dir;
        }
    }
}
//retorna a nova raiz da subarvore 

Noavl* rotacao_geral(Noavl* candidato){
    Noavl* nova_raiz=NULL;
    if(candidato->fb == +2)
        if (candidato->esq->fb == +1)
            nova_raiz = rotacao_dir(candidato);
        else
            nova_raiz = rotacao_esq_dir(candidato);
    else // fb cand -2
        if(candidato->dir->fb == -1)
            nova_raiz = rotacao_esq(candidato);
        else
            nova_raiz = rotacao_dir_esq(candidato);
    return nova_raiz;
}

Noavl* rotacao_dir(Noavl* candidato){
    Noavl* filho=candidato->esq;
    Noavl* neto=filho->dir;

    filho->dir = candidato;
    candidato->esq = neto;
    //recalculo fb
    candidato->fb = filho->fb = 0;
    
    return filho;
}


Noavl* rotacao_esq(Noavl* candidato){
    Noavl* filho=candidato->dir;
    Noavl* neto=filho->esq;

    filho->esq = candidato;
    candidato->dir = neto;
    candidato->fb = filho->fb = 0;
    
    return filho;
}

Noavl* rotacao_esq_dir(Noavl* candidato){
    Noavl* filho = candidato->esq;
    Noavl* neto = filho->dir;
    candidato->esq = rotacao_esq(candidato->esq);
    Noavl* nova_raiz = rotacao_dir(candidato);
    
    if (neto->fb == 1){
        candidato->fb = -1;
        filho->fb = neto->fb = 0;
    }    
    if (neto->fb == -1){
        candidato->fb = neto->fb = 0;
        filho->fb = 1;
    }
    if(neto->fb == 0)
      candidato->fb =  filho->fb = 0;

    return nova_raiz;
}

Noavl* rotacao_dir_esq(Noavl* candidato){
    Noavl* filho = candidato->dir;
    Noavl* neto = filho->esq;
    candidato->dir = rotacao_dir(candidato->dir);
    Noavl* nova_raiz = rotacao_esq(candidato);

   
    if (neto->fb == 1){
        candidato->fb = -1;
        filho->fb = neto->fb = 0;
    }    
    if (neto->fb == -1){
        candidato->fb = neto->fb = 0;
        filho->fb = 1;
    }
 
    return nova_raiz;
}

void em_ordem(Noavl* raiz){

        if (raiz != NULL){
            em_ordem(raiz->esq);
            printf("%i ", raiz->info);
            em_ordem(raiz->dir);
        }
}

void libera_avl(Noavl* raiz){

        if (raiz != NULL){
            libera_avl(raiz->esq);
            libera_avl(raiz->dir);
            free(raiz);
        }
}



int altura(Noavl *raiz) {
    if (raiz == NULL)
        return -1;
    int h_esq = altura(raiz->esq);
    int h_dir = altura(raiz->dir);
    return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

void imprimir_nivel_fb(Noavl *no, int nivel) {
    if (no == NULL)
        return;
    if (nivel == 0)
        printf("%d ", no->info);
    else {
        imprimir_nivel_fb(no->esq, nivel-1);
        imprimir_nivel_fb(no->dir, nivel-1);
    }
}

void imprimir_fb(Noavl *raiz) {
    int h = altura(raiz);
    for (int i = 0; i <= h; i++) {
        imprimir_nivel_fb(raiz, i);
        printf("\n");
    }
}

// usando queue -------------------------------------

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct queue {
    Node* front;
    Node* rear;
} Queue;


// Inicializa a fila vazia
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Verifica se a fila está vazia
int isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Insere um elemento no final da fila
void enqueue(Queue* q, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Remove um elemento do início da fila
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Erro: fila vazia!\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

// cria uma fila vazia
Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    initQueue(q);
    return q;
}

// retorna o tamanho da fila
int sizeQueue(Queue* q) {
    int size = 0;
    Node* temp = q->front;
    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}

// libera a memória alocada para a fila
void destroyQueue(Queue* q) {
    Node* temp = q->front;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(q);
}

// printa o fb de cada nó da árvore em níveis
void printFB(Noavl* raiz) {
    if (raiz == NULL) {
        return;
    }

    // Cria uma fila para percorrer a árvore em largura
    Queue* fila = createQueue();
    enqueue(fila, raiz->info);

    int nivel_atual = 0;

    // Enquanto a fila não estiver vazia, percorre a árvore em largura
    while (!isEmpty(fila)) {
        int n = sizeQueue(fila);
        printf("Nivel %d: ", nivel_atual);
        Noavl* no_atual = NULL;

        // Percorre todos os nós do nível atual
        for (int i = 0; i < n; i++) {
            no_atual = insercao_geral(no_atual, dequeue(fila));
            printf("%d ", no_atual->info);

            // Adiciona os filhos do nó atual na fila, se eles existirem
            if (no_atual->esq != NULL) {
                enqueue(fila, no_atual->esq->info);
            }
            if (no_atual->dir != NULL) {
                enqueue(fila, no_atual->dir->info);
            }
        }

        printf("\n");
        nivel_atual++;
    }

    // Libera a memória da fila
    destroyQueue(fila);
}





/* POUPT04 - Árvore em nível

Crie um programa que construe uma árvore AVL e exibe seu percurso em ordem de acordo com o modelo de saída a seguir.


Entrada:

Cada linha contem uma chave, números inteiros positivos (0  a 64000), que deve ser inserida na AVL. As linhas estão na ordem em devem ser inseridas na árvore.

A sequencia finaliza com a leitura de -1 (que não faz parte da árvore)

Saida:

Cada linha da saída apresenta o conjunto em ordem crescente de inteiros, que correspondem às chaves de cada nível da árvore criada. Cada linha é finalizada com espaço e fim de linha (" \n"). 

*/

int main(){
    int info;
    Noavl *tree = NULL;

    while(scanf("%d", &info) && info != -1){
        tree = insercao_geral(tree, info);
    }

    // imprimir as linhas e colunas da arvore

/*     for(int i = 0; i <= altura(tree); i++){
        //imprimir_nivel_info(tree, i);
        printFB(tree);
        //printf(" \n");
    } */

    //printFB(tree);

    imprimir_fb(tree);



    libera_avl(tree);




    return 0;
}
