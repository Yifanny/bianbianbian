/*************************************************************************
    > File Name: back-end.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年12月10日 星期四 19时33分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
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

float find(char* sandwich, char* ingredient) {
	float m;
	int i, j, k;
	int material[5] = {3, 4, 5, 5, 4};
	cook* cook_list;
	cook_list = init();
	for(i = 0; i < 5; i++) {
		if(strcmp(sandwich,cook_list[i].name) == 0) {
			for(j = 0; j < material[i]; j++) {
				if(strcmp(ingredient,cook_list[i].material[j].name) == 0) {
					m = cook_list[i].material[j].num;
					break;
				}
			}
			break;
		}
	}
	return m;
}

void facture(version* ver, int count){
	cook* cook_list;
	cook_list = init();
	float total = 0.0;
	int k = 0;
	int ndh, net, ni, r;
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
		printf("%2d %-26s", sum, sandwich);
		for(i = 0; i < 5; i++){
			if(strcmp(sandwich,price_list[i].name) == 0){
				cost = price_list[i].euro;
				break;
			}
		}
		printf("%.2f\n", cost * sum);
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
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j] + 5);
					}
					else {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j]);
					}
					cost = 0.5 * reqs[i].cnt;
					ndh = net = ni = 0;
					for(r = 0; r < strlen(reqs[i].require[j])-1; r++){
						if(reqs[i].require[j][r] == ','){
							ndh = ndh + 1;
						}
						else if(reqs[i].require[j][r] == 'e'){
							if(reqs[i].require[j][r+1] == 't')
								net = net + 1;
						}
						else if(reqs[i].require[j][r] == 'n'){
							if(reqs[i].require[j][r+1] == 'i')
								ni = ni + 1;
						}
					}
					cost = cost + 0.5 * reqs[i].cnt * (ndh + net + ni);
					printf("%.2f\n",cost);
				}
				total = total + cost;
			}
		}
		k++;
	}
	printf("                   Total :   %.2f\n",total);
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
	
	ingredient add[12] = {
		{1.0,"pain"},
		{1.0,"jambon"},
		{10.0,"beurre"},
		{10.0,"salade"},
		{2.0,"emmental"},
		{10.0,"ketchup"},
		{10.0,"moutarde"},
		{20.0,"mayonnaise"},
		{50.0,"frites"},
		{0.5,"tomate"},
		{1.0,"steak"},
		{50.0,"thon"}
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
	while( m < num ) {
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
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						n = (int)sizeof(reqs[i].require[j]) - 10;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 10;
					}
					else{
						n = sizeof(reqs[i].require[j]) - 5;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 5;	
					}
					/*if(strstr(modingred,"double") != NULL) {
						modingred = modingred + 7;
					}*/
					     //printf("%s\n",modingred);
					int l;
					char* ingred;
					l = 1;
					for(r = 0; r < strlen(modingred) - 1; ){
						for(k = 0; k < 12; k++) {
							if(modingred[r] == list[k].name[0]) {
								if(modingred[r+1] == list[k].name[1]) {
									ingred = list[k].name;
									l = strlen(list[k].name);
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * find(ver->type,ingred);
									}
									else{
										list[k].num = list[k].num + reqs[i].cnt * add[k].num;
									}
									break;
								}
							}
							else{
								l = 1;
							}
						}
						r = r + l; 
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
	int a, b, c, d, num, m;
	for(a = 0; a < count; a++) {
		for(b = a + 1; b < count; b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					//ver[a].types[num+c] = malloc(sizeof(kind));
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						int len = strlen(ver[b].types[c].require[d]);
				    	ver[a].types[num+c].require[d] = malloc(d*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	
	int stream;
	if((stream = open("cuisine.html", O_RDWR|O_TRUNC|O_CREAT, S_IRWXU)) == -1) {
		printf("create fail:%s\n",strerror(errno));
		exit(1);	
	}
	char buf[256] = "<html><head><title>Cuisine</title><body>";
	if(write(stream, buf, strlen(buf))== -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
	int n = 0;
	int i, j, k;
	while(n < count) {
		char buf1[256];
		strcpy(buf1, "<h1>");
		strcat(buf1, ver[n].type);
		strcat(buf1, "</h1><ul>");
		if(write(stream, buf1, strlen(buf1)) == -1) {
			printf("write %s fail:%s\n", ver[n].type, strerror(errno));
			exit(1);
		}
		char buf2[256] = " ";
		for(i = 0; i < ver[n].num; i++){
			strcat(buf2, "<li>");
			char tmp[20];
			//itoa(ver[n].types[i].cnt, tmp, 10);
			sprintf(tmp,"%d", ver[n].types[i].cnt);
			strcat(buf2,tmp);
			for(j = 0; j < ver[n].types[i].num; j++) {
				strcat(buf2," ");
				if(strcmp(ver[n].types[i].require[j], "") == 0 ) {
					strcat(buf2, "normaux");
				}
				strcat(buf2,ver[n].types[i].require[j]);
			}
			strcat(buf2,"</li>");
		}
		strcat(buf2,"</ul>");
		if(write(stream, buf2, strlen(buf2)) == -1) {
			printf("write requires of %s fail:%s\n", ver[n].type, strerror(errno));
			exit(1);
		}
		n++;
	}
	char buf3[256] = "</body></html>";
	if(write(stream, buf3, strlen(buf3)) == -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
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
	order[0].types[1].require[0] = "avec frites, pain";
	order[0].types[1].require[1] = "mais sans jambon";
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
	order[1].types[1].require[0] = "sans steak ni salade";
	order[1].types[1].require[1] = "mais avec double frites";
	order[1].types[1].cnt = 1;
	order[1].types[1].num = 2;
	//printf("2200000\n");

	//printf("%s\n",order[0].types[0].require[0]);	
	//printf("lalala\n");
	facture(order,2);
	inventaire(order,2);
	cuisine(order,2);
	return 0;
}
