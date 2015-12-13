%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char*);
int yylex(void);
char* res;
/*struct sandwich{
	char* name;
	char** ingredients;
}

struct commandes{
	int number;
	sandwich kebab;
	char* condition;
}*/

%}

INGREDIENT "pain"|"beurre"|"emmental"|"jambon"|"beurre"|"salade"|"tomate"|"steak"|"frites"|"mayonnaise"|"thon"|"ketchup"|"moutarde"

TYPE "fromage"[s]*|"jambon-beurre"[s]*|"panini"[s]*|"belge"[s]*|"dieppois"[s]*

%%
[\n] { 
	printf("\n"); 
	return NEW;
}

[1-9]+ {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}



"fromage"[s]?|"jambon-beurre"[s]?|"panini"[s]?|"belge"[s]?|"dieppois"[s]? {
	yylval.word = yytext;
	printf("sandwich: %s ",yytext);
	return TYPE;
}


"double "?{INGREDIENT} {
	yylval.word = yytext;
	printf("ingredient: %s ",yytext);
	return INGREDIENT;
}

 %{ 
"avec "/"double" {
	yylval.word = yytext;
	printf("operator: %s ",yytext);
}

"mais "("sans"|"avec") {
	yylval.word = yytext;
	printf("operator: %s ",yytext);
	return OPERATION;
}

", "|"sans "|"avec "[double]?|"ni "|"et "/{INGREDIENT} {
	yylval.word = yytext;
	printf("lalala");
	printf("operator: %s ",yytext);
	return OPERATION;
}
"dont "|"et "/([1-9]+) {
	yylval.word = yytext;
	printf("splite: %s ",yytext);
	return SPLITE;
}
%%

int yywarp(void) {
	return 1;
	
}