#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int value;
  struct node_t* next;
} node;

typedef node* list;

void remove_from_list(list* l, int value){
  if(*l == NULL) return;
  node** it = l;
  while((*it)->next && (*it)->value != value) it = &(*it)->next;
  if((*it)->value == value) {
    node* deleted_node = *it;
    *it = deleted_node->next;
    free(deleted_node);
  }
}

void add_to_list(list* l, int value){
  node* n = (node*)malloc(sizeof(node));
  n->next = (*l);
  n->value = value;
  (*l) = n;
}

list* new_list(){
  list* l = (list*)malloc(sizeof(list));
  *l = NULL;
  return l;
}

int main(){
  list* l = new_list();
  // 0 -> 1 -> 2 -> 3 -> NULL
  for(int i = 3; i >= 0; --i) add_to_list(l,i);

  // 1 -> 2 -> NULL
  remove_from_list(l, 3);
  remove_from_list(l, 0);

  // 1 -> 2 -> NULL
  remove_from_list(l, 7);

  // print the list (and remove elements)
  while(*l != NULL){
    printf("%d\n", (*l)->value);
    remove_from_list(l, (*l)->value);
  }

  free(l);
  return 0;
}