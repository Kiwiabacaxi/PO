/* BOLHAS - Onde Estão as Bolhas?

Uma das operações mais freqüentes em computação é ordenar uma seqüência de objetos. Por- tanto, não é surpreendente que essa operação seja também uma das mais estudadas.

Um algoritmo bem simples para ordenação é chamado Bubblesort. Ele consiste de vários turnos. A cada turno o algoritmo simplesmente itera sobre a seqüência trocando de posição dois elementos consecutivos se eles estiverem fora de ordem. O algoritmo termina quando nenhum elemento trocou de posição em um turno.

O nome Bubblesort (ordenação das bolhas) deriva do fato de que elementos menores ("mais leves") movem-se na direção de suas posições finais na seqüência ordenada (movem-se na direção do início da seqüência) durante os turnos, como bolhas na água. A figura abaixo mostra uma implementação do algoritmo em pseudo-código:

Para i variando de 1 a N faça
	Para j variando de N - 1 a i faça
		Se seq[j - 1] > seq[j] então
			Intercambie os elementos seq[j - 1] e seq[j]
		Fim-Se
	Fim-Para
	Se nenhum elemento trocou de lugar então
		Final do algoritmo
	Fim-Se
Fim-Para

Por exemplo, ao ordenar a seqüência [5, 4, 3, 2, 1] usando o algoritmo acima, quatro turnos são necessários. No primeiro turno ocorrem quatro intercâmbios: 1 x 2, 1 x 3, 1 x 4 e 1 x 5; no segundo turno ocorrem três intercâmbios: 2 x 3, 2 x 4 e 2 x 5; no terceiro turno ocorrem dois intercâmbios: 3 x 4 e 3 x 5; no quarto turno ocorre um intercâmbio: 4 x 5; no quinto turno nenhum intercâmbio ocorre e o algoritmo termina.

Embora simples de entender, provar correto e implementar, o algoritmo bubblesort é muito ineficiente: o número de comparações entre elementos durante sua execução é, em média, diretamente proporcional a N2, onde N é o número de elementos na seqüência.

Você foi requisitado para fazer uma "engenharia reversa" no bubblesort, ou seja, dados o comprimento da seqüência, o número de turnos necessários para a ordenação e o número de intercâmbios ocorridos em cada turno, seu programa deve descobrir uma possível seqüência que, quando ordenada, produza exatamente o mesmo número de intercâmbios nos turnos.
Entrada

A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois inteiros N e M que indicam respectivamente o número de elementos (1 ≤ N ≤ 100.000) na seqüência que está sendo ordenada, e o número de turnos (0 ≤ M ≤ 100.000) necessários para ordenar a seqüência usando bubblesort. A segunda linha de um caso de teste contém M inteiros Xi, indicando o número de intercâmbios em cada turno i (1 ≤ Xi ≤ N - 1, para 1 ≤ i ≤ M).

O final da entrada é indicado por N = M = 0.

A entrada deve ser lida da entrada padrão.
Saída

Para cada caso de teste da entrada seu programa deve produzir uma linha na saída, contendo uma permutação dos números {1, 2, . . . , N }, que quando ordenada usando bubblesort produz o mesmo número de intercâmbios no mesmo número de turnos especificados na entrada. Ao imprimir a permutação, deixe um espaço em branco entre dois elementos consecutivos. Se mais de uma permutação existir, imprima a maior na ordem lexicográfica padrão para seqüências de números (a ordem lexicográfica da permutação a1, a2, . . . aN é maior do que a da permutação b1, b2, . . . bN se para algum 1 ≤ i ≤ N temos ai > bi e o prefixo a1, a2, . . . ai-1 é iqual ao prefixo b1, b2, . . . bi-1) .

Em outras palavras, caso exista mais de uma solução, imprima aquela onde o primeiro elemento da permutação é o maior possível. Caso exista mais de uma solução satisfazendo essa restrição, imprima, dentre estas, aquela onde o segundo elemento é o maior possível. Caso exista mais de uma solução satisfazendo as duas restrições anteriores, imprima, dentre estas, a solução onde o terceiro elemento é o maior possível, e assim sucessivamente.

Para toda entrada haverá pelo menos uma permutação solução.

A saída deve ser escrita na saída padrão.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int *permutacoes, int esquerda, int meio, int direita){
    int i, j, k;
    int n1 = meio - esquerda + 1; // tamanho do subvetor esquerdo
    int n2 = direita - meio; // tamanho do subvetor direito

    int *L = (int*) malloc(n1 * sizeof(int)); // aloca memória para o subvetor esquerdo
    int *R = (int*) malloc(n2 * sizeof(int)); // aloca memória para o subvetor direito

    for (i = 0; i < n1; i++){
        L[i] = permutacoes[esquerda + i]; // copia os elementos do subvetor esquerdo
    }
    for (j = 0; j < n2; j++){
        R[j] = permutacoes[meio + 1 + j]; // copia os elementos do subvetor direito
    }

    i = 0;
    j = 0;
    k = esquerda;

    while (i < n1 && j < n2){
        if (L[i] <= R[j]){ // compara os elementos dos subvetores
            permutacoes[k] = L[i]; // copia o elemento do subvetor esquerdo
            i++;
        }
        else{
            permutacoes[k] = R[j]; // copia o elemento do subvetor direito
            j++;
        }
        k++;
    }

    while (i < n1){
        permutacoes[k] = L[i]; // copia os elementos restantes do subvetor esquerdo
        i++;
        k++;
    }

    while (j < n2){
        permutacoes[k] = R[j]; // copia os elementos restantes do subvetor direito
        j++;
        k++;
    }

    free(L); // libera a memória alocada para o subvetor esquerdo
    free(R); // libera a memória alocada para o subvetor direito
}

void mergeSort(int *permutacoes, int esquerda, int direita){
    if (esquerda < direita){
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(permutacoes, esquerda, meio); // ordena o subvetor esquerdo
        mergeSort(permutacoes, meio + 1, direita); // ordena o subvetor direito

        merge(permutacoes, esquerda, meio, direita); // combina os subvetores ordenados
    }
}

void sort(int permutacoes[], int N, int M){

    if (M == 0) { // verifica se M é igual a zero
        for (int i = 0; i < N; i++) {
            printf("%i ", i + 1); // imprime o vetor de saída sem fazer nenhuma ordenação
        }
        return;
    }

    int count = M, aux = 0, flag = 0, indice = 0;
    int *vetor = (int*) malloc(N * sizeof(int)); // aloca memória para o vetor de saída

    for (int i = 0; i < N; i++){
        vetor[i] = i + 1; // inicializa o vetor de saída com os valores de 1 a N
    }

    mergeSort(permutacoes, 0, M - 1); // ordena as permutações

    for (int i = 0; i < M; i++){

        for (int j = N - 1; j >= 0; j--){

            if (vetor[j] == count){

                indice = j;

                // realiza a troca dos elementos do vetor de saída
                while (flag < permutacoes[i]){

                    // troca os elementos adjacentes
                    aux = vetor[indice];
                    vetor[indice] = vetor[indice + 1];
                    vetor[indice + 1] = aux;

                    // atualiza os índices
                    flag++;
                    indice++;
                }
            }
        }

        count--;
        flag = 0;
    }

    for (int i = 0; i < N; i++){
        printf("%i ", vetor[i]); // imprime o vetor de saída
    }

    free(vetor); // libera a memória alocada para o vetor de saída
}

int main(){
    
    int n = -1, m = -1;
    while(scanf("%d %d", &n, &m) && n != 0){
        int i, j, k, aux, flag = 0, indice = 0;
        int *permutacoes = (int*) malloc(m * sizeof(int)); // aloca memória para as permutações

        for(i = m - 1; i >= 0; i--){
            scanf("%d", &permutacoes[i]); // lê as permutações
        }

        sort(permutacoes, n, m); // ordena as permutações e imprime o resultado
        printf("\n");

        free(permutacoes); // libera a memória alocada para as permutações
    }

    return 0;
}