#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    if(a > b)
        return a;
    return b;
}


// Função de comparação usada para ordenar o array "a" em ordem decrescente
int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}


int main() {

    // Lê o número de casos de teste
    int T;
    scanf("%d ", &T);

    while(T--) {
        // Lê o número de elementos do array "a"
        int n;
        scanf("%d", &n);

        int resposta = 0;
        int vetor[222222];
        memset(vetor, 0, sizeof(vetor)); // Inicializa todos os elementos do array "a" com zero
        
        // inic

        int parente, aux = 0;

        // Loop para preencher o array "a" e contar o número de elementos distintos
        for(int i = 1; i < n; i++) {
            scanf("%d", &parente);
            // Se o elemento "t-1" do array "a" for zero, então incrementa o número de elementos distintos
            // se na segunda linha digitar 1 o num sobe na hora
            if(vetor[parente-1] == 0){
                aux++;
            }
            vetor[parente-1]++;
        }

        qsort(vetor, n, sizeof(int), cmp); // Ordena o array "a" em ordem decrescente

        int maior = 0, index_maior; // "m" é o maior número de elementos iguais, "mi" é o índice correspondente
        int len = 0; // "len" é o número de elementos não nulos em "a"

        // Loop para determinar o número máximo de elementos iguais "m" e seu índice "mi",
        // bem como o número de elementos não nulos "len"
        for(int i = 0; i < n; i++) {
            if(vetor[i] > 0) {
                vetor[i] -= aux - i;
                vetor[i] = max(0, vetor[i]);
                resposta++;

                if(vetor[i] > maior) {
                    maior = vetor[i];
                    index_maior = i;
                }
                
            }

            if(vetor[i] > 0){
                len++;
            }
        }

        qsort(vetor, n, sizeof(int), cmp); // Ordena o array "a" em ordem decrescente novamente

        // Loop para adicionar elementos ao conjunto, onde cada elemento tem um número diferente de outros elementos adicionados anteriormente
        while(maior > 0) {
            maior = 0;
            index_maior = 0;

            for(int i = 0; i < len; i++) {
                if(vetor[i] > 0) {
                    vetor[i]--;

                    if(vetor[i] > maior) {
                        maior = vetor[i];
                        index_maior = i;
                    }
                }
            }

            if(maior > 0) {
                maior--;
                vetor[index_maior]--;
                resposta++;
            }
        }

        printf("%d", resposta + 1); // Adiciona 1 ao resultado final
        printf("\n");
    }

    return 0;
}
