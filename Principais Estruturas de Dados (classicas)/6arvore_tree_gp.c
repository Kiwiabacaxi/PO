# include <stdio.h>
# include <stdlib.h>

// árvore binária
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Função para criar um novo nó
struct node* newNode(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// Função para inserir um novo nó na árvore
struct node* insert(struct node* node, int data) {
    // Se a árvore estiver vazia, retorna um novo nó
    if (node == NULL) return newNode(data);

    // Caso contrário, percorre a árvore até encontrar a posição correta
    if (data < node->data)
        node->left  = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    // Retorna o ponteiro para a raiz da árvore
    return node;
}

// Função para percorrer a árvore em ordem
void inorder(struct node* node) {
    if (node == NULL) return;

    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Função para percorrer a árvore em pré-ordem
void preorder(struct node* node) {
    if (node == NULL) return;

    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Função para percorrer a árvore em pós-ordem
void postorder(struct node* node) {
    if (node == NULL) return;

    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}


// Função principal
int main() {
    struct node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf(" \n");

    printf("Preorder traversal: ");
    preorder(root);
    printf(" \n");

    printf("Postorder traversal: ");
    postorder(root);
    printf(" \n");

    return 0;
}
