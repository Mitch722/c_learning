#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 128

typedef struct list_node{
  int val;
  char string_arr[STR_LEN];
  struct list_node * next;
  struct list_node * prev;

  struct list_node * a_key;
  struct list_node * d_key;

} node_t;

typedef struct{
  
  node_t *head;
  unsigned int count;
  
} list_t;


/**
 *  Creates and initialises a list.
 **/
list_t *create_list(){
  //TODO
  
  list_t *new_list_pointer;
  new_list_pointer = (list_t *) malloc(sizeof(list_t));

  // *first_node_pointer = Null;

  new_list_pointer -> head = NULL;
  new_list_pointer -> count = 0;

  return new_list_pointer;
}

/**
 *  Destroys the list, including the stored nodes.
 **/
void destroy_list(list_t *list){
  //TODO
  node_t *current_node;
  node_t *next_node;

  current_node = list->head;

  while (current_node->next == NULL){
    next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  free(current_node);
  free(list);
}

/**
 *  Appends to the end of the list and adds links to the previous nodes
 **/
void append_list(list_t *list, int new_val, char strg_for_cpy[STR_LEN], int prev_node_val, char which_ptr){
  
  // condit.: head node is unitialized
  if ( list->head == NULL){
    list->head = (node_t *) malloc(sizeof(node_t));
    list->head->val = new_val;

    list->head->next = NULL;
    list->head->a_key = NULL;
    list->head->d_key = NULL;

    strcpy(list->head->string_arr, strg_for_cpy);
  }
  // condit.: list exists append to end of current list
  else {

    node_t * node;
    node = list->head;

    while (node->next != NULL){
      node = node->next;
    }
    node->next = (node_t *) malloc(sizeof(node_t));
    node_t *new_node;

    new_node = node->next;
    new_node->val = new_val;
    strcpy(new_node->string_arr, strg_for_cpy);

    new_node->next = NULL;
    // initially set a and d key pointers to NULL
    new_node->a_key = NULL;
    new_node->d_key = NULL;
    // search for prev_node_val
    node = list->head;
    while (node->val != prev_node_val){
      node = node->next;
    }
    // allows movement up the tree
    new_node->prev = node;

    if (which_ptr == 'a'){
      node->a_key = new_node;
    }
    else if (which_ptr == 'd'){
      node->d_key = new_node;
    }
    else{
      printf("which_ptr must either be a or d\n");
    }

    // printf("%s\n", new_node->string_arr);
  }
  list->count += 1;
}
/**
 *  Appends to the end of the list and makes a_key and d_key NULL pointers
 **/
void append_list_no_links(list_t *list, int new_val, char strg_for_cpy[STR_LEN]){
  // fulfill case of a new list
  if ( list->head == NULL){
    list->head = (node_t *) malloc(sizeof(node_t));
    list->head->val = new_val;

    list->head->next = NULL;
    list->head->a_key = NULL;
    list->head->d_key = NULL;

    strcpy(list->head->string_arr, strg_for_cpy);
  }
  else {
    node_t *node;
    node_t *new_node;

    node = list->head;

    while (node->next != NULL){
      node = node->next;
    }
    node->next = (node_t *) malloc(sizeof(node_t));
    new_node = node->next;

    new_node->next = NULL;
    new_node->a_key = NULL;
    new_node->d_key = NULL;
  }
  list->count += 1;
}

/**
 * add links to a_key and d_key to existing list
 **/
void update_links(list_t *list, int node_val, int target_val, char which_link){

  node_t *node;
  node = list->head;

  node_t *target_node;
  target_node = list->head;
  // find the node you want to create links from
  while (node->val != node_val){
    node = node->next;
  }
  // find the node you want to links to go to
  while (target_node->val != target_val){
    target_node = target_node->next;
  }
  if (which_link == 'a'){
    node->a_key = target_node;
  }
  else if (which_link == 'd'){
    node->d_key = target_node;
  }
  else {
    printf("which_link must either be a or d\n");
  }
}

/**
 *  Returns the ith value in the list
 **/
int get_ith_value(list_t *list, int i){
  //TODO
  node_t *node;
  node = list->head;

  int count;
  count = 0;

  while(count != i){

    node = node->next;
    if (node -> next == NULL){
      printf("There are not %d nodes, only %d nodes\n", i, count+1);
      return -1;
    }
    count += 1;
  }

  return node->val;
}
/**
*  Checks that all the a_key and d_key nodes are not null, returns 0 if all the 
**/
int check_null_a_d(list_t *list){
  node_t *node;
  node = list->head;
  int test_val;
  test_val = 0;

  while (node->next != NULL){
    if (node->a_key == NULL){
      printf("This node with val = %u has a_key being NULL\n", node->val);
      test_val = -1;
    }
    if (node->d_key == NULL){
      printf("This node with val = %u has d_key being NULL\n", node->val);
      test_val = -1;
    }

    node = node->next;
  }
  return test_val;
}

/**
 * main loop: build linked-list and connections between nodes
 **/
int main(void) {

  list_t *list = create_list();
  // build linked-list
  append_list_no_links(list, 1, "You are in the atrium enter room on left or right [a/d]");
  append_list(list, 2, "Here is the Dragon press [a] to slay the dragon or [d] to run away", 1, 'a');
  append_list(list, 3, "There is a chest and a door: open chest [d], go through door [a]", 1, 'd');
  append_list(list, 4, "Chest contains a sword, enter [a] for right door or [d] for hallway", 3, 'd');
  append_list(list, 5, "Dungeon, enter [a] or [d] to return to beginning", 3, 'a');

  update_links(list, 4, 2, 'd');
  update_links(list, 4, 5, 'a');

  update_links(list, 5, 1, 'a');
  update_links(list, 5, 1, 'd');

  update_links(list, 2, 1, 'a');
  update_links(list, 2, 1, 'd');
  // check nullity of the connections
  int null_check = check_null_a_d(list);
  if (null_check == -1){
    printf("Exit due to nullity fail\n");
    return 1;
  }

  // begin the game part of the nodes
  node_t *node;

  node = list->head;

  unsigned int completion = 0;
  unsigned int dragon = 0;
  // begin the game with a statement
  printf("\nWelcome to the Castle, your job is to find the Treasure!\n\n\
A Dragon guards the Treasure, so find the sword and slay it\n\n\
Press key a, key d, then return to navigate or q to quit\n\n");

  char c;
  while (completion <= 1 && dragon <=1){

    printf("%s \n ", node->string_arr);

    scanf(" %c", &c);

    if (c == 'a'){
      node = node->a_key;
    }
    if (c =='d'){
      node = node->d_key;
    }
    if (c =='q'){
      destroy_list(list);
      return 0;
    }

    if (node->val == 2 && completion == 0){
      printf("\nYou found the dragon but not the sword and hence died: you are returned to the atrium\n");
      node = list->head;
    }
    if (node->val == 4){
      completion += 1;
    }
    if (node->val == 2 && completion >= 1){
      break;
    }

  }
  
  printf("You have found the dragon's lair and have the sword press [a] to slay the Dragon \n");
  scanf(" %c", &c);

  if (c == 'a'){
    printf("You have slayed the Dragon and won the game! \n");
  }

  destroy_list(list);
  
  return 0;
}
