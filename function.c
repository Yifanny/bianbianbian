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

ingredient* inventaire(version* ver,int num){
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
	return list;
}