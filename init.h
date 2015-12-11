#ifndef _STRUCT_H_
#define _STRUCT_H_
#define MAXSANDW 100

union ast_c {
	int num;
	char* word;
};

union ast_v {
	int num;
	char** word;
};

typedef struct node_c {
	union ast_c content;
	struct node_c* left;
	struct node_c* right;
}node_c;

typedef struct node_v {
	union ast_v content;
	struct node_v* left;
	struct node_v* right;
}node_v;

typedef struct commandes {
	char* type;
	node_c head;
}commandes;

typedef struct version {
	char* type;
	node_v head;
}version;




commandes sandwhich[MAXSANDW];
version order[MAXSANDW];
	
#endif