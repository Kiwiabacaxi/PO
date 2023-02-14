#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *item;
  struct node *next;
} Node;

typedef struct {
  Node *head;
  int size;
} List;

void init(List *list) {
  list->head = NULL;
  list->size = 0;
}

void add(List *list, void *item) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->item = item;
  node->next = list->head;
  list->head = node;
  list->size++;
}

void *get(List *list, int index) {
  if (index < 0 || index >= list->size) {
    return NULL;
  }

  Node *node = list->head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  return node->item;
}

int main() {
    // lista de inteiros
    List list;
    init(&list);
    int a = 10;
    int b = 20;
    int c = 30;
    add(&list, &a);
    add(&list, &b);
    add(&list, &c);

    printf("%d ", *(int *)get(&list, 0));
    printf("%d ", *(int *)get(&list, 1));
    printf("%d ", *(int *)get(&list, 2));

    // lista de strings
    List list2;
    init(&list2);
    char *s1 = "abc";
    char *s2 = "def";
    char *s3 = "ghi";
    add(&list2, s1);
    add(&list2, s2);
    add(&list2, s3);

    printf("%s ", (char *)get(&list2, 0));
    printf("%s ", (char *)get(&list2, 1));
    printf("%s ", (char *)get(&list2, 2));

    

    return 0;
}