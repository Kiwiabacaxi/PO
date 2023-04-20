#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct nod {
    int info;
    struct nod *ant;
    struct nod *prox;
} Nod;

typedef struct listad{
    Nod *ini;
    Nod *fim;
} Listad;

typedef struct arvn {
    int numero; 
    int qtd; // quantidade de filhos
    bool infectado; // se estiver infectado 0 = não, 1 = sim
    Listad *filhos; // aponta para a lista
} ArvN;

void inserir_filho(ArvN *pai, ArvN *filho);
int contar_infectados(ArvN *no, int k, int *menor_infectados);


// -------------------------------------------------------- // LISTA DUPLA //
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

// -------------------------------------------- // LISTA DUPLA //

ArvN* criar_arvore(int info) {
    ArvN *nova_arvore = (ArvN*) malloc(sizeof(ArvN));
    nova_arvore->numero = info;
    nova_arvore->qtd = 0;
    nova_arvore->infectado = false;
    nova_arvore->filhos = (Listad*) malloc(sizeof(Listad));
    nova_arvore->filhos->ini = NULL;
    nova_arvore->filhos->fim = NULL;
    return nova_arvore;
}

/* void inserir_filho(ArvN *pai, ArvN *filho) {
    Nod *novo_no = (Nod*) malloc(sizeof(Nod));
    novo_no->info = filho->info;
    novo_no->ant = NULL;
    novo_no->prox = NULL;

    if (pai->filhos->ini == NULL) {
        pai->filhos->ini = novo_no;
        pai->filhos->fim = novo_no;
    } else {
        pai->filhos->fim->prox = novo_no;
        novo_no->ant = pai->filhos->fim;
        pai->filhos->fim = novo_no;
    }

    pai->qtd++;
} */

// clonar a arvore clonar_arvore(arvore)
ArvN* clonar_arvore(ArvN *arvore) {
    ArvN *nova_arvore = criar_arvore(arvore->numero);
    nova_arvore->infectado = arvore->infectado;
    nova_arvore->qtd = arvore->qtd;
    
    Nod *aux = arvore->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        ArvN *filho_clonado = clonar_arvore(filho);
        inserir_filho(nova_arvore, filho_clonado);
        aux = aux->prox;
    }
    
    return nova_arvore;
}

// libera a memória alocada para a árvore
void limpar_arvore(ArvN *no) {
    if (no == NULL) {
        return;
    }
    
    // percorre todos os filhos do nó atual
    Nod *aux = no->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        limpar_arvore(filho); // chama recursivamente a função para cada filho
        aux = aux->prox;
    }
    
    // libera a memória alocada para o nó atual
    free(no->filhos);
    free(no);
}

void inserir_filho(ArvN *pai, ArvN *filho) {
    Nod *novo = (Nod*) malloc(sizeof(Nod));
    // novo->info = (int) filho;
    novo->info = filho;
    novo->ant = NULL;
    novo->prox = NULL;
    //printf("Endereço de pai->filhos: %p\n", pai->filhos);
    //printf("Endereço de novo: %p\n", novo);
    //printf("Endereço de novo->info: %p\n", &novo->info);
    //printf("Endereço de novo->ant: %p\n", &novo->ant);
    //printf("Endereço de novo->prox: %p\n", &novo->prox);
    //printf("\n------------------------\n");
    if (pai->filhos->ini == NULL) {
        pai->filhos->ini = novo;
        pai->filhos->fim = novo;
    } else {
        pai->filhos->fim->prox = novo;
        novo->ant = pai->filhos->fim;
        pai->filhos->fim = novo;
    }
    pai->qtd++;
}


void dfs(ArvN *no) {
    no->infectado = true;
    Nod *aux = no->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        if (!filho->infectado) {
            dfs(filho);
        }
        aux = aux->prox;
    }
}

int buscar_kesimo(ArvN *no, int k, int *total_infectados, ArvN **encontrado) {
    //encontrado = NULL;
    // int encontrado_flag = buscar_kesimo(filho, k - *total_infectados, total_infectados, &encontrado);
    
    if (*encontrado) {
        return 0;
    }

    if (no->infectado) {
        return 0;
    }

    //int qtd_esq = contar_infectados(no, *encontrado);
    //int infectados = contar_infectados(no->filhos->ini, k, total_infectados); // passing argument 1 of 'contar_infectados' makes pointer from integer without a cast [-Werror=int-conversion]
    int infectados = contar_infectados(no, k, total_infectados);

    *total_infectados += infectados;

    if (*total_infectados >= k) {
        *encontrado = no;
        return 1;
    }

    Nod *aux = no->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        if (!filho->infectado) {
            //int encontrado = buscar_kesimo(filho, k - *total_infectados, total_infectados, encontrado); // passing argument 4 of 'buscar_kesimo' makes pointer from integer without a cast [-Werror=int-conversion]
            //int encontrado = buscar_kesimo(filho, k - *total_infectados, total_infectados, &(*encontrado));
            //int encontrado = buscar_kesimo(filho, k - *total_infectados, total_infectados, (ArvN **) encontrado); //cast to pointer from integer of different size [-Wint-to-pointer-cast]
            int encontrado = buscar_kesimo(filho, k - *total_infectados, total_infectados, (ArvN **) &encontrado); //cast to pointer from integer of different size [-Wint-to-pointer-cast]
            
            if (encontrado) {
                return 1;
            }
        }
        aux = aux->prox;
    }

    return 0;
}

/* int contar_infectados(ArvN *no) {
    int total = 0;
    no->infectado = true;
    Nod *aux = no->filhos->ini;

    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        if (!filho->infectado) {
            total += contar_infectados(filho);
        }
        aux = aux->prox;
    }

    return total + 1; // ou sem o + 1

} */

/* void contar_infectados(ArvN *no, int k, int *total_infectados, int *menor_infectados) {
    no->infectado = true;
    (*total_infectados)++;

    if (*total_infectados >= k) {
        return;
    }

    Nod *aux = no->filhos->ini;

    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        if (!filho->infectado) {
            contar_infectados(filho, k, total_infectados, menor_infectados);
            if (*total_infectados >= k) {
                return;
            }
        }
        aux = aux->prox;
    }

    *menor_infectados = *total_infectados;
    return;
} */

int contar_infectados(ArvN *no, int k, int *menor_infectados) {
    int total = 0;
    no->infectado = true;

    Nod *aux = no->filhos->ini;
    int i = 1;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;

        if (!filho->infectado) {
            if (i == k) {
                int infectados = contar_infectados(filho, k, menor_infectados);

                // atualiza total e menor_infectados
                total += infectados;
                if (total >= k && *menor_infectados == 0) {
                    *menor_infectados = total;
                }
            } else {
                total += contar_infectados(filho, k, menor_infectados);
            }
            i++;
        }

        aux = aux->prox;
    }

    return total + 1; // conta o nó atual
}

// inserir nos 


/* int busca_binaria(ArvN *raiz, int k, int *menor_infectados) {
    int total = 0;
    Nod *aux = raiz->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) aux->info;
        if (!filho->infectado) {
            total += contar_infectados(filho);
        }
        aux = aux->prox;
    }

    if (total < k) {
        *menor_infectados = total;
        return raiz->info;
    } else {
        Nod *aux = raiz->filhos->ini;
        while (aux != NULL) {
            ArvN *filho = (ArvN*) aux->info;
            if (!filho->infectado) {
                int resposta = busca_binaria(filho, k, menor_infectados);
                if (resposta != -1) {
                    return resposta;
                }
            }
            aux = aux->prox;
        }
    }

    return -1;
} */

/* int busca_binaria(ArvN *raiz, int k, int *menor_infectados) {
    int esq = 1;
    int dir = raiz->qtd + 1;
    int infectados = contar_infectados(raiz);

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        if (infectados + meio <= k) {
            *menor_infectados = infectados + meio;
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    return *menor_infectados;

} */

/* int busca_binaria(ArvN *raiz, int n) {
    int esq = 1;
    int dir = n;
    int resposta = -1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int infectados = contar_infectados(raiz, meio);
        if (infectados >= (n+1)/2) {
            resposta = infectados;
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }
    return resposta;
} */

/* int busca_binaria(ArvN *raiz, int k, int *menor_infectados) {
    int esq = 1;
    int dir = raiz->qtd + 1;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int total_infectados = 0;
        int infectados = contar_infectados(raiz, meio, &total_infectados, menor_infectados);

                // opção 1 
        // infectados + meio <= k
        // opção 2
        // total_infectados >= k

        if (infectados + meio <= k) {
            *menor_infectados = meio;
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    return *menor_infectados;
} */

/* int busca_binaria(ArvN *raiz, int k, int *menor_infectados) {
    int esq = 1;
    int dir = raiz->qtd + 1;
    int total_infectados = contar_infectados(raiz->filhos->ini, k, menor_infectados);
    

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        total_infectados = 0;
        int encontrado = buscar_kesimo(raiz, meio, k, &total_infectados);

        if (encontrado && total_infectados <= k) {
            *menor_infectados = total_infectados;
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    return esq - 1;
} */

int busca_binaria(ArvN *raiz, int k, int *menor_infectados) {
    int esq = 1;
    int dir = raiz->qtd + 1;
    int meio;

    while (esq <= dir) {
        meio = (esq + dir) / 2;
        int total_infectados = 0;
        int encontrado = buscar_kesimo(raiz, meio, (int *) &k, (ArvN **) &total_infectados); // passing argument 3 of ‘buscar_kesimo’ makes pointer from integer without a cast

        int infectados = contar_infectados(raiz, encontrado, menor_infectados);
        if (infectados >= k) {
            dir = meio - 1;
        } else {    
            esq = meio + 1;
        }
    }

    return esq;
}

/* // ordenar_lista: ordena uma lista de forma crescente
void ordenar_lista(Listad *lista) {
    Nod *aux = lista->ini;
    while (aux != NULL) {
        Nod *aux2 = aux->prox;
        while (aux2 != NULL) {
            if (aux->info > aux2->info) {
                //int temp = aux->info; // initialization of int from struct ArvN * makes integer from pointer without a cast [-Wint-conversion]
                ArvN *temp = (ArvN *) &aux->info;
                aux->info = aux2->info;
                aux2->info = temp;
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}


// ordenar os filhos de forma crescente
void ordenar_filhos(ArvN *raiz) {
    Nod *aux = raiz->filhos->ini;
    while (aux != NULL) {
        ArvN *filho = (ArvN*) &aux->info;
        ordenar_filhos(filho);
        aux = aux->prox;
    }

    ordenar_lista(raiz->filhos);
} */



int main(){
    // 1665C - Infection Tree (https://codeforces.com/contest/1665/problem/C)

    int numero_testes;
    scanf("%d", &numero_testes);

    while (numero_testes--) {
        int n;
        scanf("%d", &n);

        // encontrar o k 
        // n = 7, k = 4 => ceil(7/2) = 4
        // n = 5, k = 3 => ceil(5/2) = 3
        int k = ceil(n / 2.0);

        ArvN *arvore = criar_arvore(1);
        ArvN *aux = arvore;

        for (int i = 2; i <= n; i++) {
            int pai;
            scanf("%d", &pai);

            ArvN *no = criar_arvore(i);

            inserir_filho(aux, no);

            //printf("Pai de %d: ", i-1);

            if (i == pai) {
                aux = no;
            }
        }



        int menor_infectados = 0;


        int resposta = busca_binaria(arvore, k, &menor_infectados);
        printf("%d\n", resposta + 1);
/*         if (numero_testes > 0) {
            //printf("menor infectado %d \n", menor_infectados);
            printf("%d\n",resposta+1);
        }
        else {
            printf("%d\n",resposta);
        } */

        // limpa a memória alocada para a árvore
        limpar_arvore(arvore);
        

    }

    return 0;
}