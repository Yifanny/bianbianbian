%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "init.h"
	int yylex(void);
	void yyerror(char*);
	int count;
%}

%union {
	int num;
	char* word;
};

%token <word> TYPE
%token <num> NUMBER
%token <word> INGREDIENT
%token <word> OPERATION
%token <word> SPLITE
%token <word> CONJUNCTION

%left '+' '-'
%left '*' '/'

%%
program:
	program condition '\n' {
		printf("%s\n", $2);
		count++;
	}
;
		
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
		$$ = create_ingredient($1);
	}
	| taste OPERATION taste {
		$$ = create_ingredients($1, $2, $3);
	}
;

simple:
	NUMBER TYPE '/n' {
		sandwich[count] = create_commande($1, $2);
	}
;

%%



void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}



