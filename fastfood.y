%{
	#include <stdio.h>
	#include "init.h"
	int yylex(void);
	void yyerror(char*);
%}

%token TYPE
%token NUMBER
%token INGREDIENT
%token OPERATION
%token SPLITE
%token CONJUNCTION

%left '+' '-'
%left '*' '/'

%%
condition:
	simple SPLITE expr {
	
	}
	| simple OPERATION expr {
	
	}
	| simple expr {
	
	}
;

expr:
	expr SPLITE expr {
	
	}
	| expr CONJUNCTION expr {
	
	}
	| NUMBER OPERATION taste {
	
	}
;

taste:
	INGREDIENT {
	}
	| taste OPERATION taste {
	
	}
;

simple:
	NUMBER TYPE '/n' {
	
	}
;

%%

int main(int argc, char ** argv) {

	return 0;
}

void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}



