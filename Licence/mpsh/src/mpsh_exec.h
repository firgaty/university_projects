#ifndef MPSH_EXEC_H
#define MPSH_EXEC_H

#include <dirent.h>
#include <libgen.h>  // basename
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>  // stat

// #define _GNU_SOURCE
// #include <string.h>

#include "ast.h"
#include "consts.h"
#include "env.h"

/**
 * @brief Checks if a char* array has n items.
 *
 * @param args char* array.
 * @param n Number of items.
 * @return int 1 if true else 0.
 */
int n_args(char** args, int n);
int single_argument(char** args);

int is_file(const char* path);
int is_directory(const char* path);
int print_file(env_t* env, const char* path);
int directory_file(env_t* env, const char* path);

int mpsh_type(char** args, env_t* env);
int mpsh_alias(char** args, env_t* env);
int mpsh_cat(char** args, env_t* env);
int mpsh_cd(char** args, env_t* env);
int mpsh_echo(char** args, env_t* env);
int mpsh_history(char** args, env_t* env);
int mpsh_pwd(char** args, env_t* env);
int mpsh_type(char** args, env_t* env);
int mpsh_umask(char** args, env_t* env);
int mpsh_unalias(char** args, env_t* env);
int mpsh_exit(char** args);
int mpsh_export(char** args, env_t* env);
int mpsh_add_var(char* str, env_t* env);

int exec_set_var(char** args, env_t* env);

int mpsh_exec(ast_node_t** ast, env_t* env);
int exec_pipe(ast_node_t** ast, env_t* env);

int count_equal(char* str);
char** tok_equal(char* str);

#endif  // !MPSH_EXEC_H