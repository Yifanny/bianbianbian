#ifndef _STRUCT_H_
#define _STRUCT_H_

union ast{
	int num;
	char* word;
};

typedef struct commandes {
	char* type;
	ast* expr;
	
}commandes;

#endif