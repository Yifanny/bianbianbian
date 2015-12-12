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
		sandwich[count] = add_condition($1, $2, $3);
		$$ = &sandwich[count];
	}
	| simple OPERATION expr {
		sandwich[count] = add_requirement($1, $2, $3);
		$$ = &sandwich[count];
	}
	| simple {
		printf("order finish\n");
	}
;

expr:
	expr SPLITE expr {
		$$ = combine_entities($1, $2, $3);
	}
	| NUMBER taste {
		$$ = create_entity($1, $2);
	}
;

taste:
	OPERATION INGREDIENT {
		$$ = create_ingredient($1, $2);
	}
	| OPERATION INGREDIENT taste {
		$$ = create_ingredients($1, $2, $3);
	}
;

simple:
	NUMBER TYPE '/n' {
		sandwich[count] = create_commande($1, $2);
		$$ = &sandwich[count];
	}
;

%%



void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}



