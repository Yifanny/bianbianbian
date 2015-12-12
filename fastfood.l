%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
[\n] printf("\n");
[1-9]+ {
	//strcpy(yylval,yytext);
	printf("id%s ",yytext);
	//return NUMBER;
}



"fromage"[s]*|"jambon-beurre"[s]*|"panini"[s]*|"belge"[s]*|"dieppois"[s]* {
	//strcpy(yytext,yylval);
	printf("sandwich%s ",yytext);
	//return TYPE;
}


"double "?{INGREDIENT} {
	//strcpy(yytext,yylval);
	printf("ingredient%s ",yytext);
	//return INGREDIENT;
}

"avec "/"double" {
	//strcpy(yytext,yylval);
	printf("operator%s ",yytext);
}

"mais "("sans"|"avec") {
	//strcpy(yytext,yylval);
	printf("operator%s ",yytext);
	//return OPERATION;
}

", "|"sans "|"avec "|"ni "|"et "/{INGREDIENT} {
	//strcpy(yytext,yylval);
	//printf("lalala");
	printf("operator%s ",yytext);
	//return OPERATION;
}
"dont "|"et "/([1-9]+) {
	//strcpy(yytext,yylval);
	printf("splite%s ",yytext);
	//return SPLITE;
}
%%
