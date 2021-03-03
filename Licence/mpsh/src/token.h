#ifndef TOKEN_H_
#define TOKEN_H_ 

typedef enum {
    TOK_ENDL = 0,
    TOK_IN = 1,
    TOK_ERR = 2,
    TOK_OUT = 3,
    TOK_OR = 4,
    TOK_AND = 5,
    TOK_PIPE = 6,
    TOK_CMD = 7,
    TOK_QUOTE = 8
} token_t;

#endif //TOKEN_H_