%{
	#include <stdio.h>
	#include "struct.h"
	#define MAXSANDWA 100
	int yylex(void);
	void yyerror(char*);
	commandes sandwhich[MAXSANDW];
	version order;
%}

%token TYPE
%token NUMBER
%token INGREDIENT
%token OPERATION

%left '+' '-'
%left '*' '/'

%%
program:
	program expr '/n' { 
		printf("%d/n", $2); 
	}
;

expr:
	| NUMBER TYPE '/n' {
	
	}
	| NUMBER TYPE expr 
%%



