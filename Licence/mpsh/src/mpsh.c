/**
 * @file mpsh.c
 * @author Félix Desmaretz
 * @author Louis Gavalda
 * @brief Main file for MPSH program.
 * @version 0.1
 * @date 2018-11-10
 *
 * @copyright Copyright (c) 2018
 *
 */

#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ast.h"
#include "mpsh.h"

int main(int argc, char const* argv[]) {
  env_t* env;

  using_history();
  read_history(NULL);

  if (!(env = malloc(sizeof(env_t)))) {
    printf(
        "[!] L’environnement n’a pas pu être créé : erreur d’allocation "
        "mémoire.\n");
    return EXIT_FAILURE;
  }
  mpsh_init(env);

  return mpsh_loop(env);
}

void mpsh_init(env_t* env) {
  env_init(env);

  env_var_set(env, "USER", getenv("USER"));
  env_var_set(env, "HOME",
              (getenv("HOME")) ? getenv("HOME") : getpwuid(getuid())->pw_dir);
  env_var_set(env, "CHEMIN", getenv("PATH"));
  env_var_set(env, "?", "0");
  env_var_set(env, "INVITE", "$USER:$DIR:$?> ");
  env->fd_std[0] = dup(0);
  env->fd_std[1] = dup(1);
  env->fd_std[2] = dup(2);
  // close(1);
  // close(2);
  // close(3);
}

void set_dir(env_t* env) {
  // printf("dir set... ");
  long size;
  char* buf;
  char* path;

  size = pathconf(".", _PC_PATH_MAX);

  if ((buf = malloc((size_t)size)) != NULL) {
    path = getcwd(buf, (size_t)size);
    env_var_set(env, "DIR", basename(path));
    // printf("%s", basename(path));
  }
  // printf("\n");
  free(buf);
}

int mpsh_loop(env_t* env) {
  char prompt[BUFFER];
  char* line;
  char status_c[20];
  int status;
  // ast_node_t** tree = malloc(sizeof(ast_node_t));
  ast_node_t **tree = NULL;

  signal(SIGINT, handler);
  signal(SIGSTOP, handler);

  do {
    // dup2(env->fd_std[0], 0);
    // dup2(env->fd_std[1], 1);
    // dup2(env->fd_std[2], 2);

    set_dir(env);
    char *invite = malloc(sizeof(char) * 128);
    invite = replace_vars(env_var_get(env, "INVITE"), env);
    snprintf(prompt, strlen(invite), "%s", invite);
    line = readline(prompt);

    if (!(line))
      break;

    add_history(line);
    write_history(NULL);

    tree = parse_line(line, env);
    status = mpsh_exec(tree, env);
    // printf("status: %d\n", status);

    // Set status
    snprintf(status_c, 4, "%d", status);
    env_var_set(env, "?", status_c);

    // free(invite);
    free(line);

    env->mpsh_stdin = stdin;
    env->mpsh_stderr = stderr;
    env->mpsh_stdout = stdout;

    // close(0);
    // close(1);
    // close(2);

  } while (1);
  return EXIT_SUCCESS;
}

void handler(int sig) {
  if (sig == SIGINT) {
    printf("sigint\n");
  }
  if (sig == SIGSTOP) {
    printf("sigstp\n");
  }
}
