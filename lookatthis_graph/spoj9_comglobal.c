/* O reino de Nlogônia é rico, o povo é educado e feliz, mas o Rei é um tirano quando o assunto se refere a impostos. A cada final de ano, cada cidade do país deve pagar uma determinada quantidade de quilos de ouro em impostos. Chegado o momento de coletar os impostos, o Rei envia sua carruagem real para recolher o ouro devido, usando as estradas do reino.

Cada estrada liga duas cidades diferentes e pode ser percorrida nas duas direções. A rede de estradas é tal que é possível ir de qualquer cidade para qualquer outra cidade, possivelmente passando por cidades intermediárias, mas há apenas um caminho entre duas cidades diferentes.

Em cada cidade há um cofre real, utilizado para armazenamento de ouro de impostos. Os cofres reais são imensos, de forma que cada cofre tem capacidade de armazenar todo o ouro devido por todo o reino. A carruagem sai da capital, percorrendo as estradas do reino, visitando as cidades para recolher o ouro devido, podendo usar qualquer cofre real para armazenar temporariamente uma parte do imposto recolhido, se necessário. Ao final da coleta, todo o ouro devido por todas as cidades deve estar armazenado no cofre real da capital.

Ávaro como é o Rei, ele contratou o seu time para, dados a quantidade de ouro a ser recolhido em cada cidade (em kg), a lista das estradas do reino, com os respectivos comprimentos (em km) e a capacidade de carga da carruagem real (em kg), determine qual é a mínima distância que a carruagem deve percorrer para recolher todo o ouro devido.
Entrada

A primeira linha contém dois inteiros N e C indicando respectivamente o número de cidades e a capacidade de carga da carruagem (2 ≤ N ≤ 104 e 1 ≤ C ≤ 100). A capital do reino é identificada pelo número 1, as outras cidades são identificadas por inteiros de 2 a N . A segunda linha contém N inteiros Ei representando a quantidade de imposto devido por cada cidade i (0 ≤ Ei ≤ 100 para 1 ≤ i ≤ N ). Cada uma das N-1 linhas seguintes contém três inteiros A , B e C , indicando que uma estrada liga a cidade A e a cidade B (1 ≤ A, B ≤ N ) e tem comprimento C (1 ≤ C ≤ 100).
Saída

Seu programa deve produzir uma única linha com um inteiro representando a menor distância que a carruagem real deve percorrer para recolher todo o imposto devido, em km. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10100

// Estrutura de dados para armazenar as arestas do grafo
typedef struct {
    int destino;
    int peso;
} aresta;

// Estrutura de dados para armazenar um vetor dinâmico de arestas
typedef struct {
    aresta* dados;
    int tamanho;
    int capacidade;
} vetor;

// Variáveis globais - porque as locais dao timeout: the monitored command dumped core :DDDDDDDDDDDDDDDDDDDDDDDDDD

// Vetor grafo com as arestas do grafo
vetor grafo[MAXN];
// Vetor quantidade com a quantidade de minério em cada nó
int quantidade[MAXN], custo, N, C;

void dfs(int v, int p, int f) {
    // Percorre todas as arestas do nó v
    for (int i = 0; i < grafo[v].tamanho; i++) {
        int u = grafo[v].dados[i].destino;
        int peso = grafo[v].dados[i].peso;
        // Verifica se o nó destino é o nó pai
        if (u == p) continue; // Evita voltar para o nó pai
        // Chama a função dfs recursivamente para o nó destino
        dfs(u, v, peso);
    }
    
    // Se chegou no nó raiz, retorna
    if (v == 1) return;
    // Calcula o custo de transporte para o nó atual
    custo += f * (quantidade[v] / C);
    if (quantidade[v] % C != 0) custo += f;
    // Atualiza a quantidade de minério no nó pai
    quantidade[p] += quantidade[v];
}

int main() {

    // Lê o número de nós (N) e a capacidade do caminhão (C)
    scanf("%d %d", &N, &C);
    // Lê a quantidade de minério em cada nó
    for (int i = 1; i <= N; i++){
        scanf("%d", &quantidade[i]);
    }

    /* 
    1 - Leitura dos dados de entrada para cada aresta de um grafo
    2 - Cria duas novas arestas e adiciona no grafo
    3 - Atualiza o tamanho do grafo
    4 - Adiciona as arestas ao grafo redimensionando os arrays de arestas para os nós de origem e destino
    5 - Adiciona as novas arestas ao final desses arrays
    */

    // Lê as arestas do grafo e as adiciona à estrutura de dados
    for (int i = 1; i < N; i++) {
        int u, v, peso;
        scanf("%d %d %d", &u, &v, &peso);
        // Cria duas novas arestas com os valores lidos
        aresta aresta1 = {v, peso};
        aresta aresta2 = {u, peso};
        // Redimensiona os arrays de arestas para os nós de origem e destino
        grafo[u].dados = (aresta*)realloc(grafo[u].dados, (grafo[u].tamanho + 1) * sizeof(aresta));
        grafo[v].dados = (aresta*)realloc(grafo[v].dados, (grafo[v].tamanho + 1) * sizeof(aresta));
        // Adiciona as novas arestas ao final desses arrays
        grafo[u].dados[grafo[u].tamanho++] = aresta1;
        grafo[v].dados[grafo[v].tamanho++] = aresta2;
    }

    // Chama a função dfs para calcular o custo mínimo de transporte
    dfs(1, -1, -1);
    // Imprime o resultado (o dobro do custo mínimo)
    printf("%d\n", 2 * custo);
    
    return 0;
}