count-words: count-words.l
	flex --noyywrap count-words.l # 生成词法分析器代码 lex.yy.c
	gcc -o $@ lex.yy.c # 编译词法分析器 lex.yy.c 

clean:
	-rm -f lex.yy.c count-words