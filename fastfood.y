%{
	#include <stdio.h>
	#include "init.h"
	
%}

%token TYPE
%token NUMBER
%token INGREDIENT
%token OPERATION
%token SPLITE

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



