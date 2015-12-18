#include "middle-end.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 void nshow(node* point) {
	if (point != NULL) {
		if (point->typenode == 1) {
					printf("number: %d\n", point->content.num);
		}
		else {
			printf("%s\n", point->content.word);
		}
		
		nshow(point->left);
	 	nshow(point->right);
	 }
 }
 
 cook* init() {
	int i;
	cook* cook_list;
	cook_list = malloc(CNTSANDW * sizeof(cook));
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

int check(char* ingredient, char* type) {
	int i, j;
	for (i = 0; i < CNTSANDW; i++) {
		if (!strcmp(type, menu[i].name)) {
			for (j = 0; j < material[i]; j++) {
				if (!strcmp(ingredient, menu[i].material[j].name)) {
					return 1;
				}
			}
			return 0;
		}
	}
}

int verifie_commandes(node* point, char* type, char* opr, int cnt) {
	int ret;
	if (point != NULL) {
		switch (point->typenode) {
			case 0:
				if ((ret = verifie_commandes(point->left, type, NULL, cnt)) >= 0) {
					return verifie_commandes(point->right, type, NULL, ret);
				}
				else {
					return -1;
				}
				break;
			case 1:
				if (cnt - point->content->num < 0) {
					return -1;
				}
				else {
					return cnt - point->content->num;
				}
				break;
			case 2:
				switch (opr) {
					case "avec ":
					case "mais avec ":
						if (check(point->content.word, type)) {
							return -1;
						}
						else {
							return cnt;
						}
					case "sans ":
					case "mais sans ":
					case "avec double ":
					case "mais avec double ":
						if (check(point->content.word, type)) {
							return cnt;
						}
						else {
							return -1;
						}
				}
				break;
			case 3:
				switch (point->content.word) {
					case "avec ":
					case "sans ":
					case "avec double ":
					case "mais avec ":
					case "mais avec double ":
					case "mais sans ":
						if ((ret = verifie_commandes(point->left, type, point->content.word, cnt)) >= 0) {
							return verifie_commandes(point->right, type, point->content.word, ret);
						}
						else {
							return -1;
						}
					case "ni ":
				   	case "et ":
					case ", ":
						if ((ret = verifie_commandes(point->left, type, opr, cnt)) >= 0) {
							return verifie_commandes(point->right, type, opr, ret);
						}
						else {
							return -1;
						}
					case "et double ":
					case ", double ":
						if (strstr(opr, avec) != NULL）{
							if ((ret = verifie_commandes(point->left, type, avec_double, cnt)) >= 0) {
								return verifie_commandes(point->right, opr, ret);
							}
							else {
								return -1;
							}
						}
						else {
							return -1;
						}
					case default:
						return -1;
				}
		}
	}
}


int* combine_types(version* ver, int count) {
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
				    	ver[a].types[num+c].require[d] = malloc(len*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	return flag;
}


void combination (version* ver, int count) {
	char* ingredient[12] = {"pain", "jambon" "beurre", "salade", "emmental", 
	"ketchup", "moutarde", "mayonnaise", "frites", "tomate", "steak", "thon"};
	int i, j, k, p, q, m, n, flag;
	char** reqs;
	int* flags = combine_types(ver, count);
	flag = 0;
	for(i = 0; i < count; i++) {
		if(flags[i] == 0){
			for(p = 0; p < ver[i].num - 1; p++) {
				for(q = p + 1; q < ver[i].num; q++) {
					for(k = 0; k < 12; k++) {
						for(n = 0; n < 2; n++) {
							if(strstr(ver[i].types[p].require[n],ingredient[k]) != NULL) {
								if(strstr(ver[i].types[q].require[n],ingredient[k]) != NULL) {
									flag = 0;
								}
								else {
									flag = 1;
									break;
								}
							}
						}
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
		}
	}
}