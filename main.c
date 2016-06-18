#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int value;
  struct node_t* next;
} node;

typedef node* list;

// returns a pointer of list to the next element
list* next(list* l){
  return &(*l)->next;
}

// returns true if no next more elements exists. false otherwise
int empty(list* l){
  return *l == NULL;
}

// get the value of the first element in the list
int value(list* l){
  return (*l)->value;
}

// remove a specific element from the list. O(n) time complexity
void remove_from_list(list* l, int v){
  if(*l == NULL) return;
  list* it = l;
  while(!empty(next(it)) && value(it) != v) it = next(it);
  if(value(it) == v) {
    node* deleted_node = *it;
    *it = deleted_node->next;
    free(deleted_node);
  }
}

// add a new element to the list at the front. O(1) time complexity
void add_to_list(list* l, int value){
  node* n = (node*)malloc(sizeof(node));
  n->next = (*l);
  n->value = value;
  (*l) = n;
}

// allocates memory to a new list
list* new_list(){
  list* l = (list*)malloc(sizeof(list));
  *l = NULL;
  return l;
}

// delete the list and its elements
void delete_list(list* l){
  list* head = l;
  // remove first element until it is empty
  while(!empty(l)){
    remove_from_list(l, value(l));
  }
  free(head);
}

// print each element in the list with a space separating each element
void print_list(list* l){
  list* it = l;
  while(!empty(it)){
    printf("%d ", value(it));
    it = next(it);
  }
  printf("\n");
}

// split the list in two, returns the start node for the second list
// index deontes the last index of the first list. index should not
// exceed length of list
list split(list l, int index){
  // goto the last element of first list
  while(--index >= 0) l = l->next;
  list second = l->next;
  l->next = NULL;
  return second;
}

list merge(list l1, list l2){
  list* smallest = l1->value > l2->value? &l2 : &l1;
  list result = *smallest;
  list result_last = result;
  *smallest = (*smallest)->next;
  while(l1 != NULL && l2 != NULL){
    smallest = l1->value > l2->value? &l2 : &l1;
    list smallest_next = (*smallest)->next;
    result_last->next = *smallest;
    result_last = result_last->next;
    *smallest = smallest_next;
  }
  // one of the list is empty
  if(l1 != NULL){
    result_last->next = l1;
  } else {
    result_last->next = l2;
  }
  return result;
}

void merge_sort(list* l){
  list it = *l;
  list fst_l = it;
  int length = 0;
  while(it != NULL) { it = it->next; ++length; }
  if(length > 1){
    list snd_l = split(fst_l, length / 2 - 1);
    merge_sort(&fst_l);
    merge_sort(&snd_l);
    *l = merge(fst_l, snd_l);
  }
}


int main(){
  list* l = new_list();

  // 0 -> 1 -> 2 -> 3 -> NULL
  for(int i = 3; i >= 0; --i) {
    add_to_list(l,i);
  }

  // 1 -> 2 -> NULL
  remove_from_list(l, 3);
  remove_from_list(l, 0);

  // 1 -> 2 -> NULL
  remove_from_list(l, 7);

  // 5 -> 1 -> 2 -> NULL
  add_to_list(l, 5);

  print_list(l);

  for (int i = 0; i < 20; ++i){
    add_to_list(l, random() % 100);
  }
  print_list(l);
  merge_sort(l);
  print_list(l);
  delete_list(l);
  return 0;
}
