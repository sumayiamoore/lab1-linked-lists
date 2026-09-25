// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  node_t *curr = l->head;
  while (curr != NULL) {
    node_t *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(l);
}

void list_print(list_t *l) {
  char *s = listToString(l);
  printf("%s\n", s);
  free(s);
}

#define LIST_STR_BUF_SIZE 1024

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * LIST_STR_BUF_SIZE);
  buf[0] = '\0';
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = getNode(value);

  if (l->head == NULL) {
    l->head = new_node;
    return;
  }

  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = getNode(value);

  /* Insert to front */
  node_t *head = l->head;  // get head of list

  cur_node->next = head;
  l->head = cur_node;
}

/* Allocates a new node on the heap with the given value. */
node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index <= 1 || l->head == NULL) {
    list_add_to_front(l, value);
    return;
  }

  node_t *curr = l->head;
  int i = 1;
  while (curr->next != NULL && i < index - 1) {
    curr = curr->next;
    i++;
  }

  node_t *new_node = getNode(value);
  new_node->next = curr->next;
  curr->next = new_node;
}

/* Removes the last element in the list. Returns -1 if the list is empty. */
elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) {
    return -1;
  }

  node_t *curr = l->head;

  if (curr->next == NULL) {
    elem value = curr->value;
    free(curr);
    l->head = NULL;
    return value;
  }

  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  elem value = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return value;
}

/* Removes the first element in the list. Returns -1 if the list is empty. */
elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) {
    return -1;
  }
  node_t *temp = l->head;
  elem value = temp->value;
  l->head = temp->next;
  free(temp);
  return value;
}

/* Removes the element at the given index (starting at 1).
 * Returns -1 if the list is empty or the index is out of range. */
elem list_remove_at_index(list_t *l, int index) {
  if (l->head == NULL || index < 1 || index > list_length(l)) {
    return -1;
  }

  if (index == 1) {
    return list_remove_from_front(l);
  }

  node_t *curr = l->head;
  int i = 1;
  while (curr->next != NULL && i < index - 1) {
    curr = curr->next;
    i++;
  }

  node_t *to_remove = curr->next;
  if (to_remove == NULL) {
    return -1;
  }

  elem value = to_remove->value;
  curr->next = to_remove->next;
  free(to_remove);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

/* Returns the element at the given index (starting at 1).
 * Returns -1 if the index is out of range. */
elem list_get_elem_at(list_t *l, int index) {
  node_t *curr = l->head;
  int i = 1;
  while (curr != NULL) {
    if (i == index) {
      return curr->value;
    }
    curr = curr->next;
    i++;
  }
  return -1;
}

/* Returns the index of the given value (starting at 1).
 * Returns -1 if the value is not found. */
int list_get_index_of(list_t *l, elem value) {
  node_t *curr = l->head;
  int i = 1;
  while (curr != NULL) {
    if (curr->value == value) {
      return i;
    }
    curr = curr->next;
    i++;
  }
  return -1;
}
