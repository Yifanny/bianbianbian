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

