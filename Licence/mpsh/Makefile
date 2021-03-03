NAME ?= mpsh

CC ?= gcc
CFLAGS ?= -Wall -g 
# CFLAGS ?= -Wall -Werror -Wextra
LDLIBS ?= -lreadline

SRC_DIR ?= ./src
FLEX_DIR ?= ./src/flex
BUILD_DIR ?= ./build
SRC := $(wildcard $(SRC_DIR)/*.c)
FLEX_SRC := $(wildcard $(FLEX_DIR)/*.c)
#FLEX_LEX := $(wildcard $(FLEX_DIR)/*.flex)

.PHONY: lex.yy.c all clean  re

build: $(NAME)

#flex: $(FLEX_LEX)
#	flex $(FLEX_LEX)

# $(NAME): $(FLEX_SRC)
# 	@$(CC) $(CFLAGS) $(LDLIBS) $(FLEX_SRC) -o $(NAME) -lfl

$(NAME): $(SRC) $(FLEX_SRC)
	@$(CC) $(CFLAGS) $(LDLIBS) $(SRC) $(FLEX_SRC) -o $(NAME) -lfl

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all