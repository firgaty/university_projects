%option header-file="scan.h"
%option outfile="scan.c"
%option nounput
%option noinput
%option noyywrap
%{
#include "token.h"
%}

alpha        [a-zA-Z]
line         .*
word         [a-zA-Z0-9_\.\/\-?:~$=]+
var_name     \$[a-zA-Z0-9_?]+
quoted       (\'([^\']|\'\')*\')|(\"([^\"]|\"\")*\") 

%%
[ \t]*
[<]                 {return TOK_IN;}
2[>]                {return TOK_ERR;}
[>]                 {return TOK_OUT;}
\|\|                {return TOK_OR;}
\&\&                {return TOK_AND;}
\|                  {return TOK_PIPE;}
{word}              {return TOK_CMD;}
{quoted}            {return TOK_CMD;}
\'|\"               {return TOK_QUOTE;}
\n|\r               {return TOK_ENDL;}
.                   {}
%%