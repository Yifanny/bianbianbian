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
TYPE "panini"|"fromage"|"belge"

%%
[\n] { 
	printf("\n"); 
	return NEW;
}

[1]/" panini" {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

[1]/" fromage" {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

[1]/" belge" {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

0?1[0-9]+/" "{TYPE}s {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

0?[2-9][1-9]?/" "{TYPE}s {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

[0-9]+/" dieppois" {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

[0-9]+/" jambon-beurre" {
	yylval.num = atoi(yytext);
	printf("id: %s ",yytext);
	return NUMBER;
}

"fromage"[s]?|"jambon-beurre"[s]?|"panini"[s]?|"belge"[s]?|"dieppois"[s]? {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("sandwich: %s \n",yytext);
	return TYPE;
}


{INGREDIENT} {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("ingredient: %s ",yytext);
	return INGREDIENT;
}

"mais "("sans "|"avec "("double ")?) {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("operator: %s ",yytext);
	return OPERATION;
}

", "("double ")?|"sans "|"avec "("double ")?|"ni "|"et "("double ")?/{INGREDIENT} {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("operator: %s ",yytext);
	return OPERATION;
}

"sans "/{INGREDIENT}(", "{INGREDIENT})*(" ni "{INGREDIENT})?" mais avec " {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("operator: %s ",yytext);
	return OPERATION;
}

"avec "/{INGREDIENT}(", "{INGREDIENT})*(" et "{INGREDIENT})?" mais sans " {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("operator: %s ",yytext);
	return OPERATION;
}

"dont "|"et "/([1-9]+) {
	yylval.word = malloc((yyleng + 1) * sizeof(char));
	yylval.word = strncpy(yylval.word, yytext, yyleng);
	yylval.word[yyleng] = '\0';
	printf("splite: %s ",yytext);
	return SPLITE;
}
%%

int yywarp(void) {
	return 1;
	
}