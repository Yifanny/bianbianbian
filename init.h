#ifndef _STRUCT_H_
#define _STRUCT_H_


/***********************************************************/
/* type for the node which represent different meaning     */
/* in the syntax tree: 									   */
/* 0: split                                                */
/* 1: number                                               */
/* 2: ingredient                                           */
/* 3: operation                                            */
/* 4: entity                                               */                    
/***********************************************************/
int typenode[5] = {0, 1, 2, 3, 4};

union ast {
	int num;
	char* word;
};

typedef struct node {
	int typenode;
	union ast content;
	struct node* left;
	struct node* right;
}node;

typedef struct commandes {
	char* type;
	node head;
}commandes;

typedef struct kind {
	char** require;
	int cnt;	
}kind;

typedef struct version {
	char* type;
	kind* types;
}version;

commandes* sandwich;
version* order;
	
#endif