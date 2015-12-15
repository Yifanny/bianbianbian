%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "init.h"
	#include "config.h"
	int yylex(void);
	void yyerror(char*);
	commandes create_commande(int num, char* type);
	node* create_ingredient(char* opr, char* name);
	node* create_ingredients(char* opr, char* name, node* in2);
	node* create_entity(int num, node* in1);
	node* combine_entities(node* ent1, char* spl, node* ent2);
	commandes add_requirement(commandes* cmd, node* req);
	commandes add_condition(commandes* cmd, char* spl, node* cons);
	void nshow(node* point);
	cook* init();
	int check(char* ingredient, char* type);
	int verifie_commandes(node* point, char* type, char* opr, int cnt);
	
	cook* menu;
	int count;
%}
%defines
%union {
	int num;
	char* word;
	struct node* point;
	struct commandes* cmd;
};

%token <word> TYPE
%token <num> NUMBER
%token <word> INGREDIENT
%token <word> OPERATION
%token <word> SPLITE
%token <word> CONJUNCTION
%token <word> NEW

%type <cmd> simple
%type <point> taste
%type <point> expr
%type <cmd> condition
%type <cmd> program

%nonassoc NO_MORE_SPLITE
%nonassoc SPLITE

%%
program: {
		printf("waiting for the new command\n");
	}
	| program condition NEW {		
		printf("%s, nice choice\n", sandwich[count - 1].type);
		nshow(&sandwich[count - 1].head);
		printf("waiting for the new command\n");

	}
;
		
condition:
	simple SPLITE expr {
		printf("require are %s\n", sandwich[count - 1].type);
		sandwich[count - 1] = add_condition($1, $2, $3);
		
		$$ = &sandwich[count - 1];
	}
	| simple taste {
		sandwich[count - 1] = add_requirement($1, $2);
		$$ = &sandwich[count - 1];
	}
	| simple {
		$$ = $1;
		printf("No %d: order finish\n", count);
	}
;

expr:
	NUMBER taste SPLITE expr %prec NO_MORE_SPLITE {
		$$ = combine_entities(create_entity($1, $2), $3, $4);
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
	NUMBER TYPE {
		printf("%s\n", $2);
		if (count) {
			sandwich = realloc(sandwich, (count + 1) * sizeof(commandes));
		}
		else {
			sandwich = malloc(sizeof(commandes));
		}
			
		sandwich[count++] = create_commande($1, $2);
		printf("%s commande taken!\n", sandwich[count - 1].type);
		$$ = &sandwich[count - 1];
		
	}
;

%%


#include "init.h"
#include <stdlib.h>

commandes create_commande(int num, char* type) {
	commandes cmd;
	printf("creating %s \n", type);
	cmd.type = type;
	cmd.head.typenode = 0;
	cmd.head.content.word = NULL;
	cmd.head.left = malloc(sizeof(node));
	if (cmd.head.left == NULL) {
		yyerror("not enough memory!\n");
	}
	cmd.head.left->typenode = 1;
	cmd.head.left->content.num = num;
	cmd.head.left->left = NULL;
	cmd.head.left->right = NULL;
	cmd.head.right = NULL;
	
	return cmd;
}

node* create_ingredient(char* opr, char* name) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 3;
	p->content.word = opr;
	
	p->left = malloc(sizeof(node));
	if (p->left == NULL) {
		yyerror("not enough memory!\n");
	}
	p->left->typenode = 2;
	p->left->content.word = name;
	
	p->right = NULL;
	
	return p;
}


node* create_ingredients(char* opr, char* name, node* in2) {
	node* p = create_ingredient(opr, name);
	p->right = in2;
	
	return p;
}

node* create_entity(int num, node* in1) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 4;
	p->content.word = NULL;
	p->left = malloc(sizeof(node));
	if (p->left == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->left->typenode = 1;
	p->left->content.num = num;
	p->left->left = NULL;
	p->left->right = NULL;
	
	p->right = in1;
	
	return p;
 
}

node* combine_entities(node* ent1, char* spl, node* ent2) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 0;
	p->content.word = spl;
	p->left = ent1;
	p->right = ent2;
	
	return p; 
}

 commandes add_requirement(commandes* cmd, node* req) {
	 cmd->head.right = req;
	 cmd->head.typenode = 4;
	 
	 return *cmd;
	 
 }
 
 commandes add_condition(commandes* cmd, char* spl, node* cons) {
	 cmd->head.content.word = spl;
	 cmd->head.right = cons;
	 
	 return *cmd;
 }

 void nshow(node* point) {
	if (point != NULL) {
		if (point->typenode == 1) {
					printf("number: %d\n", point->content.num);
		}
		else {
			printf("%s\n", point->content.word);
		}
		
		nshow(point->left);
	 	nshow(point->right);
	 }
 }

cook* init() {
	int i;
	cook* cook_list;
	cook_list = malloc(5 * sizeof(cook));
	cook_list[0].name = "fromage";
	for(i = 0; i < sizeof(cook_fromage); i++){
			cook_list[0].material[i] = cook_fromage[i];
	}
	cook_list[1].name = "jambon-beurre";
	for(i = 0; i < sizeof(cook_jambon); i++){
		cook_list[1].material[i] = cook_jambon[i];
	}
	cook_list[2].name = "panini";
	for(i = 0; i < sizeof(cook_panini); i++){
		cook_list[2].material[i] = cook_panini[i];
	}
	cook_list[3].name = "belge";
	for(i = 0; i < sizeof(cook_belge); i++){
		cook_list[3].material[i] = cook_belge[i];
	}
	cook_list[4].name = "dieppois";
	for(i = 0; i < sizeof(cook_dieppois); i++){
		cook_list[4].material[i] = cook_dieppois[i];
	}
	return cook_list;
}

int check(char* ingredient, char* type) {
	int i, j;
	for (i = 0; i < CNTSANDW; i++) {
		if (!strcmp(type, menu[i].name)) {
			for (j = 0; j < material[i]; j++) {
				if (!strcmp(ingredient, menu[i].material[j].name)) {
					return 1;
				}
			}
			return 0;
		}
	}
}

int verifie_commandes(node* point, char* type, char* opr, int cnt) {
	int ret;
	if (point != NULL) {
		switch (point->typenode) {
			case 0:
				if ((ret = verifie_commandes(point->left, type, NULL, cnt)) >= 0) {
					return verifie_commandes(point->right, type, NULL, ret);
				}
				else {
					return -1;
				}
				break;
			case 1:
				if (cnt - point->content->num < 0) {
					return -1;
				}
				else {
					return cnt - point->content->num;
				}
				break;
			case 2:
				switch (opr) {
					case "avec ":
					case "mais avec ":
						if (check(point->content.word, type)) {
							return -1;
						}
						else {
							return cnt;
						}
					case "sans ":
					case "mais sans ":
					case "avec double ":
					case "mais avec double ":
						if (check(point->content.word, type)) {
							return cnt;
						}
						else {
							return -1;
						}
				}
				break;
			case 3:
				switch (point->content.word) {
					case "avec ":
					case "sans ":
					case "avec double ":
					case "mais avec ":
					case "mais avec double ":
					case "mais sans ":
						if ((ret = verifie_commandes(point->left, type, point->content.word, cnt)) >= 0) {
							return verifie_commandes(point->right, type, point->content.word, ret);
						}
						else {
							return -1;
						}
					case "ni ":
				   	case "et ":
					case ", ":
						if ((ret = verifie_commandes(point->left, type, opr, cnt)) >= 0) {
							return verifie_commandes(point->right, type, opr, ret);
						}
						else {
							return -1;
						}
					case "et double ":
					case ", double ":
						if (strstr(opr, avec) != NULL）{
							if ((ret = verifie_commandes(point->left, type, avec_double, cnt)) >= 0) {
								return verifie_commandes(point->right, opr, ret);
							}
							else {
								return -1;
							}
						}
						else {
							return -1;
						}
					case default:
						return -1;
				}
		}
	}
}



void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}

int main() {
	menu = init();
	yyparse();
	return 0;
}