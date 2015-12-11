#ifndef _STRUCT_H_
#define _STRUCT_H_

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
	node_c* left;
	node_c* right;
}node_c;

typedef struct node_v {
	ast_v content;
	node_v* left;
	node_v* right;
}node_v;

typedef struct commandes {
	char* type;
	node_c head;
}commandes;

typedef struct version {
	char* type;
	node_v head;
}version;

#endif