%{
#include "stdio.h"
%}

%%
[\n]       ;;
[1-9]+ printf("id%s ",yytext);
[a-z] printf("product%s ",yytext);
%%
