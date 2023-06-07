/* 

Hoje em dia, infelizmente, mensagens de SPAM estão ficando mais e mais comuns. Algumas delas têm efeito de multiplicação, já que pedem que repasses para teus amigos. Algumas mensagens de SPAM desejam boa sorte, outras, prometem que tornar-se-á rico, e outras apenas lhe lembram o quão importante é contar a seus amigos o quanto você se importa com suas amizades. Eis um exemplo de SPAM:
   De: Alice
   Para: Bob, Mary, Julia, Paul

   Olá, este é um e-mail de boa sorte. Desejo que se torne milionário, mas
   isso depende de você. Se você:
   * mandar esse e-mail para 10 pessoas você se ficará milionário
   * mandar esse e-mail para 5 ou mais pessoas você ficará rico
   * mandar esse e-mail para menos de 5 pessoas você será pobre
   Como eu disse, depende de você. Escreve seu e-mail e seja rico! :-)

   Alice

Pessoas normalmente reagem de dois modos diferentes quando recebem SPAM:

    Eles descartam a mensagem imediatamente sem ao menos lê-la (eles odeiam SPAM);
    Eles encaminham a mensagem para todos que conhecem (eles amam SPAM).

Para esse problema, nós assumiremos que todos amam SPAM, mas ninguém manda a mesma mensagem duas vezes. Cada mensagem de SPAM tem um efeito baseado no número de amigos que você manda as mensagens. Por exemplo: uma mensagem de SPAM poderá lhe dizer que ficarás pobre se mandares a mensagem para 5 amigos, mas serás rico se mandares para 10, e serás o mais rico do mundo se mandares para 20 amigos, e assim vai.

Consideraremos apenas as mensagens de SPAM similares ao exemplo acima. Mais especificamente, uma mensagem de SPAM definirá dois valores limiares T1 e T2 e três atribuidores A1, A2 e A3. Uma pessoa adquire um dos três valores dependendo do número de mensagens enviadas para aquele SPAM específico. Se a pessoa encaminha T mensagens e T < T1 então o atributo dele/dela é A1, se T1 ≤ T < T2 então o atributo dele/dela é A2, caso contrário o atributo dela é A3.

Lhe será dado os nomes de um grupo de pessoas, e para cada pessoa do grupo, um conjunto de amigos que ele/ela conhece o endereço de e-mail. Lhe será dado um conjunto distinto de mensagens de SPAM, e para cada mensagem de SPAM ela limita valores e atributos, e a informação sobre cada pessoa que iniciou a proliferação do SPAM. Você tem que escrever um programa que determine, para cada pessoa no grupo dado, quais atributos ele/ela adquiriu, baseado no SPAM encaminhado.

Você assumirá que o originador do SPAM tenha pelo menos um amigo (em outras palavras, ele/ela enviará pelo menos uma mensagem), e a pessoa não mandará para si mesma.
Entrada

Seu programa deverá processar vários casos de teste. A primeira linha do caso de teste contém um inteiro N indicando o número de pessoas no grupo (2 ≤ N ≤ 20). Na entrada a pessoa é identificada por um inteiro de 1 a N. As N linhas seguintes contêm cada, uma lista de amigos de cada pessoa (a linha i contém a lista de amigos da pessoa i). A lista de amigos da pessoa i descreve os amigos que a pessoa i conhece o endereço de e-mail, e consiste de uma lista de inteiros Fi (1 ≤ Fi ≤ N, Fi ≠ i) terminada pelo valor 0 (zero). Seguindo a lista de amigos vem a descrição das mensagens de SPAM (terá no máximo 100 mensagens). Cada descrição aparece em uma linha diferente. A descrição consiste de um inteiro P identificando a pessoa originadora do SPAM (2 ≤ P ≤ N); dois inteiros T1 e T2 representando os valores limites; e os três atributos A1, A2 e A3 (cada atributo é uma palavra de não mais que vinte letras). A lista de SPAM acaba com uma linha contendo apenas o valor 0 (zero). As N linhas contém cada, um nome, que é uma palavra apenas, com não mais que vinte letras. O nome na linha de i é o nome da pessoa número i. O fim da entrada é indicado por N = 0.
Saída

Para cada caso de teste seu programa deverá exibir uma lista de nomes seguida dos atributos que adquiriram. Seu programa deve escrever os nomes das pessoas na ordem em que aparecerem na entrada, seguido de ‘:’ e de um espaço, seguido de seus atributos de acordo com os SPAM que enviaram. Os atributos devem ser escritos na ordem que apareceram na entrada; cada atributo deve ser seguido de espaço.

 

Exemplo de entrada

5
2 3 0
1 3 5 4 0
5 0
0
4 1 0
1 2 4 poor rich millionaire
5 3 10 sad normal happy
0
Bob
Paul
Mary
Alice
Julia
6
2 0
1 3 0
1 2 4 0
1 2 3 5 0
1 2 3 4 0
1 3 4 0
1 2 4 red green blue
1 2 4 dumb normal smart
6 3 5 ugly bad good
0
Peter
Paul
Victoria
John
Julia
Anne
0 0



Exemplo de saída

Bob: rich sad 
Paul: millionaire normal 
Mary: poor sad 
Alice: poor sad 
Julia: rich sad 
Peter: red dumb ugly 
Paul: green normal ugly 
Victoria: green normal bad 
John: blue smart bad 
Julia: blue smart bad 
Anne: red dumb bad 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

// -------------------- // FILA // -------------------- //
typedef struct Fila {
    int* elementos;
    int tamanho;
    int inicio;
    int fim;
} Fila;

Fila* criar_fila(int tamanho) {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->elementos = (int*) malloc(tamanho * sizeof(int));
    fila->tamanho = tamanho;
    fila->inicio = 0;
    fila->fim = 0;
    return fila;
}

void enfileirar(Fila* fila, int elemento) {
    fila->elementos[fila->fim] = elemento;
    fila->fim = (fila->fim + 1) % fila->tamanho;
}

int desenfileirar(Fila* fila) {
    int elemento = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    return elemento;
}

int fila_vazia(Fila* fila) {
    return fila->inicio == fila->fim;
}

// -------------------- // LISTA // -------------------- //
// Estrutura de um nó
typedef struct node {
    int vertice;
    struct node* proximo;
} Node;

// Estrutura de uma lista ligada
typedef struct lista_ligada {
    Node* cabeca;
} ListaLigada;

// Cria um novo nó
Node* criar_no(int v) {
    Node* novo_no = (Node*) malloc(sizeof(Node));
    novo_no->vertice = v;
    novo_no->proximo = NULL;
    return novo_no;
}

// Cria uma nova lista ligada
ListaLigada* criar_lista_ligada() {
    ListaLigada* lista = (ListaLigada*) malloc(sizeof(ListaLigada));
    lista->cabeca = NULL;
    return lista;
}

// Adiciona um nó na lista ligada
void adicionar_no(ListaLigada* lista, int v) {
    Node* novo_no = criar_no(v);
    novo_no->proximo = lista->cabeca;
    lista->cabeca = novo_no;
}

// Remove um nó da lista ligada
void remover_no(ListaLigada* lista, int v) {
    Node* atual = lista->cabeca;
    Node* anterior = NULL;

    while (atual != NULL && atual->vertice != v) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return;

    if (anterior == NULL) {
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
}

// -------------------- // PILHA // -------------------- //
// Estrutura de uma pilha
typedef struct pilha {
    int topo;
    int* elementos;
} Pilha;

// Cria uma nova pilha
Pilha* criar_pilha(int tamanho) {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->topo = -1;
    pilha->elementos = (int*) malloc(tamanho * sizeof(int));
    return pilha;
}

// Verifica se a pilha está vazia
int pilha_vazia(Pilha* pilha) {
    return pilha->topo == -1;
}

// Insere um elemento na pilha
void empilhar(Pilha* pilha, int elemento) {
    pilha->elementos[++pilha->topo] = elemento;
}

// Remove um elemento da pilha
int desempilhar(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        printf("Erro: pilha vazia\n");
        exit(1);
    }
    return pilha->elementos[pilha->topo--];
}

// -------------------- // GRAFO DINAMICO // -------------------- //
// Estrutura do grafo
typedef struct grafo {
    ListaLigada* lista_adjacencia;
    int* tamanho_atributos;
    char*** atributos;
    int* processado;
    int* grau;
    int num_vertices;
} Grafo;

// Cria um novo grafo
Grafo* criar_grafo(int num_vertices) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->lista_adjacencia = (ListaLigada*) malloc(num_vertices * sizeof(ListaLigada));
    grafo->tamanho_atributos = (int*) calloc(num_vertices, sizeof(int));
    grafo->atributos = (char***) malloc(num_vertices * sizeof(char**));
    grafo->processado = (int*) calloc(num_vertices, sizeof(int));
    grafo->grau = (int*) calloc(num_vertices, sizeof(int));
    grafo->num_vertices = num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        grafo->lista_adjacencia[i].cabeca = NULL;
        grafo->atributos[i] = (char**) malloc(MAXN * sizeof(char*));
        for (int j = 0; j < MAXN; j++) {
            grafo->atributos[i][j] = (char*) malloc(21 * sizeof(char));
        }
    }

    return grafo;
}

// Adiciona uma aresta no grafo - v1
/* void adicionar_aresta(Grafo* grafo, int origem, int destino) {
    Node* novo_no = criar_no(destino);
    novo_no->proximo = grafo->lista_adjacencia[origem].cabeca;
    grafo->lista_adjacencia[origem].cabeca = novo_no;
    grafo->grau[origem]++;
} */

// Adiciona uma aresta no grafo - v2
void adicionar_aresta(Grafo* grafo, int origem, int destino) {
    adicionar_no(&grafo->lista_adjacencia[origem], destino);
    grafo->grau[origem]++;
}

// Remove uma aresta no grafo
void remover_aresta(Grafo* grafo, int origem, int destino) {
    Node* atual = grafo->lista_adjacencia[origem].cabeca;
    Node* anterior = NULL;

    while (atual != NULL && atual->vertice != destino) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return;

    if (anterior == NULL) {
        grafo->lista_adjacencia[origem].cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    grafo->grau[origem]--;
}

// Imprime o grafo - COM SWAG PKRL TEM SETA ... -> ... E NULL NO FINAL <3
void imprimir_grafo(Grafo* grafo) {
    for (int i = 1; i < grafo->num_vertices; i++) {
        printf("%d: ", i);
        Node* temp = grafo->lista_adjacencia[i].cabeca;
        while (temp != NULL) {
            printf("%d -> ", temp->vertice);
            temp = temp->proximo;
        }
        printf("NULL\n");
    }
}

// Função que libera a memória alocada
void liberar_memoria(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        Node* temp = grafo->lista_adjacencia[i].cabeca;
        while (temp != NULL) {
            Node* next = temp->proximo;
            free(temp);
            temp = next;
        }
        for (int j = 0; j < MAXN; j++) {
            free(grafo->atributos[i][j]);
        }
        free(grafo->atributos[i]);
    }
    free(grafo->lista_adjacencia);
    free(grafo->tamanho_atributos);
    free(grafo->atributos);
    free(grafo->processado);
    free(grafo->grau);
    free(grafo);
}

// -------------------- // BUSCA EM PROFUNDIDADE // -------------------- //
// Função de busca em profundidade - v1 - NAO FUNCIONA Ñ SEI PQ
void dfs(Grafo* grafo, int x, int t1, int t2, char* a1, char* a2, char* a3) {
    grafo->processado[x] = 1;
    grafo->tamanho_atributos[x]--;

    if (grafo->grau[x] < t1)
        strcpy(grafo->atributos[x][grafo->tamanho_atributos[x]++], a1);
    else if (grafo->grau[x] < t2)
        strcpy(grafo->atributos[x][grafo->tamanho_atributos[x]++], a2);
    else
        strcpy(grafo->atributos[x][grafo->tamanho_atributos[x]++], a3);

    Node* temp = grafo->lista_adjacencia[x].cabeca;
    while (temp != NULL) {
        int v = temp->vertice;
        if (grafo->processado[v] == 0) dfs(grafo, v, t1, t2, a1, a2, a3);
        temp = temp->proximo;
    }
}

/* 
101 de como deve ser a função dfs

x -- Ela recebe como parâmetro o vértice inicial P.
x -- A função marca o vértice P como processado e remove o último atributo do vetor de atributos do vértice P.
x -- A função atribui um dos valores a1, a2 ou a3 ao vértice P de acordo com o tamanho da lista de adjacência do vértice P.
x -- A função então percorre todos os vizinhos do vértice P que ainda não foram processados e chama recursivamente a função dfs para cada vizinho.
x -- A função utiliza a estrutura vector para armazenar as listas de adjacência e os atributos dos vértices.
x -- A função utiliza a variável processado para marcar os vértices que já foram processados.
x -- atribui um dos valores a1, a2 ou a3 ao vértice v de acordo com o seu grau e empilha todos os vizinhos não processados de v 
x -- A função utiliza um loop for para percorrer os vizinhos do vértice P.

P - INICIO DO SPAM
t1 - grau do spammer
t2 - grau do spammer
a1 - atributo do spammer
a2 - atributo do spammer
a3 - atributo do spammer

ergo - se o grau do spammer for menor que t1, ele recebe a1
       se o grau do spammer for menor que t2, ele recebe a2
       se o grau do spammer for maior que t2, ele recebe a3



*/

// Função de busca em profundidade com pilha - v2 - FUNCIONA
/* void dfs(Grafo* grafo, int luis_espalha_lixo, int t1, int t2, char* a1, char* a2, char* a3) {
    // Cria uma pilha e coloca o vértice inicial nela
    Pilha* pilha = criar_pilha(grafo->num_vertices);
    empilhar(pilha, luis_espalha_lixo);

    // Enquanto a pilha não estiver vazia
    while (!pilha_vazia(pilha)) {
        // Desempilha um vértice e o processa
        int v = desempilhar(pilha);

        // Se o vértice ainda não foi processado
        if (grafo->processado[v] == 0) {
            grafo->processado[v] = 1;
            grafo->tamanho_atributos[v]--;

            // Adiciona o atributo correspondente
            // strcpy para copiar as strings a1, a2 e a3 para os atributos dos vértices.
            if (grafo->grau[v] < t1)
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a1);
            else if (grafo->grau[v] < t2)
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a2);
            else
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a3);

            Node* temp = grafo->lista_adjacencia[v].cabeca;
            while (temp != NULL) {
                int u = temp->vertice;
                if (grafo->processado[u] == 0) {
                    empilhar(pilha, u);
                }
                temp = temp->proximo;
            }
        }
    }
} */


// -------------------- // BUSCA EM LARGURA // -------------------- //
// busca em largura no lugar da busca em profundidade
void bfs(Grafo* grafo, int luis_espalha_lixo, int t1, int t2, char* a1, char* a2, char* a3) {
    // Cria uma fila e coloca o vértice inicial nela
    Fila* fila = criar_fila(grafo->num_vertices);
    enfileirar(fila, luis_espalha_lixo);

    // Enquanto a fila não estiver vazia
    while (!fila_vazia(fila)) {
        // Desenfileira um vértice e o processa
        int v = desenfileirar(fila);

        // Se o vértice ainda não foi processado
        if (grafo->processado[v] == 0) {
            grafo->processado[v] = 1;
            grafo->tamanho_atributos[v]--;

            // Adiciona o atributo correspondente
            // strcpy para copiar as strings a1, a2 e a3 para os atributos dos vértices.
            if (grafo->grau[v] < t1)
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a1);
            else if (grafo->grau[v] < t2)
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a2);
            else
                strcpy(grafo->atributos[v][grafo->tamanho_atributos[v]++], a3);

            Node* temp = grafo->lista_adjacencia[v].cabeca;
            while (temp != NULL) {
                int u = temp->vertice;
                if (grafo->processado[u] == 0) {
                    enfileirar(fila, u);
                }
                temp = temp->proximo;
            }
        }
    }
}



// -------------------- // MAIN // -------------------- //
int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        // Criar grafo de tamanho n + 1
        Grafo* grafo = criar_grafo(n + 1);

        // 1 - Adicionar arestas
        for (int i = 1; i <= n; i++) {
            int j;
            while (scanf("%d", &j) && j != 0) {
                adicionar_aresta(grafo, i, j);
            }
        }

        // Imprimir grafo para ver se está tudo certo
        // printf("Primeiro grafo:\n");
        // imprimir_grafo(grafo);


        // 2 - P identificando a pessoa originadora do SPAM
        int inicio_spam = 0;
        while (scanf("%d", &inicio_spam) && inicio_spam != 0 && inicio_spam <= n) {
            // T1 e T2 representando os valores limites
            int t1, t2;

            // os três atributos A1, A2 e A3 (cada atributo é uma palavra de não mais que vinte letras)
            char a1[MAXN], a2[MAXN], a3[MAXN];

            // limpar as strings
            memset(a1, 0, sizeof(a1));
            memset(a2, 0, sizeof(a2));
            memset(a3, 0, sizeof(a3));

            // Ler os valores
            scanf("%d %d %s %s %s", &t1, &t2, a1, a2, a3);

            // ofecerer o primogênito em sacrifício para os deuses do C
            for (int i = 1; i <= n; i++) {
                // resetar o processado
                grafo->processado[i] = 0;
                // printf("%d\n", grafo->tamanho_atributos[i]);
                
                
                // copiar os atributos
                strcpy(grafo->atributos[i][grafo->tamanho_atributos[i]++], a1);
                // printf("%d\n", grafo->tamanho_atributos[i]);
            }

            // chamar a função de busca em profundidade
            dfs(grafo, inicio_spam, t1, t2, a1, a2, a3);
            // printf("%d\n", dfs2(grafo, inicio_spam, t1, t2, a1, a2, a3));
            // chamar a função de busca em largura
            // bfs(grafo, inicio_spam, t1, t2, a1, a2, a3);

        }

        // Imprimir grafo para ver se está tudo certo
        // printf("Segundo grafo\n");
        // imprimir_grafo(grafo);
        

        // 3 - Imprimir os resultados
        for (int i = 1; i <= n; i++) {
            // receber o nome de cada pessoa postumamente
            char nome[21];
            scanf("%s", nome);

            printf("%s: ", nome);

            // imprimir os atributos
            for (int j = 0; j < grafo->tamanho_atributos[i]; j++) {
                printf("%s ", grafo->atributos[i][j]);
            }
            printf("\n");
        }

        // função de liberação de memória da baguncinha
        liberar_memoria(grafo);
    }
    return 0;
}
