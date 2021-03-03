#include <malloc.h>
#include <stdio.h>

#include "ast.h"
#include "env.h"
#include "mpsh_parser.h"

// extern int yylex();
// extern int num_chars;
// extern int num_lines;

ast_node_t** parse_line(char* line, env_t* env) {
  // int position = 0;
  // char **tokens = calloc(sizeof(char *), BUFFER_SIZE);
  char buff[BUFFER];

  // ast_node_t* root = malloc(sizeof(ast_node_t));
  // root = gen_default_node();

  snprintf(buff, BUFFER, "%s%s", line, "\0");

  // zz_scan_string(line);
  yy_scan_string(buff);
  replace_vars(buff, env);
  ast_node_t **out = tree_builder(env);
  yylex_destroy();

  // ast_print_tree(root);

  // if(ast_is_valid(root)) printf("AST VALID !\n");
  // else printf("AST INVALID.");

  // return root;
  return out;
}

char* replace_alias(char* str, env_t* env) {
  char* value;
  if ((value = env_alias_get(env, str)))
    return value;
  return str;
}

dl_list_str_t* parse_vars(char* line) {
  dl_list_str_t* list = malloc(sizeof(dl_list_str_t));
  list = gen_dl_list(NULL, NULL);
  char* value;

  zz_scan_string(line);
  while (zzlex()) {
    value = zztext;
    dl_list_add_last(list, value);
  }

  zzlex_destroy();

  return list;
}

char* replace_vars(char* line, env_t* env) {
  dl_list_str_t* list = malloc(sizeof(dl_list_str_t));
  char* str;
  char* value;

  list = parse_vars(line);

  if (dl_list_size(list) > 0) {
    // vars.
    while ((str = dl_list_read_first(list))) {
      if (!(str))
        break;
      if ((value = env_var_get(env, str + 1))) {
        line = replace_str(line, str, value);
      } else {
        printf("Variable %s not defined.\n", str);
      }
      dl_list_pop_first(list, NULL);
    }
  }

  dl_list_clean(list);
  free(list);

  return line;
}

char* replace_str(char* str, char* sub, char* rep) {
  // printf(">>>%s\n", replacement);
  // char buffer[1024] = {0};
  // char* insert_point = &buffer[0];
  // const char* tmp = target;
  // size_t needle_len = strlen(needle);
  // size_t repl_len = strlen(replacement);

  // while (1) {
  //   const char* p = strstr(tmp, needle);

  //   // walked past last occurrence of needle; copy remaining part
  //   if (p == NULL) {
  //     strcpy(insert_point, tmp);
  //     break;
  //   }

  //   // copy part before needle
  //   memcpy(insert_point, tmp, p - tmp);
  //   insert_point += p - tmp;

  //   // copy replacement string
  //   memcpy(insert_point, replacement, repl_len);
  //   insert_point += repl_len;

  //   // adjust pointers, move on
  //   tmp = p + needle_len;
  // }

  // // write altered string back to target
  // strcpy(target, buffer);
  // printf(">>%s\n", target);

  static char buffer[BUFFER_SIZE];
  char* p;

  // Looks if sub is in str and gets the substring.
  if (!(p = mpsh_strstr(str, sub)))
    return str;

  // Copy
  strncpy(buffer, str, p - str);
  buffer[p - str] = '\0';

  // printf(">>%s\n%d\n", buffer, strlen(rep));
  sprintf(buffer + (p - str), "%s%s", rep, p + strlen(sub));
  // sprintf(str, "%s", buffer);
  // printf(">>%s\n>>>%s\n", buffer, str);

  return buffer;
}

char* mpsh_strstr(char* str, char* substr) {
  // Flags for comments.
  int dquote_flag = 0;
  int quote_flag = 0;

  while (*str) {
    char* begin = str;
    char* pattern = substr;

    // Set or unset flags.
    if (dquote_flag && *str == '\"') {
      dquote_flag = 0;
    } else if (quote_flag && *str == '\'') {
      quote_flag = 0;
    } else if (quote_flag || dquote_flag || *str == '\"' || *str == '\'') {
      if ((*str == '\''))
        quote_flag = 1;
      else if ((*str == '\"'))
        dquote_flag = 1;
    } else {
      // If first character of sub string match, check for whole string.
      while (*str && *pattern && *str == *pattern) {
        str++;
        pattern++;
      }
      // If complete sub string match, return starting address.
      if (!*pattern)
        return begin;
    }
    // Increament main string.
    str = begin + 1;
  }
  return NULL;
}

ast_node_t** tree_builder(env_t* env) {
  int count = 0;
  ast_node_t** nodes = malloc(sizeof(ast_node_t*) * 64);
  int rc = 1;
  while (rc) {
    nodes[count] = gen_default_node();
    rc = tree_builder_bis(env, &nodes[count]);
    count++;
    // printf("Help\n");
  }
  // printf("Help2\n");
  nodes[count] = NULL;
  return nodes;
}

int tree_builder_bis(env_t* env, ast_node_t** root) {
  int tok = 0;
  char** addr = malloc(sizeof(char*));
  ast_node_t* left = malloc(sizeof(ast_node_t));
  left = NULL;
  ast_node_t* right = malloc(sizeof(ast_node_t));
  right = gen_default_node();

  tok = yylex();

  if (tok == 0) {
    *root = gen_error_node();
    return 0;
  }

  // TODO(firgaty) remove All debug code.
  while ((tok) && tok != PIPE) {
    switch (tok) {
      case TOK_IN:
        printf("IN\n");
        if (!(next_is_cmd(addr))) {
          printf("Path to STDIN file not found.\n");
          return 0;
        }
        // env_set_redir(env, *addr, STDIN);
        tok = yylex();
        break;
      case TOK_OUT:
        printf("OUT\n");
        if (!(next_is_cmd(addr))) {
          printf("Path to STDOUT file not found.\n");
          return 0;
        }
        // env_set_redir(env, *addr, STDOUT);
        tok = yylex();
        break;
      case TOK_ERR:
        printf("ERR\n");
        if (!(next_is_cmd(addr))) {
          printf("Path to STDERR file not found.\n");
          return 0;
        }
        // env_set_redir(env, *addr, STDERR);
        tok = yylex();
        break;
      case TOK_CMD: {
      }
        dl_list_str_t* list = malloc(sizeof(dl_list_str_t));
        list = gen_dl_list(NULL, NULL);
        tok = n_command(env, list, 1);
        left = gen_command_node(NULL);
        left->args = list;
        // printf("out of CMD\n");
        break;
      case TOK_QUOTE:
        *root = gen_error_node();
        return 0;
        break;
      case TOK_PIPE:
        if (!(left)) {
          printf("Missing arguments before |\n");
          *root = gen_error_node();
          return 0;
        }
        goto end;
        return 0;
        break;
      case TOK_AND:
        if (!(left)) {
          printf("Missing arguments before &&\n");
          *root = gen_error_node();
          return 0;
        }
        tree_builder_bis(env, &right);
        *root = gen_and_node(left, right);
        return 0;
        break;
      case TOK_OR:
        if (!(left)) {
          printf("Missing arguments before ||\n");
          *root = gen_error_node();
          return 0;
        }
        tree_builder_bis(env, &right);
        *root = gen_or_node(left, right);
        return 0;
        break;
      default:
        *root = gen_error_node();
        return 0;
    }
  }

end:

  // printf("out");

  if ((*root)->node_class == DEF) {
    *root = left;
  }

  if ((tok))
    return 1;
  return 0;
}

int n_command(env_t* env, dl_list_str_t* list, int first) {
  dl_list_add_last(
      list, first ? replace_alias(yytext, env) : replace_vars(yytext, env));

  int tok = yylex();

  if (tok == TOK_CMD)
    return n_command(env, list, 0);
  else
    return tok;
}

int n_pipe(env_t* env, ast_node_t** node) {
  return 0;
}

int next_is_cmd(char** text_addr) {
  if (CMD == yylex()) {
    *text_addr = yytext;
    return TRUE;
  } else {
    return FALSE;
  }
}

void print_ast(ast_node_t* ast) {
  printf("%d [", ast->node_class);
  if ((ast->left))
    print_ast(ast->left);
  printf(":");
  if ((ast->right))
    print_ast(ast->right);
}
