/**
 * @file ast.c
 * @author Félix Desmaretz
 * @brief Source file for the AST.
 * @version 0.1
 * @date 2018-12-27
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "ast.h"

ast_node_t* gen_ast_node(ast_class_t node_class,
                         char* value,
                         dl_list_str_t* args,
                         ast_node_t* left,
                         ast_node_t* right) {
  ast_node_t* node = malloc(sizeof(ast_node_t));
  node->node_class = node_class;
  node->value = value;
  node->args = malloc(sizeof(dl_list_str_t));
  node->args = gen_dl_list(NULL, NULL);
  node->left = malloc(sizeof(ast_node_t));
  node->left = left;
  node->right = malloc(sizeof(ast_node_t));
  node->right = right;
  return node;
}

ast_node_t* gen_default_node() {
  // TODO(firgaty) : implement static DEF node for memory.
  return gen_ast_node(DEF, NULL, NULL, NULL, NULL);
}

ast_node_t* gen_pipe_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(PIPE, "|", NULL, left, right);
}

ast_node_t* gen_stdin_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(IN, "<", NULL, left, right);
}

ast_node_t* gen_stdout_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(OUT, ">", NULL, left, right);
}

ast_node_t* gen_stderr_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(ERR, "2>", NULL, left, right);
}

ast_node_t* gen_or_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(OR, "||", NULL, left, right);
}

ast_node_t* gen_and_node(ast_node_t* left, ast_node_t* right) {
  return gen_ast_node(AND, "&&", NULL, left, right);
}

ast_node_t* gen_command_node(dl_list_str_t* args) {
  if (!(args)) {
    return gen_ast_node(CMD, NULL, gen_dl_list(NULL, NULL), NULL, NULL);
  }
  return gen_ast_node(CMD, NULL, args, NULL, NULL);
}

ast_node_t* gen_path_node(char* value) {
  char* tmp = malloc(sizeof(value) + 1);
  strcpy(tmp, value);
  return gen_ast_node(PATH, tmp, NULL, NULL, NULL);
}

ast_node_t* gen_error_node() {
  return gen_ast_node(ERROR, "Error", NULL, NULL, NULL);
}

void ast_tree_free(ast_node_t* root) {
  if (!(root))
    return;
  if ((root->args)) {
    dl_list_clean(root->args);
    free(root->args);
  }
  if ((root->left)) {
    ast_tree_free(root->left);
    free(root->left);
  }
  if ((root->right)) {
    ast_tree_free(root->right);
    free(root->right);
  }
  if ((root->value)) {
    free(root->value);
  }
  free(root);
}

void ast_node_free(ast_node_t* node) {
  if (!(node))
    return;
  if ((node->args)) {
    dl_list_clean(node->args);
    free(node->args);
  }
  if ((node->left)) {
    free(node->left);
  }
  if ((node->right)) {
    free(node->right);
  }
  if ((node->value)) {
    free(node->value);
  }
  free(node);
}

void ast_node_set_child(ast_node_t* parent, ast_node_t* child, int is_right) {
  if (is_right)
    parent->right = child;
  else
    parent->left = child;
}

void ast_node_set_left_child(ast_node_t* parent, ast_node_t* child) {
  ast_node_set_child(parent, child, FALSE);
}

void ast_node_set_right_child(ast_node_t* parent, ast_node_t* child) {
  ast_node_set_child(parent, child, TRUE);
}

int ast_eval(ast_node_t* node) {
  // TODO(firgaty) finish ast_eval.

  return EXIT_SUCCESS;
}

void ast_print_tree(ast_node_t* node) {
  if (!(node)) {
    printf("NULL");
    return;
  }
  printf("[ %d: ", node->node_class);
  ast_print_tree(node->left);
  printf(" :: ");
  ast_print_tree(node->right);
  printf(" ]\n");
}

int ast_is_valid(ast_node_t* node) {
  switch (node->node_class) {
    case ERROR:
    case DEF:
      return FALSE;
      break;
    case CMD:
      return TRUE;
      break;
    case OR:
    case AND:
    case PIPE:
      return node->left != NULL && ast_is_valid(node->left) &&
             node->right != NULL && ast_is_valid(node->right);
      break;
    default:
      return FALSE;
  }
}

bool contains_pipe(ast_node_t* node) {
  return node == NULL ? false
                      : node->node_class == PIPE || node->right == NULL
                            ? false
                            : contains_pipe(node->right) || node->left == NULL
                                  ? false
                                  : contains_pipe(node->left);
}