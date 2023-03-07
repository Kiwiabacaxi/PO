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

// funcao para fazer a rotacao simples a direita
Noavl* rotacao_simples_dir(Noavl* tree){
    Noavl* aux = tree->esq; 
    tree->esq = aux->dir;
    aux->dir = tree;

    return aux;
}

Noavl* rotacao_simples_dir2(Noavl* jorgim){
    Noavl* aux = jorgim->esq; // aux recebe o filho a esquerda do no que vai ser rotacionado
    Noavl* aux2 = aux->dir;
    jorgim->esq = aux2;
    aux->dir = jorgim;


    return aux;
}


// funcao para fazer a rotacao simples a esquerda
Noavl* rotacao_simples_esq(Noavl* tree){
    Noavl* aux = tree->dir; // aux recebe o filho a direita do no que vai ser rotacionado
    tree->dir = aux->esq;   // o filho da direta do no que vai ser rotacionado recebe o filho da esquerda do aux
    aux->esq = tree;        // o aux da esquerda recebe a raiz

    return aux;
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
