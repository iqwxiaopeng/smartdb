%{
#include <stdio.h>
#include "y.tab.h"

int
yywrap(void)
{
    return 1;
}
%}
%%
"," { return COMMA; }
"(" { return LEFT_PAREN; }
"-" { return MINUS_SIGN; }
"+" { return PLUS_SIGN; }
")" { return RIGHT_PAREN; }

(?i:by) { return BY; }
(?i:order) { return ORDER; }
(?i:select) { return SELECT; }

[_a-zA-Z]\w* {
  yylval.string_v = yytext;
  return COLUMN_NAME;
}
%%
