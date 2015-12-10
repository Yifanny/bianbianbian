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

typedef struct node_c {
	ast_c content;
	node* left;
	node* right;
}node_c;

typedef struct node_v {
	ast_v content;
	node* left;
	node* right;
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