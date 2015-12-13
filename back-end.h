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
