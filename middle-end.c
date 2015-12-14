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

