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
	int verifie_commandes(node* point, char* type, char* opr, int cnt, int is_meat);
	char** collect_require(node* point, char** res, char* opr);
	kind make_kind(node* head);
	kind* collect_kind(node* point, kind* res);
	version transform(node* head, char* type);
	ingredient* ingredient_list(version* ver,int num);
	version* combien_version(version* ver, int count);
	void pshow(version* v);
	
	cook* menu;
	int count;
	int ret;
	int i;
	char* tmp;
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
		printf("henji\n");
		if (!strcmp(fromage, sandwich[count - 1].type)) {
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num, 0);
		}
		else {
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num, 1);
		}
		printf("lalal: %d\n", ret);
		if (ret < 0) {
			yyerror("error input\n");
		}
		
		order = malloc(count * sizeof(version));
		
		
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
		else if (point->content.word != NULL) {
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

/* Return: 1 means exist, 0 means not exist */
int check(char* ingredient, char* type) {
	int i, j;
	for (i = 0; i < CNTSANDW; i++) {
		if (!strcmp(type, menu[i].name)) {
			for (j = 0; j < material[i]; j++) {
				if (!strcmp(ingredient, menu[i].material[j].name)) {
					return 1;
				}
			}
		}
	}
	return 0;
}


int verifie_commandes(node* point, char* type, char* opr, int cnt, int is_meat) {
	int ret;
	if (point != NULL) {
		switch (point->typenode) {
			case 4:
			case 0:
				if ((ret = verifie_commandes(point->left, type, NULL, cnt, is_meat)) >= 0) {
					return verifie_commandes(point->right, type, NULL, ret, is_meat);
				}
				else {
					return -1;
				}
				break;
			case 1:
				printf("aaaa\n");
				printf("cnt: %d, current: %d\n", cnt, point->content.num);
				if (cnt - point->content.num < 0) {
					return -1;
				}
				else {
					return cnt - point->content.num;
				}
				break;
			case 2:
				ret = check(point->content.word, type);
				tmp = point->content.word;
				if (!strcmp(opr, avec) || !strcmp(opr, mais_avec)) {
					printf("entering\n");
					printf("now: %d\n", ret);
					if (ret) {
						return -1;
					}
					else if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
						if (is_meat) {
							return -1;
						}
						else {
							is_meat = 1;
							return cnt;
						}
					}
				}
				else if (!strcmp(opr, sans) || !strcmp(opr, mais_sans)) {
					if (ret) {
						if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
							is_meat = 0;
							return cnt;
						}
						else {
							return cnt;
						}
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(opr, avec_double) || !strcmp(opr, mais_avec_double)) {
					if (ret) {
						if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
							return -1;
						}
						else {
							return cnt;
						}
					}
				}
				else {
					return -1;
				}
			case 3:
				if (!strcmp(point->content.word, sans) || !strcmp(point->content.word, mais_sans) || !strcmp(point->content.word, avec_double) || 
					!strcmp(point->content.word, mais_avec_double) || !strcmp(point->content.word, avec) || !strcmp(point->content.word, mais_avec)) {
					if ((ret = verifie_commandes(point->left, type, point->content.word, cnt, is_meat)) >= 0) {
						return verifie_commandes(point->right, type, point->content.word, ret, is_meat);
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(point->content.word, ni) || !strcmp(point->content.word, et) || !strcmp(point->content.word, comma)) {
					if ((ret = verifie_commandes(point->left, type, opr, cnt, is_meat)) >= 0) {
						return verifie_commandes(point->right, type, opr, ret, is_meat);
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(point->content.word, et_double) || !strcmp(point->content.word, comma_double)) {
					if (strstr(opr, avec) != NULL) {
						if ((ret = verifie_commandes(point->left, type, avec_double, cnt, is_meat)) >= 0) {
							return verifie_commandes(point->right, type, opr, ret, is_meat);
						}
						else {
							return -1;
						}
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
		}
	}
	return cnt;
}

char** collect_require(node* point, char** res, char* opr) {
	if (point != NULL) {
		tmp = point->content.word;
		if (!strstr(tmp, avec)) {	
			res[0] = strcat(res[0], tmp);
			res[0] = strcat(res[0], point->left->content.word);
			ret++;
			opr = avec;
		}
		else if (!strstr(tmp, sans)) {
			res[1] = strcat(res[1], tmp);
			res[1] = strcat(res[1], point->left->content.word);
			ret++;
			opr = sans;
		}
		else {
			res[!strcmp(opr, avec)?0:1] = strcat(res[!strcmp(opr, avec)?0:1], tmp);
			res[!strcmp(opr, avec)?0:1] = strcat(res[!strcmp(opr, avec)?0:1], point->left->content.word);
		}
		return collect_require(point->right, res, opr);
	}
	return res;
	
} 

kind make_kind(node* head) {
	kind res;
	char** result = NULL;
	ret = 0;
	res.cnt = head->left->content.num;
	res.require = collect_require(head->right, result, head->right->content.word);
	res.num = ret;
	return res;
}

kind* collect_kind(node* point, kind* res) {
	kind ans;
	if (point->typenode == 4) {
		ans = make_kind(point);
		res = realloc(res, (ret + 1) * sizeof(kind));
		res[ret] = ans;
		ret++;
		return res;
	}
	else if (point->typenode == 0) {
		ans = *collect_kind(point->left, res);
		return collect_kind(point->right, &ans);
	}
	return res;
}

version transform(node* head, char* type) {
	version res;
	ret = 0;
	res.types = NULL;
	res.type = type;
	res.types = collect_kind(head, res.types);
	res.num = ret;
	return res;
}
	
/*
ingredient* ingredient_list(version* ver,int num) {
	cook* cook_list;
	cook_list = init();
	ingredient list[12] = {
		{0.0,"pain"},
		{0.0,"jambon"},
		{0.0,"beurre"},
		{0.0,"salade"},
		{0.0,"emmental"},
		{0.0,"ketchup"},
		{0.0,"moutarde"},
		{0.0,"mayonnaise"},
		{0.0,"frites"},
		{0.0,"tomate"},
		{0.0,"steak"},
		{0.0,"thon"}
	};
	
	ingredient add[12] = {
		{1.0,"pain"},
		{1.0,"jambon"},
		{10.0,"beurre"},
		{10.0,"salade"},
		{2.0,"emmental"},
		{10.0,"ketchup"},
		{10.0,"moutarde"},
		{20.0,"mayonnaise"},
		{50.0,"frites"},
		{0.5,"tomate"},
		{1.0,"steak"},
		{50.0,"thon"}
	};
	
	int n, i, j, k, r, count, sum;
	
	int material[5] = {3, 4, 5, 5, 4};
	char** sandwich;
	ingredient* cur;
	char* modingred;
	int m, f;
	
	sandwich = malloc(5 * sizeof(char*));
	for(i = 0; i < 5; i++){
		sandwich[i] = malloc(20 * sizeof(char));
	}
	sandwich[0] = "fromage";
	sandwich[1] = "jambon-beurre";
	sandwich[2] = "panini";
	sandwich[3] = "belge";
	sandwich[4] = "deippois";
	

	m = 0;
	while( m < num ) {
		sum = 0;
		f = 0;
		while(f < ver->num){
			//printf(" sum %d\n",sum);
			sum = sum + ver->types[f].cnt;;
			f++;
		}
		for (i = 0; i < 5; i++) {
			if(strcmp(ver->type,cook_list[i].name) == 0) {
				count = material[i];
				cur = malloc(count * sizeof(ingredient));
				for(r = 0; r < count; r++){
					cur[r] = cook_list[i].material[r];
				}
				for(j = 0; j < material[i]; j++){
					for(k = 0; k < 12; k++) {
						if(strcmp(list[k].name,cook_list[i].material[j].name) == 0){
							list[k].num = list[k].num + sum * cook_list[i].material[j].num;
						}
					}	
				}
				break;
			}
		}
		kind* reqs;
		n = ver->num;
		reqs = malloc(n * sizeof(kind));
		reqs = ver->types;
		for(i = 0; i < n; i++) {
			for(j = 0; j < reqs[i].num; j++) {
				if(strstr(reqs[i].require[j],"sans") != NULL || strstr(reqs[i].require[j],"avec") != NULL) {
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						n = (int)sizeof(reqs[i].require[j]) - 10;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 10;
					}
					else{
						n = sizeof(reqs[i].require[j]) - 5;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 5;	
					}
					int l;
					char* ingred;
					l = 1;
					for(r = 0; r < strlen(modingred) - 1; ){
						for(k = 0; k < 12; k++) {
							if(modingred[r] == list[k].name[0]) {
								if(modingred[r+1] == list[k].name[1]) {
									ingred = list[k].name;
									l = strlen(list[k].name);
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * find(ver->type,ingred);
									}
									else{
										list[k].num = list[k].num + reqs[i].cnt * add[k].num;
									}
									break;
								}
							}
							else{
								l = 1;
							}
						}
						r = r + l; 
					}
				}
			}
		}
		m++;
		ver++;
	}
	return list;
}
*/

version* combien_version(version* ver, int count) {
	int a, b, c, d, num, m;
	for(a = 0; a < count; a++) {
		for(b = a + 1; b < count; b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					//ver[a].types[num+c] = malloc(sizeof(kind));
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						int len = strlen(ver[b].types[c].require[d]);
				    	ver[a].types[num+c].require[d] = malloc(d*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	return ver;
}

void pshow(version* vlist）{
	int i, j, k;
	for (i = 0; i < count; i++) {
		prinf("%type is : %s\n", vlist[i].type);
		for (j = 0; j < vlist[i].num; j++ ) {
			printf("     %d: ", vlist[i].types[j].cnt);
			for (k = 0; k < vlist[i].types[j].num; k++) {
				printf(" %s ", vlist[i].types[j].require[k]);
			}
			printf("\n");
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