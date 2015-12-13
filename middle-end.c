#include "init.h"
#include "config.h"
#include <stdlib.h>

 void nprintf(node* point) {
	if (point != NULL) {
		printf(typenode == 1?"number: %d\n", point->content.num:"%s\n", point->content.word);
		nprintf(point->left);
	 	nprintf(point->right);
	 }
 }