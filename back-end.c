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

/* This function is for initialization of a list
 * which include the name of a sandwich and a list of its neccessary ingredients
 * for each type of sandwich, the ingredients for this sandwich 
 * have already declared and stored in the file config.h
 * return the list of recettes of sandwichs 
 */
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

/* This is an auxilary funtion
 * it has two arguments, one is the name of sandwich 
 * the other is the name of one of its ingredients
 * then return the quantity of this kind of ingredient 
 */
float search(char* sandwich, char* ingredient) {
	float m;
	int i, j, k;
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

/* This is the funtion for printing the facture of commandes
 * it has two arguments, one is a list of versions of sandwichs
 * the other is the number of versions 
 */
void facture(version* ver, int count){
	cook* cook_list;
	cook_list = init();
	float total = 0.0;
	int k = 0;
	int ndh, net, ni, r, n;
	int i, j, sum;
	float cost;
	kind* reqs;
	char sandwich[20];
	
/* This loop is for traversing each sandwich of this list of version*/
	while(k < count){
 		strcpy(sandwich, ver[k].type);
		n = ver[k].num;
		reqs = malloc(n * sizeof(kind));
		for(i = 0, sum = 0; i < n; i++) {
			reqs[i] = ver[k].types[i];
			sum = sum + reqs[i].cnt;
		}
		printf("%2d %-26s", sum, sandwich);
		
/* This loop is for finding the price of this sandwich*/
		for(i = 0; i < 5; i++){
			if(strcmp(sandwich,price_list[i].name) == 0){
				cost = price_list[i].euro;
				break;
			}
		}
		printf("%.2f\n", cost * sum);
		total = total + cost * sum;
		cost = 0.0;
		
/* This loop is in order to traversing all types of this version 
 * the next loop in this loop is for traversing each require in one type 
 */
		for(i = 0; i < n; i++){
			for(j = 0; j < reqs[i].num; j++) {
				if(strstr(reqs[i].require[j],"avec") != NULL || strstr(reqs[i].require[j],"sans") != NULL) {
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j] + 5);
					}
					else {
						printf("  %2d %-25s",reqs[i].cnt,reqs[i].require[j]);
					}
					cost = 0.5 * reqs[i].cnt;
					ndh = net = ni = 0;

/* This loop is for searching ',' or 'et' or 'ni' in the current require */
					for(r = 0; r < strlen(reqs[i].require[j])-2; r++){
						if(reqs[i].require[j][r] == ','){
							ndh = ndh + 1;
						}
						else if(reqs[i].require[j][r] == ' '){
							if(reqs[i].require[j][r+1] == 'e'){
								if(reqs[i].require[j][r+2] == 't')
									net = net + 1;	
							}
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


/* This function is for calculation of the inventory of ingredients
 * it has two arguments like the previous function
 * one is a list of versions, the other is the number of the versions in this list
 * it prints a list of neccessary ingredients for this list of versions 
 */
void inventaire(version* ver,int num){			
	cook* cook_list;
	cook_list = init();
	ingredient* cur;
	char* modingred;
	int m, f;
	int n, i, j, k, r, count, sum;
	int l;
	char* ingred;
	kind* reqs;
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
	

/* This array is definited to store the number of ingredients for each sandwich*/	
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
	
	
/* This loop is used for traversing all verions of sandwichs */	
	m = 0;
	while( m < num ) {
		sum = 0;
		f = 0;

/* This loop is for calculating the total quantity of this version */
		while(f < ver[m].num){
			sum = sum + ver[m].types[f].cnt;;
			f++;
		}
		
/* This loop is for searching which type this version is 
 * the next three loops are for adding the quantity in the final list of ingredients 
 */
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
	//printf("%d  :  %s\n",m ,ver[m].type);	
/* This part is for check that if there are "sans" or "avec" 
 * and change the quantity in the list of ingredients 
 */
		n = ver->num;
		reqs = malloc(n * sizeof(kind));
		reqs = ver->types;
/* This loop is for traversing all types in the current version 
 * the next one is for traversing all requires in each type 
 */
		for(i = 0; i < n; i++) {
			for(j = 0; j < reqs[i].num; j++) {
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
					
					l = 1;
/* In the next two loops, they are for check the ingredients in require
 * and change its quantity in the list of ingredients 
 */
					for(r = 0; r < strlen(modingred) - 1; ){
						for(k = 0; k < 12; k++) {
							if(modingred[r] == list[k].name[0]) {
								if(modingred[r+1] == list[k].name[1]) {
									ingred = list[k].name;
									l = strlen(list[k].name);
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * search(ver->type,ingred);
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
	}
	for(i = 0; i < 12; i++) {
		printf("%s,%.2f\n",list[i].name,list[i].num);
	}
}


/* This function is for outputing a file which include HTML for showing the list to the cook 
 * the two arguments are the same as the previous function
 * one is a list of version, the other is number of version 
 */
void cuisine(version* ver, int count) {
	int a, b, c, d, num, m;
	int stream;
	int n = 0;
	int i, j, k;
	int flag[count];
	
	for(i = 0; i < count; i++) {
		flag[i] = 0;
	}
	
/* This part is for combination of the same version in the list of version */	
	for(a = 0; a < count; a++) {
		for(b = a + 1; b < count; b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				flag[b] = 1;
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
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

/* open the file cuisine.html, if there isn't this file, create one */	
	if((stream = open("cuisine.html", O_RDWR|O_TRUNC|O_CREAT, S_IRWXU)) == -1) {
		printf("create fail:%s\n",strerror(errno));
		exit(1);	
	}
/* write the content into this file */
	char buf[256] = "<html><head><title>Cuisine</title><body>";
	if(write(stream, buf, strlen(buf))== -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
/* traverse all the versions after combination 
 * and write them into the file in a certain form of HTML
 */
	while(n < count) {
		if(flag[n] == 0) {
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
		else {
			n++;
		}
	}
	char buf3[256] = "</body></html>";
	if(write(stream, buf3, strlen(buf3)) == -1) {
		printf("write fail:%s\n",strerror(errno));
		exit(1);
	}
}


version* combine_types(version* ver, int* count) {
	int a, b, c, d, num, m;
	int n = 0;
	int i, j, k;
	int* flag;
	version* new_ver;
	
	//printf("aaaaa%d\n",ver[0].num);
	flag = malloc((*count) * sizeof(int));
	for(i = 0; i < (*count); i++) {
		flag[i] = 0;
	}
	
/* This part is for combination of the same version in the list of version */	
	for(a = 0; a < (*count); a++) {
		for(b = a + 1; b < (*count); b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				flag[b] = 1;
				num = ver[a].num;
				printf("%d %d %d %d\n",a,ver[a].num,b,ver[b].num);
				ver[a].num = ver[a].num + ver[b].num;
				//printf("%d %s\n",ver[a].num,ver[a].type);
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						int len = strlen(ver[b].types[c].require[d]);
				    	ver[a].types[num+c].require[d] = malloc(len*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	new_ver = malloc(5 * sizeof(version));
	for (i = 0, j = 0; i < (*count); i++) {
		if(flag[i] == 0) {
			new_ver[j] = ver[i];
			j = j + 1;
		}
	}
	*count = j;
	//printf("lalala : %d\n",*count);
	return new_ver;
}


void combination (version* vers, int count) {
	//printf("aaaaa%d\n",vers[0].num);
	char* ingredient[12] = {"pain", "jambon","beurre", "salade", "emmental", 
	"ketchup", "moutarde", "mayonnaise", "frites", "tomate", "steak", "thon"};
	int i, j, k, p, q, m, n, flag;
	char** reqs;
	int* pcount = &count;
	   //printf("aaaaa%d\n",vers[0].num);
	version* ver = combine_types(vers, pcount);
	printf("0 : %s\n",ver[0].type);
	printf("1 : %s\n",ver[1].type);
	printf("2 : %s\n",ver[2].type);
	//count = *pcount;
	//printf("lalala : %d\n",count);
	flag = 1;
	for(i = 0; i < count; i++) {
		//if(flags[i] == 0){
		//printf("lalala : %d\n",i);
		//printf("%s   %d\n",ver[i].type, ver[i].num);
			for(p = 0; p < ver[i].num - 1; p++) {
				for(q = p + 1; q < ver[i].num; q++) {
					//printf("qqqqqq %d\n",q);
					for(n = 0; n < 2; n++) {
						for(k = 0; k < 12; k++){
							//printf("fff %d : %s %d %s\n",k,ver[i].type,flag,ingredient[k]);
							if(strstr(ver[i].types[p].require[n],ingredient[k]) != NULL) {
								if(strstr(ver[i].types[q].require[n],ingredient[k]) != NULL) {
									flag = 0;
									printf("asdf\n");
								}
								else {
									flag = 1;
									break;
								}
							}
						}
						//printf("nnnnnn %d\n",n);
					}
					if(flag == 0) {
						ver[i].types[p].cnt = ver[i].types[q].cnt + ver[i].types[p].cnt;
						for(j = q + 1; j < ver[i].num; j++) {
							for(m = 0; m < 2; m++) {
								strcpy(ver[i].types[j-1].require[m],ver[i].types[j].require[m]);	
							}
							ver[i].types[j-1].cnt = ver[i].types[j].cnt;
						}
						ver[i].num = ver[i].num - 1;
					}
				}
			}
		//}
	}
}


int main() {
	int i, j;
	version order[3];
	order[0].type = "panini";
	order[1].type = "belge";
	order[2].type = "panini";

//printf("lalala\n");
	order[0].num = 2;
	order[1].num = 2;
	order[2].num = 1;
	order[0].types = malloc(2 * sizeof(kind));
	order[1].types = malloc(2 * sizeof(kind));
	order[2].types = malloc(1 * sizeof(kind));
//printf("ooooo\n");
	
	order[0].types[0].require = malloc(2 * sizeof(char*));
	order[0].types[0].require[0] = malloc(20 * sizeof(char));
	order[0].types[0].require[1] = malloc(20 * sizeof(char));
	order[0].types[0].require[0] = "avec ketchup";
	order[0].types[0].require[1] = "sans tomate";
	order[0].types[0].cnt = 1;
	order[0].types[0].num = 2;
//printf("1100000\n");
	order[0].types[1].require = malloc(2 * sizeof(char*));
	order[0].types[1].require[0] = malloc(20 * sizeof(char));
	order[0].types[1].require[1] = malloc(20 * sizeof(char));
	order[0].types[1].require[0] = "avec frites, pain";
	order[0].types[1].require[1] = "mais sans jambon";
	order[0].types[1].cnt = 2;
	order[0].types[1].num = 2;
//printf("1200000\n");
	order[1].types[0].require = malloc(2 * sizeof(char*));
	order[1].types[0].require[0] = malloc(20 * sizeof(char));
	order[1].types[0].require[1] = malloc(20 * sizeof(char));
	order[1].types[0].require[0] = "";
	order[1].types[0].require[1] = "";
	order[1].types[0].cnt = 3;
	order[1].types[0].num = 2;
//printf("2100000\n");
	order[1].types[1].require = malloc(2 * sizeof(char*));
	order[1].types[1].require[0] = malloc(20 * sizeof(char));
	order[1].types[1].require[1] = malloc(20 * sizeof(char));
	order[1].types[1].require[0] = "sans steak ni salade";
	order[1].types[1].require[1] = "mais avec double frites";
	order[1].types[1].cnt = 1;
	order[1].types[1].num = 2;
//printf("2200000\n");
	order[2].types[0].require = malloc(2 * sizeof(char*));
	order[2].types[0].require[0] = malloc(20 * sizeof(char));
	order[2].types[0].require[1] = malloc(20 * sizeof(char));
	order[2].types[0].require[0] = "avec frites, pain";
	order[2].types[0].require[1] = "sans jambon";
	order[2].types[0].cnt = 2;
	order[2].types[0].num = 2;

//printf("%s\n",order[0].types[0].require[0]);	
//printf("lalala\n");
	facture(order,3);
	inventaire(order,3);
	//printf("bbbbbb%d\n",order[0].num);
	//cuisine(order,3);
	combination(order,3);
	//facture(order,2);
	return 0;
}
