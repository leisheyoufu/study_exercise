calculator: calculator.l calculator.y
	bison -d calculator.y
	flex calculator.l
	gcc -o calculator calculator.tab.c lex.yy.c -lfl

clean:
	-rm -f calculator lex.yy.c *.tab.*