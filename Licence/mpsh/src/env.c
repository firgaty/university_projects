/**
 * @file env.c
 * @author Félix Desmaretz
 * @brief Source for the MPSH environment.
 * @version 0.1
 * @date 2018-12-26
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "env.h"

/**
 * @brief copies the content of map main to map copy.
 *
 * @param main map_str_t*
 * @param copy map_str_t*
 */
void map_str_copy(map_str_t *main, map_str_t *copy) {
  map_iter_t it = map_iter(main);
  const char *key;
  while ((key = map_next(main, &it))) {
    map_set(copy, key, *map_get(main, key));
  }
}

/**
 * @brief initializes the given environement.
 *
 * @param env Enrironment to initialize.
 */
void env_init(env_t *env) {
  env->aliases = malloc(sizeof(map_str_t));
  env->vars = malloc(sizeof(map_str_t));
  map_init(env->aliases);
  map_init(env->vars);

  env->exports = malloc(sizeof(dl_list_str_t));
  env->exports = gen_dl_list(NULL, NULL);

  env->dir = malloc(sizeof(char) * BUFFER);
  env->home = ".";
  env->umask = DEFAULT_UMASK;

  env->mpsh_stdout = malloc(sizeof(FILE));
  env->mpsh_stderr = malloc(sizeof(FILE));
  env->mpsh_stdin = malloc(sizeof(FILE));
  env->mpsh_stdout = stdout;
  env->mpsh_stderr = stderr;
  env->mpsh_stdin = stdin;
}

/**
 * @brief Copies the environment main to copy.
 *
 * @param main Environment to copy from.
 * @param copy Environment to copy to.
 */
void env_copy(env_t *main, env_t *copy) {
  map_str_copy(main->aliases, copy->aliases);
  map_str_copy(main->vars, main->vars);
  env_dir_set(copy, main->dir);
  copy->umask = main->umask;
}

/**
 * @brief frees all memory allocated to the env.
 *
 * @param env Environment to free.
 */
void env_deinit(env_t *env) {
  map_deinit(env->vars);
  map_deinit(env->aliases);
  dl_list_clean(env->exports);
  free(env->vars);
  free(env->aliases);
  free(env->exports);
}

/**
 * @brief Creates a child environment.
 *
 * @param env Parent.
 * @return env_t* Child.
 */
env_t *env_child(env_t *env) {
  env_t *out = malloc(sizeof(env_t));
  env_init(out);
  out->exports = gen_dl_list(NULL, NULL);
  dl_list_append_copy(env->exports, out->exports);
  // TODO(firgaty) add exported vars (from map to map).
  env_dir_set(out, env->dir);
  out->umask = DEFAULT_UMASK;
  return out;
}

/**
 * @brief sets a var, creates it if nonexistent.
 *
 * @param env Environment to set a var.
 * @param name Var name.
 * @param var Var value.
 * @return int : 0 if success or -1 if failure.
 */
int env_var_set(env_t *env, char *name, char *var) {
  int n = sizeof(char) * (strlen(var) + 1);
  char *str = malloc(n);
  snprintf(str, n, "%s", var);
  return map_set(env->vars, name, str);
}

/**
 * @brief Gets a var from a given env_t.
 *
 * @param env Environment from which to get a var.
 * @param name The nameof the var.
 * @return char* or NULL if nonexistent
 */
char *env_var_get(env_t *env, char *name) {
  char **addr = map_get(env->vars, name);
  if ((addr))
    return *addr;
  return NULL;
}

/**
 * @brief Sets an alias, creates it if nonexistent.
 *
 * @param env Environment to set an alias.
 * @param name Alias name.
 * @param alias Alias value.
 * @return int : 0 if success or -1 if failure.
 */
int env_alias_set(env_t *env, char *name, char *alias) {
  return map_set(env->aliases, name, alias);
}

/**
 * @brief Gets an alias from a given env_t.
 *
 * @param env Environment to get an alias from.
 * @param name Name of the alias.
 * @return char* or NULL if nonexistent.
 */
char *env_alias_get(env_t *env, const char *name) {
  char **addr = map_get(env->aliases, name);
  if ((addr))
    return *addr;
  return NULL;
}

/**
 * @brief Removes an alias.
 *
 * @param env Environment to remove the alias from.
 * @param name Alias name.
 */
void env_alias_remove(env_t *env, char *name) {
  return map_remove(env->aliases, name);
}

/**
 * @brief dir setter.
 *
 * @param env Environment to set the dir.
 * @param path Path of the dir.
 */
void env_dir_set(env_t *env, char *path) {
  if (strlen(path) / BUFFER > 0) {
    env->dir =
        realloc(env->dir, sizeof(char) * (BUFFER + strlen(path) / BUFFER));
  }
  // ça fonctionne ça ?
  *(env->dir) = *path;
}

/**
 * @brief dir getter.
 *
 * @param env Environment to get the dir from.
 * @return char* The dir path.
 */
char *env_dir_get(env_t *env) { return env->dir; }

/**
 * @brief Home getter.
 *
 * @param env Environment to get the home from.
 * @return char* The home path.
 */
char *env_home_get(env_t *env) { return env_var_get(env, "HOME"); }

/**
 * @brief home setter.
 *
 * @param env Environment to set the home.
 * @param path Path of the home.
 */
void env_home_set(env_t *env, char *path) { env_var_set(env, "HOME", path); }

/**
 * @brief umask setter.
 *
 * @param env Environment to set the umask.
 * @param umask New value (in base-8/oct) of the umask.
 */
void env_umask_set(env_t *env, int umask) { env->umask = umask; }

/**
 * @brief umask getter.
 *
 * @param env Environment to get the umask from.
 * @return int The umask value (in base-8/octal numeral system).
 */
int env_umask_get(env_t *env) { return env->umask; }

void env_unset_redir(env_t *env) {
  env->mpsh_stdin = NULL;
  env->mpsh_stdout = NULL;
  env->mpsh_stdout = NULL;
}

void env_set_stdin(env_t *env, FILE *stream) {
	env->mpsh_stdin = stream;
}

void env_set_stdout(env_t *env, FILE *stream) {
	env->mpsh_stdout = stream;
}

void env_set_stderr(env_t *env, FILE *stream) {
	env->mpsh_stderr = stream;
}

// void env_set_redir(env_t *env, char *file_path, int flow) {
//   switch (flow) {
// 	  case STDIN:
// 	    if (env->mpsh_stdin)
// 	      printf("stdin already set.\n");
// 	    env->mpsh_stdin = file_path;
// 	    break;
// 	  case STDOUT:
// 	    if (env->mpsh_stdin)
// 	      printf("stdout already set.\n");
// 	    env->mpsh_stdout = file_path;
// 	    break;
// 	  case STDERR:
// 	    if (env->mpsh_stdin)
// 	      printf("stderr already set.\n");
// 	    env->mpsh_stderr = file_path;
// 	    break;
// 	  default:
// 	    printf("Not a valid flow.\n");
// 	}
// }
