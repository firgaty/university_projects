/**
 * @file dl_list_str.h
 * @brief Header for a double linked list of char*.
 * @version 0.1
 * @date 2018-10-01
 *
 * @copyright Copyright (c) 2018
 *
 */
#ifndef DL_LIST_STR_H
#define DL_LIST_STR_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "consts.h"

/**
 * @brief Node for dl_list_str_t.
 */
typedef struct node_dl_list_t {
    /*! Label of the node. */
    char *label;
    /*! Previous node in the list. */
    struct node_dl_list_t *prev;
    /*! Next node in the list. */
    struct node_dl_list_t *next;
} node_dl_list_t;

typedef struct {
    /*! Head of the list. */
    node_dl_list_t *first;
    /*! Tail of the list. */
    node_dl_list_t *last;
} dl_list_str_t;


/**
 * @brief Adds a node at index.
 *
 * @param target List to add a node to.
 * @param index Postion of new node.
 * @param label Label of new node.
 * @return int 0 if failure else 1.
 */
int dl_list_add_at(dl_list_str_t *target, int index, char *label);

/**
 * @brief Pops the node at index.
 *
 * @param target List to read from.
 * @param index Position of the node.
 * @param addr Where the label is then stored.
 * @return int 0 if failure else 1.
 */
int dl_list_pop_at(dl_list_str_t *target, int index, char **addr);

/**
 * @brief Stores the label of the node at index.
 *
 * @param target List to read from.
 * @param index Position of the node.
 * @param char* label of the target or NULL if target is nonexistent.
 */
char* dl_list_read_at(dl_list_str_t *target, int index);

/**
 * @brief Returns the node at index.
 *
 * @param target List to seek from.
 * @param index Position of the node in the list.
 * @return node_dl_list_t* Node found else NULL.
 */
node_dl_list_t *seek_dl_list_node(dl_list_str_t *target, int index);

/**
 * @brief Checks if list is valid.
 *
 * @param l List to check.
 * @return int 0 if failure else 1.
 */
int dl_list_is_valid(dl_list_str_t *l);

/**
 * @brief Pops the tail of the list.
 *
 * @param target List to pop.
 * @param addr Where to store the poped label.
 * It's a pointer to a string.
 * @return int 0 if failure else 1.
 */
int dl_list_pop_last(dl_list_str_t *target, char **addr);

/**
 * @brief Pops the head of the list.
 *
 * @param target List to pop.
 * @param addr Where to store the poped label.
 * It's a pointer to a string.
 * @return int 0 if failure else 1.
 */
int dl_list_pop_first(dl_list_str_t *target, char **addr);

/**
 * @brief Frees and cleans the list and all it's nodes.
 *
 * @param target List to free.
 */
void dl_list_clean(dl_list_str_t *target);

/**
 * @brief Calculates the size of the list.
 *
 * @param target List to get evaluate the size.
 * @return int Size of the list.
 */
int dl_list_size(dl_list_str_t *target);

/**
 * @brief Prints a list.
 *
 * @param target List to print.
 * @param rev 1 if print in reverse else 0.
 */
void print_dl_list(dl_list_str_t *target, int rev);

/**
 * @brief Prints node.
 *
 * @param n Node to print.
 */
void print_dl_list_node(node_dl_list_t *n);

/**
 * @brief Reads the last node's label.
 *
 * @param target List to target.
 * @return char* label of the target or NULL if target is nonexistent.
 */
char* dl_list_read_last(dl_list_str_t *target);

/**
 * @brief Reads the first node's label.
 *
 * @param target List to target.
 * @return char* label of the target or NULL if target is nonexistent.
 */
char* dl_list_read_first(dl_list_str_t *target);

/**
 * @brief Adds a node at the tail of the list.
 *
 * @param target List to insert into.
 * @param label Label of the node.
 * @return int 0 if error else 1.
 */
int dl_list_add_last(dl_list_str_t *target, char *label);

/**
 * @brief Adds a node at the head of the list.
 *
 * @param target List to insert into.
 * @param label Label of the node.
 * @return int 0 if error else 1.
 */
int dl_list_add_first(dl_list_str_t *target, char *label);

/**
 * @brief Initializes a list.
 *
 * @param first First node (or head).
 * @param last Last node (or tail).
 * @return dl_list_str_t* Generated list.
 */
dl_list_str_t *gen_dl_list(node_dl_list_t *first, node_dl_list_t *last);

/**
 * @brief Initializes a node.
 *
 * @param label Node label.
 * @param prev Previous node.
 * @param next Next node.
 * @return node_dl_list_t* Generated node.
 */
node_dl_list_t *gen_dl_list_node(
    char *label,
    node_dl_list_t *prev,
    node_dl_list_t *next);

/**
 * @brief Appends a copy of main to copy.
 *
 * @param main List to copy from.
 * @param copy List to copy to.
 * @return int 0 if failure, else 1.
 */
int dl_list_append_copy(dl_list_str_t *main, dl_list_str_t *copy);

/**
 * @brief Prints list
 *
 * @param list List to put into string.
 * @param separator To put between each node of the list.
 * If NULL, it will default to be a space.
 * @param rev List will be writen in reverse if value different of 0.
 * @return String or NULL if empty list.
 */
char *dl_list_str_to_string(dl_list_str_t *list, char *separator, int rev);

/**
 * @brief Gets an array of strings from the dl_list_str_t
 *
 * @param list List to get an array from.
 * @param rev 1 reverse, else in normal order.
 * @return char** Array of node labels or NULL if empty list.
 */
char **dl_list_str_to_string_array(dl_list_str_t *list, int rev);

#endif // DL_LIST_STR_H_
