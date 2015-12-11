%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char*);
%}

%token TYPE
%token NUMBER
%token INGREDIENT
%token OPERATION

%left '+' '-'
%left '*' '/'

%%
program:
	program expr '/n' { printf("%d/n", $2); }
;

%%



