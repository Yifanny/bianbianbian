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

void facture(commandes order[]){
	int num = 0;
	int count = 0;
	float total = 0.0;
	while(count<sizeof(order)){
		num = (order[count].head).left->content.num;
		printf("\n%2d %10s",num,order[count].type);
		int i;
		float sum1,sum2;
		for(i = 0; i < 5; i++){
			if(!strcmp(price_list[i].name,order[count].type)){
				sum1 = num * price_list[i].euro;
			}
		}
		total = total + sum1;
		printf("%.2f",sum1);
		node_c* cur = order[count].head.right;
		sum2 = InOrder(cur);
		total = total + sum2;
		count = count+1;	
	}
	printf("\nTotal:%.2f\n",total);
}

/*
int main() {
	union ast_c u1;
	u1.word = NULL;
	union ast_c u2;
	u2.num = 1;
	node_c* number;
	number->left = NULL;
	number->right = NULL;
	number->content = u2;
	node_c tree = {
		u1,number,NULL
	};
	commandes orders[1] = {
		{"panini",tree}
	};
	facture(orders);
	return 0;
}
*/