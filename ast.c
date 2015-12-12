#include "init.h"
#include <stdlib.h>

commandes create_commande(int num, char* type) {
	commandes cmd;
	cmd.type = type;
	cmd.head.typenode = 0;
	cmd.head.content.word = NULL;
	cmd.head.left = malloc(sizeof(node));
	if (cmd.head.left = NULL) {
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
	 
	 return cmd;
 }