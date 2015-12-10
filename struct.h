#ifndef _STRUCT_H_
#define _STRUCT_H_

union ast_c {
	int num;
	char* word;
};

union ast_v {
	int num;
	char** word;
}

typedef struct node {
	ast content;
	node* left;
	node* right;
}node;

typedef struct commandes {
	char* type;
	node head;
}commandes;

#endif