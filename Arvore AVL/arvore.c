# include <stdlib.h>
# include <stdio.h>

// arvore avl
struct noavl
{
    int info;
    int fb;
    struct noavl *esq, *dir;
    //struct noavl *pai;
};

typedef struct noavl Noavl;

// funcao para criar um no
Noavl* cria_noavl(int info){
    Noavl* novo = (Noavl*) malloc(sizeof(Noavl));
    novo -> dir=novo  ->esq = NULL;
    novo -> info = info;
    novo -> fb = 0;

    return novo;
}

// funcao para calcular o fator de balanceamento
int calcula_fb(Noavl* tree){
    int altura_esq = 0;
    int altura_dir = 0;
    Noavl* aux = tree;

    while(aux->esq != NULL){
        altura_esq++;
        aux = aux->esq;
    }

    aux = tree;
    while(aux->dir != NULL){
        altura_dir++;
        aux = aux->dir;
    }

    return altura_dir - altura_esq;
}

void recalcula_fb(Noavl* candidato, int info){
    Noavl* aux = candidato;             // porque se chegar no final do while, o candidato vai ser nulo

    while(candidato->info != info){     // enquanto o candidato nao for o no que vai ser inserido
        if (info < candidato->info){    // se o no que vai ser inserido for menor que o candidato
            aux->fb--;
            aux = aux->esq;
            
        }
        
        else {
            aux->fb++;
            aux = aux->dir;
        
        }
    
    }
}

// Funcao para calcular a altura de um no
int altura(Noavl *candidato) {
    if (candidato == NULL) {
        return 0;
    }
    return candidato->fb;
}

// Funcao para recalcular o "altura" de um no
void update_fb(Noavl *candidato) {
    int fb_esq= altura(candidato->esq);
    int fb_dir = altura(candidato->dir);
    if (fb_esq > fb_dir) {       // se a altura do filho a esquerda for maior que a altura do filho a direita
        candidato->fb = 1 + fb_esq;     // altura do no = 1 + altura do filho a esquerda
    } else {
        candidato->fb = 1 + fb_dir;    // altura do no = 1 + altura do filho a direita
    }
}

// funcao para fazer a rotacao simples a direita
Noavl* rotacao_simples_dir(Noavl* tree){
    Noavl* aux = tree->esq; 
    tree->esq = aux->dir;
    aux->dir = tree;

    // recalcular o fator de balanceamento primeiro recalcular o fator de balanceamento do filho a direita do no que vai ser rotacionado
    update_fb(tree);
    update_fb(aux);

    return aux;
}

/* 
Noavl* rotacao_simples_dir2(Noavl* jorgim){
    Noavl* aux = jorgim->esq; // aux recebe o filho a esquerda do no que vai ser rotacionado
    Noavl* aux2 = aux->dir;
    jorgim->esq = aux2;
    aux->dir = jorgim;

    // recalcular o fator de balanceamento primeiro recalcular o fator de balanceamento do filho a direita do no que vai ser rotacionado
    update_fb(jorgim);
    update_fb(aux);

    return aux;
} */


// funcao para fazer a rotacao simples a esquerda
Noavl* rotacao_simples_esq(Noavl* tree){
    Noavl* aux = tree->dir; // aux recebe o filho a direita do no que vai ser rotacionado
    tree->dir = aux->esq;   // o filho da direta do no que vai ser rotacionado recebe o filho da esquerda do aux
    aux->esq = tree;        // o aux da esquerda recebe a raiz

    // recalcular o fatro de balanceamento primeiro, recalcular o fator de balanceamento do filho a esquerda do no que vai ser rotacionado
    update_fb(tree);
    update_fb(aux);

    return aux;
}

// funcao para fazer a rotacao esquerda-direita
Noavl* rotacao_esq_dir(Noavl* tree){
    tree->esq = rotacao_simples_esq(tree->esq);
    return rotacao_simples_dir(tree);
}

// funcao para fazer a rotacao esquerda-direita sem usar a funcao de rotacao simples a direita
Noavl* rotacao_esq_dir2(Noavl* tree){
    Noavl* aux = tree->esq; // aux recebe o filho a esquerda do no que vai ser rotacionado
    Noavl* aux2 = aux->dir; // aux2 recebe o filho a direita do aux
    tree->esq = aux2;       // o filho da esquerda do no que vai ser rotacionado recebe o filho da direita do aux
    aux->dir = tree;        // o aux da direita recebe a raiz
    tree = aux;             // a raiz recebe o aux

    // recalcular o fator de balanceamento primeiro, recalcular o fator de balanceamento do filho a direita do no que vai ser rotacionado
    update_fb(tree);
    update_fb(aux);

    return tree;
}

/* // exemplo de rotacao esquerda-direita
Noavl* rotacao_esq_dir3(Noavl* candidato){
    Noavl* filho = candidato->esq;
    Noavl* neto = filho->dir;
    candidato->esq = rotacao_simples_esq(candidato->esq);
    Noavl* nova_raiz = rotacao_simples_dir(candidato);
    
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
} */


// funcao para fazer a rotacao esquerda-direita
Noavl* rotacao_dir_esq(Noavl* tree){
    tree->dir = rotacao_simples_dir(tree->dir);
    return rotacao_simples_esq(tree);
}

// funcao para fazer a rotacao direita-esquerda sem usar a funcao de rotacao simples a esquerda
Noavl* rotacao_dir_esq2(Noavl* tree){
    Noavl* aux = tree->dir; // aux recebe o filho a direita do no que vai ser rotacionado
    Noavl* aux2 = aux->esq; // aux2 recebe o filho a esquerda do aux
    tree->dir = aux2;       // o filho da direita do no que vai ser rotacionado recebe o filho da esquerda do aux
    aux->esq = tree;        // o aux da esquerda recebe a raiz
    tree = aux;             // a raiz recebe o aux

    // recalcular o fator de balanceamento primeiro, recalcular o fator de balanceamento do filho a esquerda do no que vai ser rotacionado
    update_fb(tree);
    update_fb(aux);

    return tree;
}

// funcao para fazer a rotacao dupla a direita
Noavl* rotacao_dupla_dir(Noavl* tree){
    tree->esq = rotacao_simples_esq(tree->esq);
    return rotacao_simples_dir(tree);
}

// funcao para fazer a rotacao dupla a esquerda
Noavl* rotacao_dupla_esq(Noavl* tree){
    tree->dir = rotacao_simples_dir(tree->dir);
    return rotacao_simples_esq(tree);
}

// funcao para fazer a rotacao geral
Noavl* rotacao_geral(Noavl* tree){
    if (tree->fb == -2){
        if (tree->esq->fb == -1)
            return rotacao_simples_dir(tree);
        else
            return rotacao_dupla_dir(tree);
    }
    else{
        if (tree->dir->fb == 1)
            return rotacao_simples_esq(tree);
        else
            return rotacao_dupla_esq(tree);
    }
}



Noavl* insere_no(Noavl* tree, int info, Noavl** pai_candidato){
    Noavl* aux = tree;
    Noavl* pai_aux = NULL;
    Noavl* novo = cria_noavl(info);
    Noavl* candidato = NULL;

    while(aux != NULL){
        if (aux->fb != 0){
               candidato = aux;
               *pai_candidato = pai_aux;
        }
        pai_aux = aux;
        if (info < aux->info)
            aux=aux->esq;
        else
            aux=aux->dir;
    }

    if(info < pai_aux->info)
        pai_aux->esq = novo;
    else
        pai_aux->dir = novo;

    return candidato;
}

void recalculo_final_fb(Noavl* candidato){
    Noavl* aux = candidato;
    while(aux != NULL){
        aux->fb = calcula_fb(aux);
        //aux = aux->pai;
    }
}

Noavl* insercao_geral(Noavl* tree, int info){
    Noavl* candidato=NULL;
    Noavl* pai_candidato = NULL;
    
    if (tree == NULL){              // se a arvore for vazia
        return cria_noavl(info);    // cria um no e retorna
    }

    else{
        candidato = insere_no(tree, info, &pai_candidato); // candidato reccbe o no que vai ser inserido
        recalcula_fb(candidato, info);
        if(candidato->fb == -2 || candidato->fb == +2){
            if (candidato == tree)
                tree = rotacao_geral(candidato);
            else
                if(pai_candidato->esq == candidato)
                    pai_candidato->esq = rotacao_geral(candidato);
                else
                    pai_candidato->dir = rotacao_geral(candidato);
            recalculo_final_fb(candidato);

        }
    }

    return tree;
}








int main (){


    return 0;
}
