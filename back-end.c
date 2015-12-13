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

typedef struct ingredient {
	float num;
	char* name;
}ingredient;

typedef struct cook {
	char* name;
	ingredient material[5];
}cook;

ingredient cook_fromage[3] = {
	{1.0,"pain"},
	{10.0,"beurre"},
	{2.0,"emmental"}
};

ingredient cook_jambon[4] = {
	{1.0,"pain"},
	{1.0,"jambon"},
	{10.0,"beurre"},
	{10.0,"salade"}
};

ingredient cook_panini[5] = {
	{1.0,"pain"},
	{1.0,"jambon"},
	{2.0,"emmental"},
	{0.5,"tomato"},
	{10.0,"salade"}
};

ingredient cook_belge[5] = {
	{1.0,"pain"},
	{1.0,"steak"},
	{50.0,"frites"},
	{20.0,"mayonnaise"},
	{10.0,"salade"}
};

ingredient cook_dieppois[4] = {
	{1.0,"pain"},
	{50.0,"thon"},
	{20.0,"mayonnaise"},
	{10.0,"salade"}
};

cook* init(){
	int i;
	cook* cook_list;
	cook_list = malloc(5 * sizeof(cook));
	cook_list[0].name = "fromage";
	for(i = 0; i < sizeof(cook_fromage); i++){
			cook_list[0].material[i] = cook_fromage[i];
	}
	cook_list[1].name = "jambon-beurre";
	for(i = 0; i < sizeof(cook_jambon); i++){
		cook_list[1].material[i] = cook_jambon[i];
	}
	cook_list[2].name = "panini";
	for(i = 0; i < sizeof(cook_panini); i++){
		cook_list[2].material[i] = cook_panini[i];
	}
	cook_list[3].name = "belge";
	for(i = 0; i < sizeof(cook_belge); i++){
		cook_list[3].material[i] = cook_belge[i];
	}
	cook_list[4].name = "dieppois";
	for(i = 0; i < sizeof(cook_dieppois); i++){
		cook_list[4].material[i] = cook_dieppois[i];
	}
	return cook_list;
}
/*float InOrder(node_c* tree) {
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
}*/

void facture(version* ver){
	cook* cook_list;
	cook_list = init();
	float total = 0.0;
	while(ver){
		char* sandwich = ver->type;
		int n = sizeof(ver->types);
		int i, j, sum;
		float cost;
		kind* reqs;
		reqs = malloc(n * sizeof(kind));
		for(i = 0, sum = 0; i < n; i++) {
			reqs[i] = ver->types[i];
			sum = sum + reqs[i].cnt;
		}
		printf("%2d%20s", sum, sandwich);
		for(i = 0; i < 5; i++){
			if(strcmp(sandwich,price_list[i].name) == 0){
				cost = price_list[i].euro;
				break;
			}
		}
		printf("%.2f\n", cost * sum);
		total = total + cost * sum;
		cost = 0.0;
		for(i = 0; i < n; i++){
			for(j = 0; j < sizeof(reqs[i].require); j++) {
				printf("  %2d%18s",reqs[i].cnt,reqs[i].require[j]);
				cost = 0.5 * reqs[i].cnt;
				printf("%.2f\n",cost);
				total = total + cost;
			}
		}
		ver++;
	}
	printf("          Total : %.2f\n",total);
}


void inventaire(version* ver){
	cook* cook_list;
	cook_list = init();
	ingredient list[12] = {
		{0.0,"pain"},
		{0.0,"jambon"},
		{0.0,"beurre"},
		{0.0,"salade"},
		{0.0,"emmental"},
		{0.0,"ketchup"},
		{0.0,"moutarde"},
		{0.0,"mayonnaise"},
		{0.0,"frites"},
		{0.0,"tomate"},
		{0.0,"steak"},
		{0.0,"thon"}
	};
	int n, i, j, k, r;
	ingredient* cur;
	char* modingred;
	while(ver) {
		for (i = 0; i < 5; i++) {
			if(strcmp(ver->type,cook_list[i].name) == 0) {
				n = sizeof(cook_list[i].material);
				cur = malloc(n * sizeof(ingredient));
				cur = cook_list[i].material;
				for(j = 0; j < sizeof(cook_list[i].material); j++){
					for(k = 0; k < 12; k++) {
						if(strcmp(list[k].name,cook_list[i].material[j].name) == 0){
							list[k].num = list[k].num + cook_list[i].material[j].num;
						}
					}	
				}
				break;
			}
		}
		kind* reqs;
		n = sizeof(ver->types);
		reqs = malloc(n * sizeof(kind));
		reqs = ver->types;
		for(i = 0; i < n; i++) {
			for(j = 0; j < sizeof(reqs[i].require); j++) {
				if(strstr(reqs[i].require[j],"sans") != NULL || strstr(reqs[i].require[j],"avec") != NULL) {
					n = sizeof(reqs[i].require[j]) - 5;
					modingred = malloc(n * sizeof(char));
					modingred = reqs[i].require[j] + 5;
					for(k = 0; k < 12; k++) {
						if(strcmp(modingred,list[k].name) == 0) {
							for(r = 0; r < sizeof(cur); r++){
								if(strcmp(cur[r].name,modingred) == 0){
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * cur[r].num;
									}
									else{
										list[k].num = list[k].num + reqs[i].cnt * cur[r].num;
									}
								}
							}	
						}
					}
				}
			}
		}
		ver++;
	}
	for(i = 0; i < 12; i++) {
		printf("%s,%.2f\n",list[i].name,list[i].num);
	}
}

int main() {

}
