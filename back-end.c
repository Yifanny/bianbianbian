/*************************************************************************
    > File Name: back-end.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年12月10日 星期四 19时33分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include "init.h"
#include "config.h"

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

void facture(version* ver, int count){
	cook* cook_list;
	cook_list = init();
	float total = 0.0;
	int k = 0;
	while(k < count){
		char* sandwich = ver[k].type;
		int n = ver[k].num;
		//int n = 2;
		//printf("nnnnn%d\n",n);
		int i, j, sum;
		float cost;
		kind* reqs;
		reqs = malloc(n * sizeof(kind));
		for(i = 0, sum = 0; i < n; i++) {
			reqs[i] = ver[k].types[i];
			sum = sum + reqs[i].cnt;
		}
		printf("%2d%s", sum, sandwich);
		for(i = 0; i < 5; i++){
			if(strcmp(sandwich,price_list[i].name) == 0){
				cost = price_list[i].euro;
				break;
			}
		}
		printf("     %.2f\n", cost * sum);
		total = total + cost * sum;
		cost = 0.0;
		//printf("rererere%lu\n",sizeof(reqs[0].require));
		for(i = 0; i < n; i++){
			//printf("sizeof %lu\n",sizeof(reqs[i].require));
			for(j = 0; j < reqs[i].num/*sizeof(reqs[i].require)*/; j++) {
				//printf("%daaaaa\n",j);
				//printf("%s\n",reqs[i].require[j]);
				//printf("%s\n",strstr(reqs[i].require[j],"avec"));
				if(strstr(reqs[i].require[j],"avec") != NULL || strstr(reqs[i].require[j],"sans") != NULL) {
					printf("  %2d%18s",reqs[i].cnt,reqs[i].require[j]);
					cost = 0.5 * reqs[i].cnt;
					printf("%.2f\n",cost);
				}
				total = total + cost;
			}
		}
		k++;
	}
	printf("          Total : %.2f\n",total);
}


void inventaire(version* ver,int num){
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
	int n, i, j, k, r, count, sum;
	
	int material[5] = {3, 4, 5, 5, 4};
	char** sandwich;
	sandwich = malloc(5 * sizeof(char*));
	for(i = 0; i < 5; i++){
		sandwich[i] = malloc(20 * sizeof(char));
	}
	sandwich[0] = "fromage";
	sandwich[1] = "jambon-beurre";
	sandwich[2] = "panini";
	sandwich[3] = "belge";
	sandwich[4] = "deippois";
	
	ingredient* cur;
	char* modingred;
	//while(ver) {
	int m, f;
	m = 0;
	while(m<num) {
		sum = 0;
		f = 0;
		while(/*ver->types*/ f < ver->num){
			//printf(" sum %d\n",sum);
			sum = sum + ver->types[f].cnt;;
			f++;
		}
		for (i = 0; i < 5; i++) {
			if(strcmp(ver->type,cook_list[i].name) == 0) {
				count = material[i];
				cur = malloc(count * sizeof(ingredient));
				for(r = 0; r < count; r++){
					cur[r] = cook_list[i].material[r];
				}
				for(j = 0; j < material[i]; j++){
					for(k = 0; k < 12; k++) {
						if(strcmp(list[k].name,cook_list[i].material[j].name) == 0){
							list[k].num = list[k].num + sum * cook_list[i].material[j].num;
						}
					}	
				}
				break;
			}
		}
		kind* reqs;
		n = ver->num;
		    //printf("sizeof %lu\n",sizeof(ver->types));
		reqs = malloc(n * sizeof(kind));
		reqs = ver->types;
		for(i = 0; i < n/*n*/; i++) {
			for(j = 0; j < reqs[i].num/*sizeof(reqs[i].require)*/; j++) {
				if(strstr(reqs[i].require[j],"sans") != NULL || strstr(reqs[i].require[j],"avec") != NULL) {
					n = sizeof(reqs[i].require[j]) - 5;
					modingred = malloc(n * sizeof(char));
					modingred = reqs[i].require[j] + 5;
					if(strstr(modingred,"double") != NULL) {
						modingred = modingred + 7;
					}
					     //printf("%s\n",modingred);
					for(k = 0; k < 12; k++) {
						if(strcmp(modingred,list[k].name) == 0) {
							  //printf(" count %s %d\n",ver->type,count);
							for(r = 0; r < count; r++){
								if(strcmp(cur[r].name,modingred) == 0){
									  //printf("cnt %d\n",reqs[i].cnt);
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
		m++;
		ver++;
			//printf("12345\n");
	}
	for(i = 0; i < 12; i++) {
		printf("%s,%.2f\n",list[i].name,list[i].num);
	}
}

void cuisine(version* ver, int count) {
	int str = fopen("./cuisine.html", a+);
	if(fwrite()	
}

int main() {
	int i, j;
	version order[2];
	order[0].type = "panini";
	order[1].type = "belge";

	order[0].num = 2;
	order[1].num = 2;
	order[0].types = malloc(2 * sizeof(kind));
	order[1].types = malloc(2 * sizeof(kind));
	//printf("ooooo\n");
	
	order[0].types[0].require = malloc(1 * sizeof(char*));
	order[0].types[0].require[0] = malloc(20 * sizeof(char));
	order[0].types[0].require[0] = "sans tomate";
	order[0].types[0].cnt = 1;
	order[0].types[0].num = 1;
	//printf("1100000\n");
	order[0].types[1].require = malloc(2 * sizeof(char*));
	order[0].types[1].require[0] = malloc(20 * sizeof(char));
	order[0].types[1].require[1] = malloc(20 * sizeof(char));
	order[0].types[1].require[0] = "avec frites";
	order[0].types[1].require[1] = "sans jambon";
	order[0].types[1].cnt = 2;
	order[0].types[1].num = 2;
	//printf("1200000\n");
	order[1].types[0].require = malloc(1 * sizeof(char*));
	order[1].types[0].require[0] = malloc(20 * sizeof(char));
	order[1].types[0].require[0] = "";
	order[1].types[0].cnt = 3;
	order[1].types[0].num = 1;
	//printf("2100000\n");
	order[1].types[1].require = malloc(2 * sizeof(char*));
	order[1].types[1].require[0] = malloc(20 * sizeof(char));
	order[1].types[1].require[1] = malloc(20 * sizeof(char));
	order[1].types[1].require[0] = "sans steak";
	order[1].types[1].require[1] = "avec double frites";
	order[1].types[1].cnt = 1;
	order[1].types[1].num = 2;
	//printf("2200000\n");

	//printf("%s\n",order[0].types[0].require[0]);	
	//printf("lalala\n");
	facture(order,2);
	inventaire(order,2);
	return 0;
}
