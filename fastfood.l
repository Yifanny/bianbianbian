%{
#include<stdio.h>
#include<string.h>

void yyerror(char*);
int yylex(void);
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

%%
[\n] printf("\n");
[1-9]+ {/*strcpy(yylval,yytext);*/printf("id%s ",yytext);}
"fromage"[s]*|"jambon-beurre"[s]*|"panini"[s]*|"belge"[s]*|"dieppois"[s]* {/*strcpy(yytext,yylval);*/printf("sandwich%s ",yytext);}
"pain"|"beurre"|"emmental"|"jambon"|"beurre"|"salade"|"tomate"|"steak"|"frites"|"mayonnaise"|"thon"|"ketchup"|"moutarde" {/*strcpy(yytext,yylval);*/printf("ingredient%s ",yytext);}
"sans"|"avec"|"ni"|"double"|"dont"|"mais"|"et" {
	//strcpy(yytext,yylval);
	printf("operator%s ",yytext);
}
%%
