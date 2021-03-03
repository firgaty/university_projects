/**
 * @file ast.h
 * @author Félix Desmaretz
 * @brief Abstract Syntax Tree (AST) for parsing
 * and evaluation of command line.
 * @version 0.1
 * @date 2018-12-26
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef SRC_AST_H_
#define SRC_AST_H_

#include "consts.h"
#include "dl_list_str.h"
#include "stdbool.h"

/**
 * @brief Class of an ast_node_t.
 */
typedef enum {
  /*! Not set */
  DEF,
  /*! Command. */
  CMD,
  /*! Boolean 'OR' : || . */
  OR,
  /*! Boolean 'AND' : && . */
  AND,
  /*! Pipe | . */
  PIPE,
  /*! I/O redirection 'stdin'. */
  IN,
  /*! I/O redirection 'stdout'. */
  OUT,
  /*! I/O redirection 'stderr'. */
  ERR,
  /*! char* path to file or folder. */
  PATH,
  // /*! Error node -> invalid ast */
  ERROR
} ast_class_t;

/**
 * @brief Node of the AST
 */
typedef struct ast_node {
  /*! Node class */
  ast_class_t node_class;

  /*! Value of the node, i.e : Symbol or path...*/
  char* value;
  /*! Command */
  dl_list_str_t* args;
  /*! Children nodes */

  struct ast_node* left;
  struct ast_node* right;
} ast_node_t;

/**
 * @brief ast_node_t constructor.
 *
 * @param node_class Class of the node.
 * @param value Value of the node. Can be NULL.
 * @param args Arguments of a command. Can be NULL.
 * @param left Left child node. Can be NULL.
 * @param right Right child node. Can be NULL.
 * @return ast_node_t* Generated node.
 */
ast_node_t* gen_ast_node(ast_class_t node_class,
                         char* value,
                         dl_list_str_t* args,
                         ast_node_t* left,
                         ast_node_t* right);

/**
 * @brief DEF node constructor.
 *
 * @return ast_node_* DEF node.
 */
ast_node_t* gen_default_node();

/**
 * @brief PIPE node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* PIPE node.
 */
ast_node_t* gen_pipe_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief STDIN node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* STDIN node.
 */
ast_node_t* gen_stdin_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief STDOUT node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* STDOUT node.
 */
ast_node_t* gen_stdout_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief STDERR node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* STDERR node.
 */
ast_node_t* gen_stderr_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief OR node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* OR node.
 */
ast_node_t* gen_or_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief AND node constructor.
 *
 * @param left Left child.
 * @param right Right child.
 * @return ast_node_t* AND node.
 */
ast_node_t* gen_and_node(ast_node_t* left, ast_node_t* right);

/**
 * @brief COMMAND node contructor.
 *
 * @param args List of arguments (command included).
 * @return ast_node_t* COMMAND node.
 */
ast_node_t* gen_command_node(dl_list_str_t* args);

/**
 * @brief PATH node constructor.
 *
 * @param value Path value.
 * @return ast_node_t* Path node.
 */
ast_node_t* gen_path_node(char* value);

/**
 * @brief ERROR node constructor.
 *
 * @return ast_node_t* Error node.
 */
ast_node_t* gen_error_node();

/**
 * @brief Frees all allocated memory to tree.
 *
 * @param node Root of the tree.
 */
void ast_tree_free(ast_node_t* root);

/**
 * @brief Frees all allocated memory to a node.
 *
 * @param node NOde to free.
 */
void ast_node_free(ast_node_t* node);

/**
 * @brief Sets a child ast_node_t of parent.
 *
 * @param parent Parent ast_node_t.
 * @param child Child ast_node_t to set.
 * @param is_right Boolean :
 * - 0 sets child as left parent's child.
 * - 1 sets child as right parent's child.
 */
void ast_node_set_child(ast_node_t* parent, ast_node_t* child, int is_right);

/**
 * @brief Sets left child of parent.
 *
 * @param parent Parent ast_node_t.
 * @param child  Child ast_node_t.
 */
void ast_node_set_left_child(ast_node_t* parent, ast_node_t* child);
/**
 * @brief Sets right child of parent.
 *
 * @param parent Parent ast_node_t.
 * @param child  Child ast_node_t.
 */
void ast_node_set_right_child(ast_node_t* parent, ast_node_t* child);

/**
 * @brief Evaluates the AST.
 *
 * @param node Node to evaluate.
 * @return int Execution return value.
 */
int ast_eval(ast_node_t* node);

/**
 * @brief Prints tree.
 *
 * The format is :
 * [ parent->value : ast_print_tree(left_child) ast_print_tree(right_child) ]
 *
 * @param node Node to print.
 */
void ast_print_tree(ast_node_t* node);

/**
 * @brief Checks if the ast is valid.
 *
 * @param node Node to check.
 * @return int 1 if valid, else 0.
 */
int ast_is_valid(ast_node_t* node);

bool contains_pipe(ast_node_t* node);

#endif  // SRC_AST_H_
