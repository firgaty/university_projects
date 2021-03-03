#include "mpsh_exec.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mpsh_parser.h"

int piped = 0;

bool is_builtin(ast_node_t* ast) {
  if (ast->node_class != CMD)
    return false;
  char** args = dl_list_str_to_string_array(ast->args, 0);
  char* cmd = args[0];
  if (cmd == NULL)
    return false;

  return strcmp(cmd, "exit") == 0 || strcmp(cmd, "echo") == 0 ||
         strcmp(cmd, "type") == 0 || strcmp(cmd, "history") == 0 ||
         strcmp(cmd, "alias") == 0 || strcmp(cmd, "unalias") == 0 ||
         strcmp(cmd, "pwd") == 0 || strcmp(cmd, "cd") == 0 ||
         strcmp(cmd, "umask") == 0 || strcmp(cmd, "export") == 0 ||
         strcmp(cmd, "true") == 0 || strcmp(cmd, "false") == 0;
}

int exec_builtin(char** args, env_t* env) {
  char* cmd = args[0];
  if (cmd == NULL)
    return EXIT_FAILURE;

  // TODO(firgaty) Enlever les commentaire de debug.

  if (strcmp(cmd, "exit") == 0)
    return mpsh_exit(args);
  else if (strcmp(cmd, "echo") == 0)
    return mpsh_echo(args, env);
  else if (strcmp(cmd, "type") == 0)  // test
    return mpsh_type(args, env);
  else if (strcmp(cmd, "history") == 0)
    return mpsh_history(args, env);
  else if (strcmp(cmd, "alias") == 0)
    return mpsh_alias(args, env);
  else if (strcmp(cmd, "unalias") == 0)  // TODO(firgaty) test.
    return mpsh_unalias(args, env);
  else if (strcmp(cmd, "pwd") == 0)
    return mpsh_pwd(args, env);
  else if (strcmp(cmd, "cd") == 0)
    return mpsh_cd(args, env);
  else if (strcmp(cmd, "umask") == 0)
    return mpsh_umask(args, env);
  else if (strcmp(cmd, "export") == 0)
    return mpsh_export(args, env);
  else if (strcmp(cmd, "true") == 0)
    return EXIT_SUCCESS;
  else if (strcmp(cmd, "false") == 0)
    return EXIT_FAILURE;

  return -1;
}

char* exec_concat_path(char* a, char* b) {
  int n = strlen(a) + strlen(b) + 2;
  char* str = malloc(sizeof(char) * n);
  snprintf(str, n, "%s/%s", a, b);
  return str;
}

int exec_prog(char* path, char** args, env_t* env) {
  errno = 0;
  int status = -1;
  status = execv(path, args);
  if (errno == EACCES) {
    fprintf(env->mpsh_stderr, "Program not accessible\n");
    return EXIT_FAILURE;
  } else if (errno == ENOEXEC) {
    fprintf(env->mpsh_stderr, "Program not found\n");
    return EXIT_FAILURE;
  }
  return status < 0 ? status : EXIT_SUCCESS;
}

int exec_from_path(char** args, env_t* env) {
  char* _path = env_var_get(env, "CHEMIN");
  if (!_path) {
    fprintf(env->mpsh_stderr, "No path\n");
    return EXIT_FAILURE;
  }
  // Init copy for strtok.
  char* path = malloc(sizeof(char) * (strlen(_path) + 1));
  strcpy(path, _path);
  char* dir_path = strtok(path, ":");

  if (dir_path == NULL) {
    fprintf(env->mpsh_stderr, "No path\n");
    return EXIT_FAILURE;
  }

  DIR* dir;
  struct dirent* file;
  char* full_path;
  int status;

  do {
    // printf("%s\n", dir_path);
    dir = opendir(dir_path);

    while ((file = readdir(dir)) != NULL) {
      if (strcmp(args[0], file->d_name) == 0) {
        full_path = exec_concat_path(dir_path, file->d_name);
        status = exec_prog(full_path, args, env);
        closedir(dir);  // TODO: check closedir
        return status;
      }
    }

    closedir(dir);  // TODO: check closedir
  } while ((dir_path = strtok(NULL, ":")));

  fprintf(env->mpsh_stderr, "No command found with the name '%s'\n", args[0]);

  return EXIT_FAILURE;
}

int exec_set_var(char** args, env_t* env) {
  if (count_equal(args[0]) == 0)
    return EXIT_FAILURE;
  if (args[0][0] == '$')
    return EXIT_FAILURE;

  char** toks = malloc(sizeof(char*));
  toks = tok_equal(args[0]);

  if (toks[0] == NULL || toks[1] == NULL)
    return EXIT_FAILURE;

  env_var_set(env, toks[0], toks[1]);

  // #########################################
  printf("%s set to %s\n", toks[0], toks[1]);
  // #########################################


  return EXIT_SUCCESS;
}

int exec_cmd(ast_node_t* ast, env_t* env) {
  if (ast->node_class != CMD)
    return EXIT_FAILURE;
  char** args = dl_list_str_to_string_array(ast->args, 0);

  int status;

  if (args[0] == NULL)
    return EXIT_FAILURE;

  status = exec_set_var(args, env);
  if (status == 0)
    return status;
  status = exec_builtin(args, env);
  if (status >= 0)
    return status;
  status = exec_from_path(args, env);
  return status;

  // ast_tree_free(ast);

  exit(-1);
}

int mpsh_exec_bis(ast_node_t* ast, env_t* env) {
  switch (ast->node_class) {
    case (CMD):
      return exec_cmd(ast, env);
      break;
    case (OR):
      exit((!(mpsh_exec_bis(ast->left, env) == EXIT_SUCCESS ||
             mpsh_exec_bis(ast->right, env) == EXIT_SUCCESS)));
      break;
    case (AND):
      exit(!(mpsh_exec_bis(ast->left, env) == EXIT_SUCCESS &&
             mpsh_exec_bis(ast->right, env) == EXIT_SUCCESS));
      break;
    default: {
      return -1;
    }
  }
  return EXIT_SUCCESS;
}

void mpsh_close(int fd) {
  do {
    int close_fd = (fd);
    if (close(close_fd) == -1) {
      perror("close");
      fprintf(stderr, "%s:%d: close(\" fd \") %d\n", __FILE__, __LINE__,
              close_fd);
    }
  } while (0);
}

static void redirect(int oldfd, int newfd) {
  if (oldfd != newfd) {
    if (dup2(oldfd, newfd) != -1)
      mpsh_close(oldfd); /* successfully redirected */
    else
      perror("dup2");
  }
}

static int run(ast_node_t* ast, int in, int out, env_t* env) {
  redirect(in, STDIN_FILENO);   /* <&in  : child reads from in */
  redirect(out, STDOUT_FILENO); /* >&out : child writes to out */

  return mpsh_exec_bis(ast, env);
  perror("mpsh_exec_bis");
  return -1;
}

int mpsh_exec(ast_node_t** ast, env_t* env) {
  int n = (ast) ? 1 : 0;
  ast_node_t** tmp = ast;
  while (*(tmp + 1) != NULL) {
    n++;
    tmp++;
  }

  pid_t pid;
  int status = -1;

  if (n == 0) {
    return 0;
  }

  if (n > 1) {
    if ((pid = fork()) == 0) {
      exec_pipe(ast, env);
    } else {
      waitpid(pid, &status, 0);
      return status;
    }
    return EXIT_FAILURE;
  }

  if (is_builtin(ast[0])) {
    return run(ast[0], 0, 1, env);
  }

  if ((pid = fork()) == 0) {
    run(ast[0], 0, 1, env);
  } else {
    waitpid(pid, &status, 0);
    return status;
  }

  return -1;
}

// TODO: Récupérer les commandes avant de lancer une boucle.
int exec_pipe(ast_node_t** ast, env_t* env) {
  /* run all commands but the last */
  int n = 0;
  ast_node_t** tmp = ast;
  while (*(tmp + 1) != NULL) {
    n++;
    tmp++;
  }

  int i = 0, in = STDIN_FILENO; /* the first command reads from stdin */
  for (; i < n; ++i) {
    int fd[2]; /* in/out pipe ends */
    pid_t pid; /* child's pid */

    if (is_builtin(ast[i])) {
      run(ast[i], in, STDOUT_FILENO, env);
      continue;
    }

    if (pipe(fd) == -1) {
      perror("pipe");
      exit(-1);
    } else if ((pid = fork()) == -1) {
      perror("fork");
      exit(-1);
    } else if (pid == 0) { /* run command[i] in the child process */
      mpsh_close(fd[0]);   /* close unused read end of the pipe */
      return run(ast[i], in, fd[1], env); /* $ command < in > fd[1] */
    } else {                              /* parent */
      assert(pid > 0);
      mpsh_close(fd[1]); /* close unused write end of the pipe */
      mpsh_close(in);    /* close unused read end of the previous pipe */
      in = fd[0];        /* the next command reads from here */
    }
  }
  /* run the last command */
  return run(ast[i], in, STDOUT_FILENO, env); /* $ command < in */
  return EXIT_FAILURE;
}

int count_args(char** args) {
  int i = 0;
  while (*args) {
    args++;
    i++;
  }
  return i;
}

int n_args(char** args, int n) {
  while (*args) {
    args++;
    n--;
  }
  return n == 0;
}

int no_argument(char** args) {
  return !*args;
}

int single_argument(char** args) {
  return n_args(args, 1);
}

int is_file(const char* path) {
  struct stat s;

  return stat(path, &s) == 0;
}

int is_directory(const char* path) {
  struct stat s;

  return stat(path, &s) == 0 && S_ISDIR(s.st_mode);
}

//

int count_equal(char* str) {
  int i = 0;
  while (*str) {
    if (*str == '=')
      i++;
    str++;
  }
  return i;
}

char** tok_equal(char* str) {
  char** array = malloc(sizeof(char*) * 3);
  array[0] = strtok(str, "=");
  array[1] = strtok(NULL, "=");
  array[2] = malloc(sizeof(char));
  array[2] = NULL;
  return array;
}

int mpsh_alias(char** args, env_t* env) {
  int n = count_args(args);
  if (n == 1) {
  	map_iter_t iter = map_iter(env->aliases);
		char *alias_name;
  	while ((alias_name = (char *)map_next(env->aliases, &iter))) {
  		printf("%s=%s\n", alias_name, *map_get(env->aliases, alias_name));
  	}
    return EXIT_SUCCESS;
  } else if (n > 2) {
    fprintf(env->mpsh_stderr, "Too many arguments.\n");
    return EXIT_FAILURE;
  }
  n = count_equal(args[1]);
  if (n == 0 || n > 2) {
    fprintf(env->mpsh_stderr, "Too many arguments.\n");
    return EXIT_FAILURE;
  }
  char** a = tok_equal(args[1]);
  if (a[0] == NULL || a[1] == NULL) {
    fprintf(env->mpsh_stderr, "No alias specified.\n");
    return EXIT_FAILURE;
  }
  env_alias_set(env, a[0], a[1]);
  return EXIT_SUCCESS;
}

//

int print_file(env_t* env, const char* path) {
  FILE* file;
  char* buffer;
  size_t size;

  if (!(file = fopen(path, "r"))) {
    fprintf(env->mpsh_stderr,
            "[!] Impossible d’ouvrir le fichier %s (il existe pourtant)\n",
            path);
    return EXIT_FAILURE;
  }
  if (!(buffer = calloc(sizeof(char), BUFFER + 1))) {
    fprintf(env->mpsh_stderr, "[!] Erreur d’allocation mémoire.");
    return EXIT_FAILURE;
  }
  while ((size = fread(buffer, 1, BUFFER, file))) {
    fwrite(buffer, 1, size, env->mpsh_stdout);
  }
  fwrite("\n", 1, sizeof(char), env->mpsh_stdout);
  return EXIT_SUCCESS;
}

int mpsh_cat(char** args, env_t* env) {
  int status;

  if (no_argument(args)) {
    fprintf(env->mpsh_stderr, "usage: cat FILE\n");
    return EXIT_FAILURE;
  }
  status = EXIT_SUCCESS;
  while (*args) {
    if (!is_file(*args)) {
      fprintf(env->mpsh_stderr,
              "cat: %s: Aucun fichier ou dossier de ce type\n", *args);
      status = EXIT_FAILURE;
    } else if (is_directory(*args)) {
      fprintf(env->mpsh_stderr, "cat: %s: est un dossier\n", *args);
      status = EXIT_FAILURE;
    } else {
      print_file(env, *args);
    }
    args++;
  }
  return status;
}

//

int mpsh_cd(char** args, env_t* env) {
  if (count_args(args) != 2) {
    printf("[!] cd takes 2 arguments\n");
    return EXIT_FAILURE;
  }
  int out = chdir(args[1]);
  if (out != 0) {
    printf("[!] %s is not accessible.\n", args[1]);
  }
  return out;
}

//

int mpsh_echo(char** args, env_t* env) {
  args++;
  while (*args) {
    fprintf(env->mpsh_stdout, "%s ", *args);
    args++;
  }
  printf("\n");
  return EXIT_SUCCESS;
}

//

void mpsh_print_history(env_t* env) {
  HIST_ENTRY** h = history_list();
  int i = 1;
  while (*h) {
    fprintf(env->mpsh_stdout, " %-5d %s\n", i, (*h)->line);
    h++;
    i++;
  }
}

int mpsh_history(char** args, env_t* env) {
  int n = count_args(args);

  if (n == 1) {
    mpsh_print_history(env);
    return EXIT_SUCCESS;
  }
  if (n > 2) {
    fprintf(env->mpsh_stderr, "history: too many arguments, sorry\n");
    return EXIT_FAILURE;
  }
  n = atoi(args[1]);
  if (n < 0) {
    stifle_history(-n);
    unstifle_history();
    return EXIT_SUCCESS;
  } else {
    HIST_ENTRY* h = malloc(sizeof(HIST_ENTRY));
    h = history_get(n);
    if (h == NULL)
      return EXIT_FAILURE;
    return mpsh_exec(parse_line(h->line, env), env);
  }
  return EXIT_SUCCESS;
}

int mpsh_pwd(char** args, env_t* env) {
  char path[BUFFER];
  fprintf(env->mpsh_stdout, "%s\n", getcwd(path, BUFFER));
  return EXIT_SUCCESS;
}

int mpsh_type(char** args, env_t* env) {
  char* alias;
  args++;

  while (*args) {
    alias = env_alias_get(env, *args);
    if (alias) {
      fprintf(env->mpsh_stdout, "%s is an alias for %s\n", *args, alias);
    } else {
      fprintf(env->mpsh_stderr, "%s not found, sorry\n", *args);
      return EXIT_FAILURE;
    }
    args++;
  }
  return EXIT_SUCCESS;
}

int mpsh_umask(char** args, env_t* env) {
  mode_t mask;

  if (!single_argument(args)) {
    fprintf(env->mpsh_stdout, "umask: too many arguments\n");
    return EXIT_FAILURE;
  }
  mask = atoi(*args);
  umask(mask);
  return EXIT_SUCCESS;
}

int mpsh_unalias(char** args, env_t* env) {
  args++;
  while (*args) {
    env_alias_remove(env, *args);
    args++;
  }
  return EXIT_SUCCESS;
}

int mpsh_exit(char** args) {
  int n = count_args(args);
  if (n > 2) {
    printf("Too many arguments");
    return EXIT_FAILURE;
  } else if (n == 1) {
    exit(EXIT_SUCCESS);
  }
  exit(atoi(args[1]));
}

int mpsh_add_var(char* str, env_t* env) {
  int n = count_equal(str);
  if (n == 1) {
    char** a = tok_equal(str);
    if (a[0] == NULL || a[1] == NULL) {
      fprintf(env->mpsh_stderr, "Not a var assignation1.\n");
      return EXIT_FAILURE;
    }
    env_var_set(env, a[0], a[1]);
    return EXIT_SUCCESS;
  }
  fprintf(env->mpsh_stderr, "Not a var assignation2.\n");
  return EXIT_FAILURE;
}

int mpsh_export(char** args, env_t* env) {
  int n = count_args(args);
  if (n == 1) {
    fprintf(env->mpsh_stderr, "No var specified.\n");
    return EXIT_FAILURE;
  } else if (n > 2) {
    fprintf(env->mpsh_stderr, "Too many arguments.\n");
    return EXIT_FAILURE;
  }
  n = count_equal(args[1]);
  char* str = malloc(sizeof(char) * (strlen(args[1]) + 1));
  strcpy(str, args[1]);

  if (n > 0) {
    if (n > 1) {
      fprintf(env->mpsh_stderr, "Not a var assignation3.\n");
      return EXIT_FAILURE;
    }
    if (mpsh_add_var(args[1], env)) {
      return EXIT_FAILURE;
    } else {
      strtok(" ", "=");
      str = strtok(args[1], "=");
    }
  }
  // TODO(firgaty) finish this.
  // setenv returns -1 on failure, but we want to return 1.
  return -1 * setenv(str, env_var_get(env, str), 1);
}
