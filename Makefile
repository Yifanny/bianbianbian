fastfood: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -o fastfood -ly -ll
y.tab.c: fastfood.y
	bison -y fastfood.y
lex.yy.c: fastfood.l
	lex fastfood.l
	
clean:
	rm fastfood y.tab.* lex.yy.c cuisine.html
