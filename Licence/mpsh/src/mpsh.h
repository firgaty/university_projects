/**
 * @file mpsh.h
 * @author Félix Desmaretz
 * @author Louis Gavalda
 * @brief Main file header for MPSH program.
 * @version 0.1
 * @date 2018-11-10
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef MPSH_H
#define MPSH_H

#include <stdio.h>              // readline
#include <stdlib.h>
#include <readline/readline.h>  // readline ;
#include <readline/history.h>   // HISTORY/ ;
#include <unistd.h>             // getwcd ;
#include <sys/stat.h>			// stat
#include <sys/types.h>
#include <pwd.h>                // HOME
#include <signal.h>

#include "mpsh_exec.h"
#include "mpsh_parser.h"
#include "dl_list_str.h"
#include "env.h"
#include "consts.h"

/**
 * @brief Main function.
 *
 * @param argc Number of arguments + 1.
 * @param argv Arguments.
 * @return int 0 if success.
 */
int main(int argc, char const *argv[]);

/**
 * @brief Init function
 *
 * All the variables are initialized.
 *
 * @param env Environment to initialize.
 */
void mpsh_init(env_t *env);

/**
 * @brief Loop for the command line.
 *
 * @param env Shell environment.
 * @return int 0 if success.
 */
int mpsh_loop(env_t *env);

void handler(int sig);

#endif  // MPSH_H
