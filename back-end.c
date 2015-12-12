/*************************************************************************
    > File Name: back-end.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年12月10日 星期四 19时33分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "init.h"

extern count;

struct price {
	char* name;
	float euro;
};

typedef struct price price;

price price_list[5] = {
	{"fromage",3.0},
	{"jambon-beurre",4.0},
	{"panini",5.0},
	{"belge",5.0},
	{"dieppois",4.5}
};

char* operators = "sans,avec";

float InOrder(node_c* tree) {
	int num;
	float sum;
	if(tree) {
		sum = sum + InOrder(tree->left);
		if(sizeof(tree->content) == sizeof(int)) {
			printf("\n  %2d ",tree->content.num);
			num = tree->content.num;
		}
		else if(strstr(operators, tree->content.word)){
			printf("%s",tree->content.word);
		}
		else if(strcmp(tree->content.word,"et") == 0) {
			printf("\n  %2d avec ",num);
		}
		else if(strcmp(tree->content.word,"ni") == 0) {
			printf("\n  %2d sans ",num);
		}
		else if(strcmp(tree->content.word,"mais") == 0) {
			printf("\n  %2d ",num);
		}
		else {
			sum = 0.5 * num;
			printf(" %5s%.2f",tree->content.word,sum);
		}
		sum = sum + InOrder(tree->right);
	}
	return sum;
}

void facture(version* ver){
	while(ver){
		char* sandwich = *ver.type;
		int i;
		kind reqs[count];
		reqs = malloc(count * sizeof(kind));
		for(i = 0; i < count; i++) {
			reqs[i] = ver.types[i];
		}
		printf("%2d",)
	}
}

int main() {

}
