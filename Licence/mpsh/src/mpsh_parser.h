/**
 * @file mpsh_parser.h
 * @author Félix Desmaretz
 * @brief File for the line parsing functions.
 * @version 0.1
 * @date 2019-01-01
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MPSH_PARSER_H_
#define MPSH_PARSER_H_

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "consts.h"
#include "dl_list_str.h"
#include "env.h"
#include "scan.h"
#include "token.h"
#include "vars_scan.h"

/**
 * @brief Main parsinn function.
 *
 * @param line Line to parse.
 * @return char** Line split into char* tokens.
 */
ast_node_t** parse_line(char* line, env_t* env);

/**
 * @brief Parses the line for vars.
 *
 * @param line Line to parse.
 * @return dl_list_str_t* List of vars in the line.
 */
dl_list_str_t* parse_vars(char* line);

/**
 * @brief Replace!(mpsh_exec_bis(ast->left, env) == EXIT_SUCCESS &&s command if the
 * alias was set.             mpsh_exec_bis(ast->right, env) == EXIT_SUCCESS)
 *
 * @param str Alias to look for.
 * @param env Envirnment of MPSH.
 * @return char* The command of the alias or the alias if not set.
 */
char* replace_alias(char* str, env_t* env);

/**
 * @brief Replaces the vars in the string.
 *
 * @param line String to work onto.
 * @param env MPSH environment.
 * @return char* line with vars replaced by their value.
 */
char* replace_vars(char* line, env_t* env);

/**
 * @brief Replaces a substring sub of str by rep.
 *
 * @param str String to work onto.
 * @param sub Substring to replace.
 * @param rep String to use as replacement.
 * @return char* str with substring replaced.
 */
char* replace_str(char* str, char* sub, char* rep);

/**
 * @brief Homebrewed strstr() equivalent which finds a
 * substring in a string if not quoted.
 *
 * @param str Haystack
 * @param substr Needle
 * @return char* A pointer to the substring or NULL.
 */
char* mpsh_strstr(char* str, char* substr);

ast_node_t** tree_builder(env_t* env);
/**
 * @brief Builds the AST.
 *
 * @param env Environment of MPSH.
 * @param root Node, root of the AST.
 * @return int 0 if finished, else TOKEN.
 */
int tree_builder_bis(env_t* env, ast_node_t** root);

/**
 * @brief Builds command list (single command + vars).
 *
 * @param env Environment of MPSH.
 * @param list List to add the args to.
 * @param replace_vars 1 If vars wil be replaced else 0.
 * @return int 1 if success else 0;
 */
int n_command(env_t* env, dl_list_str_t* list, int replace_vars);

/**
 * @brief Checks if next char* command token exists.
 *
 * @param text_addr Stores the char*.
 * @return int 1 if success else 0.
 */
int next_is_cmd(char** text_addr);

void print_ast(ast_node_t* ast);

#endif  // MPSH_PARSER_H_
