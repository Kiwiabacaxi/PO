# include <stdlib.h>
# include <stdio.h>

// implementação de uma lista generica
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
/* void remove(list *l, void *data) {
    node *n = l->head;
    node *prev = NULL;
    while (n != NULL) {
        if (n->data == data) {
            if (prev == NULL) {
                l->head = n->next;
            } else {
                prev->next = n->next;
            }
            if (n->next == NULL) {
                l->tail = prev;
            }
            free(n);
            l->size--;
            return;
        }
        prev = n;
        n = n->next;
    }
} */

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

int main(){

    // criar uma lista de inteiros
    list *l = create_list();
    int a = 10;
    int b = 20;
    int c = 30;
    insert(l, &a);
    insert(l, &b);
    insert(l, &c);

    // imprimir os elementos da lista
    int i;
    for (i = 0; i < size(l); i++) {
        int *data = (int *) get(l, i);
        printf("%d ", *data);
    }


    // imprimir os elementos da lista
    for (i = 0; i < size(l); i++) {
        int *data = (int *) get(l, i);
        printf("%d ", *data);
    }

    // liberar a memória alocada pela lista
    free_list(l);


    // criar uma lista de strings
    list *l2 = create_list();
    char *s1 = "abc";
    char *s2 = "def";
    char *s3 = "ghi";
    insert(l2, s1);
    insert(l2, s2);
    insert(l2, s3);

    // imprimir os elementos da lista
    for (i = 0; i < size(l2); i++) {
        char *data = (char *) get(l2, i);
        printf("%s ", data);
    }

    // liberar a memória alocada pela lista
    free_list(l2);

    
    return 0;
}