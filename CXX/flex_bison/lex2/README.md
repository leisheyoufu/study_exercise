make
./count-words a.txt b.txt # a.txt, b.txt 作为输入
如果不指定输入（具体是修改yyin全局变量），程序默认使用标准输入；如果要修改输入，我们可以通过yyrestart()修改。