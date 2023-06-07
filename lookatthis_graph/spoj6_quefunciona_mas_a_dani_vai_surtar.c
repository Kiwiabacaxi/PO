#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 21

int grafo[MAXN][MAXN];
int grafo_size[MAXN];

char atributos[MAXN][MAXN][21];
int atributos_size[MAXN];

int processado[MAXN];

int t1, t2, n;
char a1[21], a2[21], a3[21];

void dfs(int x) {
    processado[x] = 1;
    atributos_size[x]--;

    if (grafo_size[x] < t1)
        strcpy(atributos[x][atributos_size[x]++], a1);
    else if (grafo_size[x] < t2)
        strcpy(atributos[x][atributos_size[x]++], a2);
    else
        strcpy(atributos[x][atributos_size[x]++], a3);

    for (int i = 0; i < grafo_size[x]; i++) {
        int v = grafo[x][i];
        if (processado[v] == 0) dfs(v);
    }
}

int main() {
    while (scanf("%d", &n) && n != 0) {
        memset(grafo_size, 0, sizeof(grafo_size));
        memset(atributos_size, 0, sizeof(atributos_size));

        for (int i = 1; i <= n; i++) {
            int j;
            while (scanf("%d", &j) && j != 0) {
                grafo[i][grafo_size[i]++] = j;
            }
        }

        int ini = 0;

        while (scanf("%d", &ini) && ini != 0) {

            scanf("%d %d %s %s %s", &t1, &t2, a1, a2, a3);

            for (int i = 1; i <= n; i++) {
                processado[i] = 0;
                strcpy(atributos[i][atributos_size[i]++], a1);
            }
            dfs(ini);
        }

        for (int i = 1; i <= n; i++) {
            char nome[21];
            scanf("%s", nome);

            printf("%s: ", nome);

            for (int j = 0; j < atributos_size[i]; j++) {
                printf("%s ", atributos[i][j]);
            }
            printf("\n");
        }

    }
    return 0;
}