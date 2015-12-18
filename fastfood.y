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
	char** collect_require(node* point, char** res, char* opr);
	kind* make_kind(node* head);
	kind* collect_kind(node* point, kind* res);
	version transform(node* head, char* type);
	ingredient* ingredient_list(version* ver,int num);
	version* combien_version(version* ver, int count);
	void pshow(version* v);
	
	cook* menu;
	int count;
	int is_meat;
	int length;
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
		//nshow(&sandwich[count - 1].head);
		printf("henji\n");
		if (!strcmp(fromage, sandwich[count - 1].type)) {
			is_meat = 0;
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num);
		}
		else {
			is_meat = 1;
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num);
		}
		printf("lalal: %d\n", ret);
		if (ret < 0 || is_meat > 1) {
			yyerror("error input\n");
			return 1;
		}
		
		order = malloc(count * sizeof(version));
		printf("start transform\n");
		length = ret;
		for (i = 0; i < count; i++) {
			order[i] = transform(&sandwich[i].head, sandwich[i].type);
		}
		if (length > 0 && length != sandwich[count - 1].head.left->content.num) {
			order[count - 1].num++;
			order[count - 1].types = realloc(order[count - 1].types, order[count - 1].num * sizeof(kind));
			order[count - 1].types[order[count - 1].num - 1].require = malloc(2 * sizeof(char*));
			order[count - 1].types[order[count - 1].num - 1].require[0] = NULL;
			order[count - 1].types[order[count - 1].num - 1].require[1] = NULL;
			order[count - 1].types[order[count - 1].num - 1].num = 2;
			order[count - 1].types[order[count - 1].num - 1].cnt = length;
		} 
		printf("finish transform\n");
		pshow(order);
		
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
	cmd.head.typenode = 4;
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
	 
	 return *cmd;
	 
 }
 
 commandes add_condition(commandes* cmd, char* spl, node* cons) {
	 cmd->head.content.word = spl;
	 cmd->head.right = cons;
	 cmd->head.typenode = 0;
	 
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
		if (strstr(type, menu[i].name) != NULL) {
			for (j = 0; j < material[i]; j++) {
				if (!strcmp(ingredient, menu[i].material[j].name)) {
					return 1;
				}
			}
		}
	}
	return 0;
}


int verifie_commandes(node* point, char* type, char* opr, int cnt) {
	int ret;
	if (point != NULL) {
		switch (point->typenode) {
			case 4:
			case 0:
				if ((ret = verifie_commandes(point->left, type, NULL, cnt)) >= 0) {
					return verifie_commandes(point->right, type, NULL, ret);
				}
				else {
					return -1;
				}
				break;
			case 1:
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
				printf("%s %s %d henji\n", tmp, opr, ret);
				if (!strcmp(opr, avec) || !strcmp(opr, mais_avec)) {
					printf("now: %d\n", ret);
					if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
						is_meat++;
					}
					if (ret) {
						return -1;
					}
					else {
						return cnt;
					}
				}
				else if (!strcmp(opr, sans) || !strcmp(opr, mais_sans)) {
					if (ret) {
						if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
							is_meat--;
						}
						return cnt;
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
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
			case 3:
				if (!strcmp(point->content.word, sans) || !strcmp(point->content.word, mais_sans) || !strcmp(point->content.word, avec_double) || 
					!strcmp(point->content.word, mais_avec_double) || !strcmp(point->content.word, avec) || !strcmp(point->content.word, mais_avec)) {
					if ((ret = verifie_commandes(point->left, type, point->content.word, cnt)) >= 0) {
						return verifie_commandes(point->right, type, point->content.word, ret);
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(point->content.word, ni) || !strcmp(point->content.word, et) || !strcmp(point->content.word, comma)) {
					if (strstr(opr, twice) != NULL) {
						if (strstr(opr, avec) != NULL) {
							if ((ret = verifie_commandes(point->left, type, avec, cnt)) >= 0) {
								return verifie_commandes(point->right, type, avec, ret);
							}
							else {
								return -1;
							}
						}
						else if (strstr(opr, sans) != NULL) {
							if ((ret = verifie_commandes(point->left, type, sans, cnt)) >= 0) {
								return verifie_commandes(point->right, type, sans, ret);
							}
							else {
								return -1;
							}
						}
					}
					else {
						if ((ret = verifie_commandes(point->left, type, opr, cnt)) >= 0) {
								return verifie_commandes(point->right, type, opr, ret);
							}
						else {
							return -1;
						}
					}
				}
				else if (!strcmp(point->content.word, et_double) || !strcmp(point->content.word, comma_double)) {
					if (strstr(opr, avec) != NULL) {
						if ((ret = verifie_commandes(point->left, type, avec_double, cnt)) >= 0) {
							return verifie_commandes(point->right, type, opr, ret);
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
	int i, j;
	printf("%s  \n", opr);
	if (point != NULL) {
		printf("hereh\n");
		tmp = point->content.word;
		printf("%d %s as\n", point->typenode, tmp);
		if (strstr(tmp, avec) != NULL) {	
			printf("lalalalalalalala\n");
			if (res[0] == NULL) {
			printf(" current condition is : %s \n", res[0]);
				i = strlen(tmp) + strlen(point->left->content.word) + 2;
				res[0] = malloc(i * sizeof(char));
				res[0] = memset(res[0], '\0', i);
				printf(" current condition is : %s \n", res[0]);
				printf(" current add is : %s \n", tmp);
				printf(" current condition is : %s \n", res[0]);
				res[0] = strcat(res[0], tmp);
				printf(" current condition is : %s \n", res[0]);
				res[0] = strcat(res[0], point->left->content.word);
				printf(" current condition is : %s \n", res[0]);
				i = strlen(res[0]);
				res[0][i] = ' ';
				res[0][i + 1] = '\0';
			}
			else {
				res[0] = realloc(res[0], (strlen(res[0]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
				res[0] = strcat(res[0], tmp);
				res[0] = strcat(res[0], point->left->content.word);
				i = strlen(res[0]);
				res[0][i] = ' ';
				res[0][i + 1] = '\0';
			}
			opr = avec;
			
		}
		else if (strstr(tmp, sans) != NULL) {
			printf("herer?\n");
			if (res[1] == NULL) {
				i = strlen(tmp) + strlen(point->left->content.word) + 2;
				res[1] = malloc(i * sizeof(char));
				res[1] = memset(res[1], '\0', i);
				res[1] = strcat(res[1], tmp);
				printf("muamua\n");
				res[1] = strcat(res[1], point->left->content.word);
				i = strlen(res[1]);
				res[1][i] = ' ';
				res[1][i + 1] = '\0';
			}
			else {
				res[1] = realloc(res[1], (strlen(res[1]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
				res[1] = strcat(res[1], tmp);
				res[1] = strcat(res[1], point->left->content.word);
				i = strlen(res[1]);
				res[1][i] = ' ';
				res[1][i + 1] = '\0';
			}
			opr = sans;
		}
		else {
			i = strstr(opr, avec) != NULL?0:1;
			res[i] = realloc(res[i], (strlen(res[i]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
			printf(" current condition is : %s \n", res[i]);
			res[i] = strcat(res[i], tmp);	
			printf(" current condition is : %s \n", res[i]);	
			res[i] = strcat(res[i], point->left->content.word);
			j = strlen(res[i]);
			res[i][j] = ' ';
			res[i][j + 1] = '\0';
			
			
		}
		return collect_require(point->right, res, opr);
	}
	return res;
	
} 

kind* make_kind(node* head) {
	kind* res;
	char** result = malloc(2 * sizeof(char*));
	result[0] = NULL;
	result[1] = NULL;
	res = malloc(sizeof(kind));
	res->cnt = head->left->content.num;
	printf("number of type: %d\n", res->cnt); 
	if (head->right != NULL) {
		res->require = collect_require(head->right, result, head->right->content.word);
	}
	else {
		res->require = result;
	}
	printf("ls\n");
	res->num = 2;
	return res;
}

kind* collect_kind(node* point, kind* res) {
	kind* ans;
	printf("here %d\n", point->typenode);
	if (point->typenode == 4) {
		ans = make_kind(point);
		printf("inside %d\n", ret);
		res = realloc(res, (ret + 1) * sizeof(kind));
		res[ret] = *ans;
		ret++;
		return res;
	}
	else if (point->typenode == 0) {
		ans = collect_kind(point->left, res);
		return collect_kind(point->right, ans);
	}
	return res;
}

version transform(node* head, char* type) {
	version res;
	ret = 0;
	res.types = NULL;
	res.type = type;
	res.types = collect_kind(head, res.types);
	printf("finish collect\n");
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

void pshow(version* vlist) {
	int i, j, k;
	printf("%d: aaaaaaaa\n",vlist[0].types[0].cnt);
	
	//printf("%d: %s lalalala\n", vlist[0].types[0].cnt, vlist[0].types[0].require[0]);
	for (i = 0; i < count; i++) {
		printf("type is : %s\n", vlist[i].type);
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