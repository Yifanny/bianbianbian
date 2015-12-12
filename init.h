#ifndef _STRUCT_H_
#define _STRUCT_H_
#define MAXSANDW 100
#define MAXTYPE 100

/***********************************************************/
/* type for the node which represent different meaning     */
/* in the syntax tree: 									   */
/* 1: number                                               */
/* 2: ingredient                                           */
/* 3: operation                                            */
/* 4: entity                                               */                    */
/***********************************************************/
int typenode[4] = {1, 2, 3, 4};

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
	char* require;
	int cnt;	
}kind;

typedef struct version {
	char* type;
	kind types[MAXTYPE];
}version;

commandes sandwhich[MAXSANDW];
version order[MAXSANDW];
	
#endif