/********************************************************************/
/* Author: Heqing HUANG Yifan ZHANG                                 */
/* Date: 2015-12-01                                                 */
/* Usage:                                                           */
/*	YACC file for the fastfood compiler include 					*/
/*	all the functions of the operation and printing.				*/
/********************************************************************/
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include<unistd.h>
	#include<fcntl.h>
	#include<sys/types.h>
	#include<sys/stat.h>
	#include<errno.h>
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
	float search(char* sandwich, char* ingredient);
	void facture(version* ver, int count);
	void inventaire(version* ver,int num);
	void cuisine(version* ver, int count);
	version* combine_types(version* ver, int* count);
	version* combination (version* vers, int* count);
	
	
	
	cook* menu;
	int count;
	int is_meat;
	int length;
	int ret;
	int i;
	int* p;
	char* tmp;
	version* new_ver;
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
		//printf("henji\n");
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
		
		length = count;
		p = &length;
		facture(order, count);
		inventaire(order, count);
		//printf("aaaaaa%d\n",count);
		new_ver = combination(order, p);
		cuisine(new_ver, length);
		
		
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

// Usage: Creating the init commande
// Enter: Number of sandwich and types
// Return: Command structure
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

// Usage: Creating the node of ingredient
// Enter: Operation name and ingredient name
// Retrun: Node of the Operation with left son of ingredient
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

// Usage: Combine multiply ingredients together
// Enter: Operation name ingredient name and other ingredients head node pointer
// Return: Head node of the Operation with multiple ingredients
node* create_ingredients(char* opr, char* name, node* in2) {
	node* p = create_ingredient(opr, name);
	p->right = in2;
	
	return p;
}

// Usage: Creating a new types of requirement sandwich
// Enter: Number of this type of sandwich and requirement
// Return: Head node of this type of sandwich
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

// Usage: Combine multiple types of sandwichs
// Enter: Two head node pointers of the sandwichs and the conjunction word
// Return: Head node of the conjunction word
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
// Usage: Check whether a ingredient is in the sandwich
// Enter: Name of the ingredient and the type of the sandwich
// Return: 1 means exist, 0 means not exist 
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

// Usage: verifie whether a command is correct
// Enter: Head node of the commande tree, sandwich's name operation and the rest unverifie number 
// Retrun: -1 means error, else return the number of sandwich which is no special require
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
	//printf("number of type: %d\n", res->cnt); 
	if (head->right != NULL) {
		res->require = collect_require(head->right, result, head->right->content.word);
	}
	else {
		res->require = result;
	}
	//printf("ls\n");
	res->num = 2;
	return res;
}

kind* collect_kind(node* point, kind* res) {
	kind* ans;
	//printf("here %d\n", point->typenode);
	if (point->typenode == 4) {
		ans = make_kind(point);
		//printf("inside %d\n", ret);
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
	

void pshow(version* vlist) {
	int i, j, k;
	
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

/* This function is for initialization of a list
 * which include the name of a sandwich and a list of its neccessary ingredients
 * for each type of sandwich, the ingredients for this sandwich 
 * have already declared and stored in the file config.h
 * return the list of recettes of sandwichs 
 */
cook* init(){
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

/* This is an auxilary funtion
 * it has two arguments, one is the name of sandwich 
 * the other is the name of one of its ingredients
 * then return the quantity of this kind of ingredient 
 */
float search(char* sandwich, char* ingredient) {
	float m;
	int i, j, k;
	cook* cook_list;
	cook_list = init();
	for(i = 0; i < 5; i++) {
		if(strcmp(sandwich,cook_list[i].name) == 0) {
			for(j = 0; j < material[i]; j++) {
				if(strcmp(ingredient,cook_list[i].material[j].name) == 0) {
					m = cook_list[i].material[j].num;
					break;
				}
			}
			break;
		}
	}
	return m;
}

/* This is the funtion for printing the facture of commandes
 * it has two arguments, one is a list of versions of sandwichs
 * the other is the number of versions 
 */
void facture(version* ver, int count){
	cook* cook_list;
	cook_list = init();
	float total = 0.0;
	int k = 0;
	int ndh, net, ni, r, n;
	int i, j, sum;
	float cost;
	kind* reqs;
	char sandwich[20];
	
/* This loop is for traversing each sandwich of this list of version*/
	while(k < count){
 		strcpy(sandwich, ver[k].type);
		n = ver[k].num;
		reqs = malloc(n * sizeof(kind));
		for(i = 0, sum = 0; i < n; i++) {
			reqs[i] = ver[k].types[i];
			sum = sum + reqs[i].cnt;
		}
		printf("%2d %-26s", sum, sandwich);
		
/* This loop is for finding the price of this sandwich*/
		for(i = 0; i < 5; i++){
			if(strstr(sandwich,price_list[i].name) != NULL){
				cost = price_list[i].euro;
				break;
			}
		}
		printf("%.2f\n", cost * sum);
		total = total + cost * sum;
		cost = 0.0;
		
/* This loop is in order to traversing all types of this version 
 * the next loop in this loop is for traversing each require in one type 
 */
		for(i = 0; i < n; i++){
			for(j = 0; j < reqs[i].num; j++) {
			if(reqs[i].require[j] != NULL){
				if(strstr(reqs[i].require[j],"avec") != NULL || strstr(reqs[i].require[j],"sans") != NULL) {
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j] + 5);
					}
					else {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j]);
					}
					cost = 0.5 * reqs[i].cnt;
					ndh = net = ni = 0;

/* This loop is for searching ',' or 'et' or 'ni' in the current require */
					for(r = 0; r < strlen(reqs[i].require[j])-2; r++){
						if(reqs[i].require[j][r] == ','){
							ndh = ndh + 1;
						}
						else if(reqs[i].require[j][r] == ' '){
							if(reqs[i].require[j][r+1] == 'e'){
								if(reqs[i].require[j][r+2] == 't')
									net = net + 1;	
							}
						}
						else if(reqs[i].require[j][r] == 'n'){
							if(reqs[i].require[j][r+1] == 'i')
								ni = ni + 1;
						}
					}
					cost = cost + 0.5 * reqs[i].cnt * (ndh + net + ni);
					printf("%.2f\n",cost);
				}
				total = total + cost;
			}
			}
		}
		k++;
	}
	printf("                   Total :   %.2f\n",total);
}


/* This function is for calculation of the inventory of ingredients
 * it has two arguments like the previous function
 * one is a list of versions, the other is the number of the versions in this list
 * it prints a list of neccessary ingredients for this list of versions 
 */
void inventaire(version* ver,int num){			
	cook* cook_list;
	cook_list = init();
	ingredient* cur;
	char* modingred;
	int m, f;
	int n, i, j, k, r, count, sum, z;
	int l;
	int len;
	char* ingred;
	kind* reqs;
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
	

/* This array is definited to store the number of ingredients for each sandwich*/	
	int material[5] = {3, 4, 5, 5, 4};
	char** sandwich;
	sandwich = malloc(5 * sizeof(char*));
	for(i = 0; i < 5; i++){
		sandwich[i] = malloc(20 * sizeof(char));
	}
	sandwich[0] = "fromage";
	sandwich[1] = "jambon-beurre";
	sandwich[2] = "panini";
	sandwich[3] = "belge";
	sandwich[4] = "deippois";
	
	
/* This loop is used for traversing all verions of sandwichs */	
	m = 0;
	while( m < num ) {
	printf("%d 1 panini sans jambon mais avec steak\n",m);
		sum = 0;
		f = 0;
		/* This loop is for calculating the total quantity of this version */
		while(f < ver[m].num){
			sum = sum + ver[m].types[f].cnt;;
			f++;
		}
		
/* This loop is for searching which type this version is 
 * the next three loops are for adding the quantity in the final list of ingredients 
 */
		for (i = 0; i < 5; i++) {
			if(strstr(ver[m].type,cook_list[i].name) != NULL) {
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
	//printf("%d  :  %s\n",m ,ver[m].type);	
/* This part is for check that if there are "sans" or "avec" 
 * and change the quantity in the list of ingredients 
 */
		n = ver[m].num;
		//printf("nnnnnnnnnnn  %d\n",n);
		reqs = malloc(n * sizeof(kind));
		reqs = ver[m].types;
		for(z = 0; z < n; z++) {
			reqs[z].num = 2;
		}
/* This loop is for traversing all types in the current version 
 * the next one is for traversing all requires in each type 
 */
 //printf("%d reqs2\n",reqs[0].num);
 //printf("%d  : types %s\n",n ,ver[m].type);
		for(i = 0; i < n; i++) {
		//printf(" i de zhi %d\n",i);
		//printf("require : %d\n",reqs[i].num);
			for(j = 0; j < reqs[i].num; j++) {
			if(reqs[i].require[j] != NULL){
				if(strstr(reqs[i].require[j],"sans") != NULL || strstr(reqs[i].require[j],"avec") != NULL) {
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						len = (int)sizeof(reqs[i].require[j]) - 10;
						modingred = malloc(len * sizeof(char));
						modingred = reqs[i].require[j] + 10;
					}
					else{
						len = sizeof(reqs[i].require[j]) - 5;
						modingred = malloc(len * sizeof(char));
						modingred = reqs[i].require[j] + 5;	
					}
					//printf("1 panini sans jambon mais avec steak\n");
					
					l = 1;
/* In the next two loops, they are for check the ingredients in require
 * and change its quantity in the list of ingredients 
 */
					for(r = 0; r < strlen(modingred) - 1; ){
						for(k = 0; k < 12; k++) {
							if(modingred[r] == list[k].name[0]) {
								if(modingred[r+1] == list[k].name[1]) {
									ingred = list[k].name;
									l = strlen(list[k].name);
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * search(ver->type,ingred);
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
			//printf("iiiiiiiiii  %d\n",i);
		}
		m++;
	}
	for(i = 0; i < 12; i++) {
		printf("%s,%.2f\n",list[i].name,list[i].num);
	}
}


/* This function is for outputing a file which include HTML for showing the list to the cook 
 * the two arguments are the same as the previous function
 * one is a list of version, the other is number of version 
 */
void cuisine(version* ver, int count) {
	int a, b, c, d, num, m;
	int stream;
	int n = 0;
	int i, j, k;
	int flag[count];
	
	for(i = 0; i < count; i++) {
		flag[i] = 0;
	}
	
/* This part is for combination of the same version in the list of version */	
	/*for(a = 0; a < count; a++) {
		for(b = a + 1; b < count; b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				flag[b] = 1;
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						if(ver[b].types[c].require[d] != NULL){
							int len = strlen(ver[b].types[c].require[d]);
				    		ver[a].types[num+c].require[d] = malloc(len * sizeof(char));
							strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
						}
					}
					//printf("a%d num+c%d require0 : %s\n",a,num+c,ver[a].types[num+c].require[0]);
					//printf("a%d num+c%d require1 : %s\n",a,num+c,ver[a].types[num+c].require[1]);
				}
			}
		}
	}
*/

/* open the file cuisine.html, if there isn't this file, create one */	
	if((stream = open("cuisine.html", O_RDWR|O_TRUNC|O_CREAT, S_IRWXU)) == -1) {
		printf("create fail:%s\n",strerror(errno));
		exit(1);	
	}
/* write the content into this file */
	char buf[256] = "<html><head><title>Cuisine</title><body>";
	if(write(stream, buf, strlen(buf))== -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
/* traverse all the versions after combination 
 * and write them into the file in a certain form of HTML
 */
	while(n < count) {
		if(flag[n] == 0) {
			char buf1[256];
			strcpy(buf1, "<h1>");
			strcat(buf1, ver[n].type);
			strcat(buf1, "</h1><ul>");
			if(write(stream, buf1, strlen(buf1)) == -1) {
				printf("write %s fail:%s\n", ver[n].type, strerror(errno));
				exit(1);
			}
			char buf2[256] = " ";
			for(i = 0; i < ver[n].num; i++){
				strcat(buf2, "<li>");
				char tmp[20];
				sprintf(tmp,"%d", ver[n].types[i].cnt);
				strcat(buf2,tmp);
	
				if(ver[n].types[i].require[0] == NULL && ver[n].types[i].require[1] == NULL){
						strcat(buf2, " normaux");
				}
				else{
					for(j = 0; j < ver[n].types[i].num; j++) {
						//printf("%s  %s\n",ver[n].type,ver[n].types[i].require[j]);
						strcat(buf2," ");
						if(ver[n].types[i].require[j] != NULL){
							strcat(buf2,ver[n].types[i].require[j]);
						}
					}
				}
				strcat(buf2,"</li>");
			}
			strcat(buf2,"</ul>");
			if(write(stream, buf2, strlen(buf2)) == -1) {
				printf("write requires of %s fail:%s\n", ver[n].type, strerror(errno));
				exit(1);
			}
			n++;
		}
		else {
			n++;
		}
	}
	char buf3[256] = "</body></html>";
	if(write(stream, buf3, strlen(buf3)) == -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
}


version* combine_types(version* ver, int* ls) {
	int a, b, c, d, num, m;
	int n = 0;
	int i, j, k;
	int* flag;
	char* tmp;
	version* new_ver;
	
	//printf("bbbbbb\n");
	flag = malloc((*ls) * sizeof(int));
	for(i = 0; i < (*ls); i++) {
		flag[i] = 0;
	}
	
	for(a = 0; a < (*ls); a++) {
		for(b = a + 1; b < (*ls); b++) {
			if(strlen(ver[a].type) < strlen(ver[b].type)) {
				tmp = strstr(ver[b].type,ver[a].type);
			}
			else {
				tmp = strstr(ver[a].type,ver[b].type);
			}
			if(tmp != NULL) {
				flag[b] = 1;
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						int len = strlen(ver[b].types[c].require[d]);
				    	ver[a].types[num+c].require[d] = malloc(len*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	new_ver = malloc(5 * sizeof(version));
	for (i = 0, j = 0; i < (*ls); i++) {
		if(flag[i] == 0) {
			new_ver[j] = ver[i];
			j = j + 1;
		}
	}
	printf("%d jjj\n", j);
	*ls = j;
	return new_ver;
}


version* combination (version* vers, int* num) {
	char* ingredient[12] = {"pain", "jambon","beurre", "salade", "emmental", 
	"ketchup", "moutarde", "mayonnaise", "frites", "tomate", "steak", "thon"};
	int i, j, k, p, q, m, n, flag;
	version* new_ver;
	version* ver = combine_types(vers, num);
	printf("num: %d\n", *num);
	flag = 1;
	for(i = 0; i < (*num); i++) {
		//if(flags[i] == 0){
		//printf("lalala : %d\n",i);
		//printf("%s   %d\n",ver[i].type, ver[i].num);
			for(p = 0; p < ver[i].num - 1; p++) {
				for(q = p + 1; q < ver[i].num; q++) {
					//printf("qqqqqq %d\n",q);
					for(n = 0; n < 2; n++) {
						flag = 1;
						if(ver[i].types[p].require[n] == NULL && ver[i].types[q].require[n] == NULL) {
							flag = 0;
							continue;
						}
						else {
							for(k = 0; k < 12; k++){
							//printf("fff %d : %s %d %s\n",k,ver[i].type,flag,ingredient[k]);
								if(strstr(ver[i].types[p].require[n],ingredient[k]) != NULL) {
									if(strstr(ver[i].types[q].require[n],ingredient[k]) != NULL) {
										flag = 0;
										//printf("asdf  %s\n",ingredient[k]);
									}
									else {
										flag = 1;
										//printf("11111111%s\n",ver[i].type);
										break;
									}
								}
							}
						}
					}
					if(flag == 0) {
						//printf("nnnnnn %s %s\n",ver[i].type,ver[i].types[p].require[0]);
						//printf("nnnnnn %s %s\n",ver[i].type,ver[i].types[p].require[1]);
						
						ver[i].types[p].cnt = ver[i].types[q].cnt + ver[i].types[p].cnt;
						for(j = q + 1; j < ver[i].num; j++) {
							for(m = 0; m < 2; m++) {
								strcpy(ver[i].types[j-1].require[m],ver[i].types[j].require[m]);	
							}
							ver[i].types[j-1].cnt = ver[i].types[j].cnt;
						}
						ver[i].num = ver[i].num - 1;
						q--;
					}
				}
			}
		//}
	}
	new_ver = malloc((*num) * sizeof(version));
	for(i = 0; i < (*num); i++) {
		new_ver[i] = ver[i];
	}
	return new_ver;
}

void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}

int main() {
	menu = init();
	yyparse();
	return 0;
}