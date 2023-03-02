# include <stdlib.h>
# include <stdio.h>

// Arvore AVL
typedef struct AVL_Tree {
    int key;
    int height;
    struct AVL_Tree *left;
    struct AVL_Tree *right;
} AVL_Tree;

// Funcao para criar um novo no
AVL_Tree *create_node(int key) {
    AVL_Tree *new_node = (AVL_Tree *) malloc(sizeof(AVL_Tree));
    new_node->key = key;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Funcao para calcular a altura de um no
int height(AVL_Tree *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Funcao para calcular o fator de balanceamento de um no
int balance_factor(AVL_Tree *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Funcao para atualizar a altura de um no
void update_height(AVL_Tree *node) {
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right)); // altura do no = 1 + maior altura entre os filhos
}

// Funcao para atualizar a altura de um no sem usar operador ternario
void update_height2(AVL_Tree *node) {
    int left_height = height(node->left);
    int right_height = height(node->right);
    if (left_height > right_height) {       // se a altura do filho a esquerda for maior que a altura do filho a direita
        node->height = 1 + left_height;     // altura do no = 1 + altura do filho a esquerda
    } else {
        node->height = 1 + right_height;    // altura do no = 1 + altura do filho a direita
    }
}



// Funcao para realizar uma rotacao simples a direita
AVL_Tree *right_rotation(AVL_Tree *node) {
    AVL_Tree *aux = node->left;
    node->left = aux->right;
    aux->right = node;
    update_height(node);
    update_height(aux);
    return aux;
}

// Funcao para realizar uma rotacao simples a esquerda
AVL_Tree *left_rotation(AVL_Tree *node) {
    AVL_Tree *aux = node->right;
    node->right = aux->left;
    aux->left = node;
    update_height(node);
    update_height(aux);
    return aux;
}

// Funcao para realizar uma rotacao dupla a direita
AVL_Tree *double_right_rotation(AVL_Tree *node) {
    node->left = left_rotation(node->left);
    return right_rotation(node);
}

// Funcao para realizar uma rotacao dupla a esquerda
AVL_Tree *double_left_rotation(AVL_Tree *node) {
    node->right = right_rotation(node->right);
    return left_rotation(node);
}

// Funcao para inserir um no na arvore
AVL_Tree *insert(AVL_Tree *node, int key) {
    if (node == NULL) {
        return create_node(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }
    update_height(node);
    int balance = balance_factor(node);
    if (balance > 1 && key < node->left->key) {
        return right_rotation(node);
    }
    if (balance < -1 && key > node->right->key) {
        return left_rotation(node);
    }
    if (balance > 1 && key > node->left->key) {
        return double_right_rotation(node);
    }
    if (balance < -1 && key < node->right->key) {
        return double_left_rotation(node);
    }
    return node;
}

// Funcao para imprimir a arvore em ordem
void print_in_order(AVL_Tree *node) {
    if (node != NULL) {
        print_in_order(node->left);
        printf("%d ", node->key);
        print_in_order(node->right);
    }
}

// Funcao para imprimir a arvore em pre ordem
void print_pre_order(AVL_Tree *node) {
    if (node != NULL) {
        printf("%d ", node->key);
        print_pre_order(node->left);
        print_pre_order(node->right);
    }
}

// Funcao para imprimir a arvore em pos ordem
void print_post_order(AVL_Tree *node) {
    if (node != NULL) {
        print_post_order(node->left);
        print_post_order(node->right);
        printf("%d ", node->key);
    }
}

// Funcao para imprimir a arvore em niveis
void print_by_level(AVL_Tree *node) {
    int i, j, height = node->height;
    AVL_Tree *queue[100];
    queue[0] = node;
    for (i = 0; i < height; i++) {
        for (j = 0; j < (1 << i); j++) {
            printf("%d ", queue[j]->key);
            if (queue[j]->left != NULL) {
                queue[(1 << i) + j] = queue[j]->left;
            }
            if (queue[j]->right != NULL) {
                queue[(1 << i) + j + 1] = queue[j]->right;
            }
        }
        printf("\n");
    }
}

// Funcao para imprimir o factor de balanceamento de cada no em niveis
void print_balance_factor_by_level(AVL_Tree *node) {
    int i, j, height = node->height;
    AVL_Tree *queue[100];
    queue[0] = node;
    for (i = 0; i < height; i++) {
        for (j = 0; j < (1 << i); j++) {
            printf("%d ", balance_factor(queue[j]));
            if (queue[j]->left != NULL) {
                queue[(1 << i) + j] = queue[j]->left;
            }
            if (queue[j]->right != NULL) {
                queue[(1 << i) + j + 1] = queue[j]->right;
            }
        }
        printf("\n");
    }
}

// Funcao para imprimir o factor de balanceamento de cada no
void print_balance_factor(AVL_Tree *node) {
    if (node != NULL) {
        print_balance_factor(node->left);
        printf("%d ", balance_factor(node));
        print_balance_factor(node->right);
    }
}

// Funcao para liberar a memoria alocada para a arvore
void free_tree(AVL_Tree *node) {
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

// function wich draws the tree upside down
void draw_tree(AVL_Tree *node, int level) {
    if (node != NULL) {
        draw_tree(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("\t");
        }
        printf("%d (%d) \n", node->key, balance_factor(node));
        draw_tree(node->left, level + 1);
    }
}



int main() {
    AVL_Tree *root = NULL;
    int i, key, key2;
    int keystore[10];
    for (i = 0; i < 10; i++) {
        key = rand() % 100;
        keystore[i] = key;
        printf("Botando %d\n", key);
        root = insert(root, key);
    }
    // ordem original
    printf("Original order: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", keystore[i]);
    }

    printf("\nIn order: ");
    print_in_order(root);

    printf("\nPre order: ");
    print_pre_order(root);
    
    printf("\nPost order: ");
    print_post_order(root);

    printf("\nBalance factor: ");
    print_balance_factor(root);

    printf("\nBalance factor by level: \n");
    print_balance_factor_by_level(root);
    
    printf("\nBy level: \n");
    print_by_level(root);

    printf("\nTree: \n");
    draw_tree(root, 0);

    free_tree(root);
    return 0;
}
