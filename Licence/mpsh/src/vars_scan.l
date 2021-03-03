%option header-file="vars_scan.h"
%option outfile="vars_scan.c"
%option prefix="zz"
%option noyywrap
%option nounput
%option noinput

blank        "\n" | "\r" | " " | "\t"
alpha        [a-zA-Z]
line         .*
word         [{alpha}|{number}|_|.|/|\-|"?"]+
var_name     [{alpha}|{number}|_]+
var          \${var_name}
quoted       (\'([^\']|\'\')*\')|(\"([^\"]|\"\")*\") 
%%
\$[a-zA-Z0-9_?]+                {return 1;}
{quoted}                        {}
\n|\r                           {return 0;}
.                               {}
%%