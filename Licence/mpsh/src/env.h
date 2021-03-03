/**
 * @file env.h
 * @author Félix Desmaretz
 * @author Louis Gavalda
 * @brief Header for the environment of MPSH.
 * @version 0.1
 * @date 2018-12-26
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "map.h"
#include "dl_list_str.h"
#include "consts.h"


/**
 * @brief Environment containing the variables and
 * aliases used for the parsing and execution of
 * commands and a few other useful things.
 */
typedef struct {
  /*! Map of variables */
  map_str_t *vars;
  /*! Map of aliases */
  map_str_t *aliases;
  /*! List of all the exported vars */
  dl_list_str_t *exports;
  /*! Home directory */
  char *home;
  /*! Current dir */
  char *dir;
  /*! umask of current environment */
  int umask;
  /*! stdout of current environment */
  FILE *mpsh_stdout;
  /*! stderr of current environment */
  FILE *mpsh_stderr;
  /*! stdin of current environment */
  FILE *mpsh_stdin;
  /*! File descriptors for the redirections */
  int fd[3];
  int fd_std[3];
} env_t;

void env_init(env_t *env);
void env_copy(env_t *main, env_t *copy);
void env_deinit(env_t *env);
env_t *env_child(env_t *env);

int env_var_set(env_t *env, char *name, char *var);
char *env_var_get(env_t *env, char *name);
int env_alias_set(env_t *env, char *name, char *alias);
char *env_alias_get(env_t *env, const char *name);
void env_alias_remove(env_t *env, char *name);
void env_dir_set(env_t *env, char *path);
char *env_dir_get(env_t *env);
void env_home_set(env_t *env, char *path);
char *env_home_get(env_t *env);
void env_umask_set(env_t *env, int umask);
int env_umask_get(env_t *env);
void env_export_add(char *var_name);
void env_unset_redir(env_t *env);
void env_set_redir(env_t *env, char *file, int flow);

#endif // ENV_H
