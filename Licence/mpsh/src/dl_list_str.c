/**
 * @file dl_list_str.c
 * @author Félix Desmaretz
 * @brief Source file for a Double Linked List
 * of strings.
 * @version 0.1
 * @date 2018-12-26
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "dl_list_str.h"

node_dl_list_t *gen_dl_list_node(char *label, node_dl_list_t *prev,
                                 node_dl_list_t *next) {
  node_dl_list_t *out = malloc(sizeof(node_dl_list_t));
  char *str = malloc(strlen(label) + 1);
  strcpy(str, label);
  if (out != NULL) {
    out->label = str;
    out->next = next;
    out->prev = prev;
  }
  return out;
}

dl_list_str_t *gen_dl_list(node_dl_list_t *first, node_dl_list_t *last) {
  dl_list_str_t *out = malloc(sizeof(dl_list_str_t));
  if (out != NULL) {
    out->first = first;
    out->last = last;
  }
  return out;
}

int dl_list_add_first(dl_list_str_t *target, char *label) {
  if (target == NULL)
    return 0;

  node_dl_list_t *n = NULL;

  if (target->first == NULL) {
    n = gen_dl_list_node(label, NULL, NULL);
    target->last = n;
  } else {
    n = gen_dl_list_node(label, NULL, target->first);
    target->first->prev = n;
  }

  target->first = n;

  return 1;
}

int dl_list_add_last(dl_list_str_t *target, char *label) {
  if (target == NULL)
    return 0;

  node_dl_list_t *n = NULL;

  if (target->last == NULL) {
    n = gen_dl_list_node(label, NULL, NULL);
    target->first = n;
  } else {
    n = gen_dl_list_node(label, target->last, NULL);
    target->last->next = n;
  }

  target->last = n;

  return 1;
}

char *dl_list_read_first(dl_list_str_t *target) {
  if (target == NULL || target->first == NULL)
    return NULL;
  return target->first->label;
}

char *dl_list_read_last(dl_list_str_t *target) {
  if (target == NULL || target->last == NULL)
    return NULL;
  return target->last->label;
}

void print_dl_list_node(node_dl_list_t *n) { printf("> %s <", n->label); }

void print_dl_list(dl_list_str_t *target, int rev) {
  if(target == NULL) printf("NULL pointer");
  if (target == NULL || target->first == NULL || target->last == NULL) {
    printf("NULL list. \n");
    return;
  }

  printf("|");

  if (!rev) {
    node_dl_list_t *n = target->first;
    do {
      print_dl_list_node(n);
      n = n->next;
    } while (n != NULL);
  } else {
    node_dl_list_t *n = target->last;
    do {
      print_dl_list_node(n);
      n = n->prev;
    } while (n != NULL);
  }

  printf("|\n");
}

int dl_list_size(dl_list_str_t *target) {
  if (target == NULL || target->last == NULL || target->first == NULL)
    return 0;
  int i = 0;
  node_dl_list_t *n = target->first;

  do {
    i++;
    n = n->next;
  } while (n != NULL);

  return i;
}

void dl_list_clean(dl_list_str_t *target) {
  if (target == NULL || target->first == NULL || target->last == NULL)
    return;

  node_dl_list_t *n = target->first, *m = NULL;
  do {
    m = n->next;
    free(n);
    n = m;
  } while (n != NULL);

  free(target);
}

int dl_list_pop_first(dl_list_str_t *target, char **addr) {
  if (target == NULL || target->first == NULL)
    return 0;

  if (target->first == target->last) {
    free(target->first);
    target->first = NULL;
    target->last = NULL;

    return 1;
  }

  target->first = target->first->next;
  free(target->first->prev);
  target->first->prev = NULL;

  return 1;
}

int dl_list_pop_last(dl_list_str_t *target, char **addr) {
  if (target == NULL || target->last == NULL)
    return 0;

  if (target->last == target->first) {
    free(target->last);
    target->last = NULL;
    target->first = NULL;

    return 1;
  }

  target->last = target->last->prev;
  free(target->last->next);
  target->last->next = NULL;

  return 1;
}

int dl_list_is_valid(dl_list_str_t *l) {
  return !(l == NULL || l->first == NULL || l->last == NULL);
}

node_dl_list_t *seek_dl_list_node(dl_list_str_t *target, int index) {
  if (!dl_list_is_valid(target))
    return NULL;

  node_dl_list_t *n;

  if (index >= 0) {
    n = target->first;

    for (int i = 0; i < index; i++) {
      if (n->next == NULL)
        return NULL;
      n = n->next;
    }
    return n;
  }

  n = target->last;

  for (int i = 1; i < -index; i++) {
    if (n->prev == NULL)
      return NULL;
    n = n->prev;
  }
  return n;
}

char *dl_list_read_at(dl_list_str_t *target, int index) {
  node_dl_list_t *n = seek_dl_list_node(target, index);
  if (n == NULL)
    return NULL;
  // addr = n->label;
  return n->label;
}

int dl_list_pop_at(dl_list_str_t *target, int index, char **addr) {
  node_dl_list_t *n = seek_dl_list_node(target, index);
  if (n == NULL)
    return 0;

  if (n->prev == NULL)
    return dl_list_pop_first(target, addr);
  if (n->next == NULL)
    return dl_list_pop_last(target, addr);

  n->prev->next = n->next;
  n->next->prev = n->prev;
  *addr = n->label;
  free(n);
  return 1;
}

int dl_list_add_at(dl_list_str_t *target, int index, char *label) {
  node_dl_list_t *n = seek_dl_list_node(target, index);
  if (n == NULL)
    return 0;

  if (n->prev == NULL)
    return dl_list_add_first(target, label);
  if (n->next == NULL)
    return dl_list_add_last(target, label);

  node_dl_list_t *new_node = gen_dl_list_node(label, n->prev, n);
  n->prev->next = new_node;
  n->prev = new_node;

  return 1;
}

int dl_list_append_copy(dl_list_str_t *main, dl_list_str_t *copy) {
  // TODO(firgaty) test if function works properly.
  if (main->first == NULL)
    return 0;

  node_dl_list_t *n = main->first;
  char tmp[BUFFER];

  for (; ((n)); n = n->next) {
    snprintf(tmp, sizeof(BUFFER), "%s", n->label);
    dl_list_add_last(copy, tmp);
  }
  return 1;
}

char *dl_list_str_to_string(dl_list_str_t *list, char *separator, int rev) {
  if (list == NULL || list->first == NULL || list->last == NULL) {
    printf("NULL list. \n");
    return NULL;
  }

  if (separator == NULL)
    separator = " ";

  char *str = malloc(sizeof(char) * BUFFER);
  int buffer_size = 1;
  node_dl_list_t *n = rev ? list->last : list->first;

  do {
    if (strlen(str) + strlen(n->label) + strlen(separator) >=
        (size_t)(BUFFER * buffer_size)) {
      buffer_size++;
      str = realloc(str, BUFFER * buffer_size);
    }
    strcat(str, n->label);
    n = rev ? n->prev : n->next;
    if (n != NULL)
      strcat(str, separator);
  } while (n != NULL);

  return str;
}

char **dl_list_str_to_string_array(dl_list_str_t *list, int rev) {
  if (list == NULL || list->first == NULL || list->last == NULL) {
    printf("NULL list. \n");
    return NULL;
  }
  char **array = malloc(sizeof(char *) * (dl_list_size(list) + 1));
  int i = 0;

  for (node_dl_list_t *n = rev ? list->last : list->first; n != NULL;
       n = rev ? n->prev : n->next, i++) {
    array[i] = malloc(sizeof(char) * strlen(n->label) + 1);
    strcpy(array[i], n->label);
  }
  array[i] = malloc(sizeof(char));
  array[i] = NULL;
  return array;
}
