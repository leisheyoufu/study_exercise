##  flex 生成代码流程简析
```
/* 
 * 在分析具体代码前，我们先聊一下 flex 的 fl 库。
 * flex工具带有一个微型的 fl 库，它定义了 main(), yywrap() 接口。 其中：
 *  . main() 函数调用 yylex() 做词法分析;
 *  . yywrap() 简单地返回 1。
 *    yywrap() 的作用是，在yylex()发现到达输入数据末尾时，调用 yywrap()，看是否还有数据，如果有，yywrap() 应该
 *    返回0，否则返回1。
 *
 * 如果我们的flex程序，不自己实现 main() 和 yywrap()，则在编译时，可以给 gcc 指定 -lfl 选项。另外，可以通过给 
 * flex 传递 --noyywrap 选项，或者在 flex 程序中，指定 %option noyywrap 来告诉flex ，我们不调用 yywrap() ，
 * 以此来屏蔽编译链接报错。
 */
/* 接下来，进入具体的代码流程分析 */
main()
	yylex() /* 进入词法分析器入口 */
		/* yylex() 初次调用的初始化。后续 yylex() 调用会在之前的上下文下继续工作。 */
		if ( !(yy_init) )
		{
			(yy_init) = 1;
			...
			if ( ! (yy_start) )
				(yy_start) = 1;	/* first start state */
				
			if ( ! yyin ) /* 没有设定输入, 默认将 stdin 作为输入 */
				yyin = stdin;
				
			if ( ! yyout ) /* 没有设定输出, 默认将 stdout 作为输入 */
				yyout = stdout;
				
			/* 输入缓冲初始化 */
			if ( ! YY_CURRENT_BUFFER ) {
				yyensure_buffer_stack (); /* 创建 yy_buffer_state 输入缓冲管理对象指针栈 */
				YY_CURRENT_BUFFER_LVALUE =
					yy_create_buffer(yyin,YY_BUF_SIZE ); /* 创建栈顶 YY_BUF_SIZE 大小的输入缓冲 */
			}
			
			/*
		 	 * 获取栈顶输入缓冲如下状态:
		 	 * . yy_n_chars: 读到栈顶输入缓冲空间的字符个数
		 	 * . yytext, yy_c_buf_p: 栈顶输入缓冲空间当前位置指针(char *)
		 	 * . yyin: 输入缓冲输入文件
		 	 * . yy_hold_char: 栈顶输入缓冲空间当前字符
		 	 */
			yy_load_buffer_state( );
		}
		
		/* 扫描循环，直到输入结束 */
		while ( /*CONSTCOND*/1 )		/* loops until end-of-file is reached */
		{
			/* 正则匹配状态机循环 */
			yy_current_state = (yy_start);
		yy_match:
			do {
				YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
				...
				yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
				++yy_cp;
			}
			while ( yy_base[yy_current_state] != 17 );
			
			...
			
			/* 一个正则模式匹配完成的后惯例动作:
			 * yytext: 当前正则模式匹配的内容
			 * yyleng: 当前正则模式匹配内容长度
			 * yy_hold_char: 当前正则模式匹配内容的最后一个字符(也即当前字符)
			 * *yy_cp = '\0';
			 * yy_c_buf_p: 下一个待解析字符位置指针
			 */
			YY_DO_BEFORE_ACTION;
		do_action:	/* This label is used only to access EOF actions. */
			/* 状态机正则匹配结束，按匹配的正则做用户定义的动作 */
			switch ( yy_act )
			{ /* beginning of action switch */
			...
			case 1:
				YY_RULE_SETUP
#line 18 "calculator.l"
				{ return ADD; } /* 正则模式匹配时，执行的C代码 */
				YY_BREAK
			...
			default:
				YY_FATAL_ERROR(
					"fatal flex scanner internal error--no action found" );
			}
		}
```
其实 yylex() 的工作逻辑很简单，可以总结如下：
```
while (1)
	从输入读取数据
	按正则模式匹配输入数据
	如果有匹配的模式，执行匹配模式的C代码
	否则，报错
```


## 3.1.4.1 option 选项
(1) 生成可重入词法分析器。

一方面，生成的词法分析器代码，有很多全局变量； 另一方面，在词法分析器入口 yylex() 返回后，下一次调用会接着使用上一次运行后的上下文继续执行。以上两点，不能满足要求可重入的调用的上下文。此时，我们可以通过%option reentrant 选项来生成可重入的词法分析器。此时，我们通过如下代码片段构建可重入的词法分析器：
```
yyscan_t scanner;

yylex_init(&scanner) / yylex_init_extra(extra, &scanner); /* 创建词法分析器上下文 */
while (yylex(scanner)) { /* 基于独立的上下文进行词法分析 */
	...
}
yylex_destroy(scanner); /* 销毁词法分析器上下文 */
```
(2) 改变生成代码函数名。

我们有时候可能不想使用 yylex() 等其它词法分析器接口名，可以通过%option prefix="XXX"作为词法分析器接口名前缀。如：%option prefix="parse_events_"，那生成代码中，yylex() 则变为 parse_events_lex()，当然，还有更多函数名的变换。

(3) 自动维护行号代码。

我们可以自己在规则中，更新 yylineno 来维护行号。当然，也可以通过 %option yylineno选项，让 flex 帮我们自动生成行号维护代码。

(4) 与 bison 协同工作选项。

默认生成的代码，yylex() 函数是没有参数的，除了可以通过%option reentrant选项来增加词法分析器的上下文参数外，我们还可以通过%option bison-bridge和%option bison-locations来改变 yylex() 原型：
```
%option bison-bridge: 为 yylex() 增加参数 YYSTYPE *yylval_param, 用来记录词法分析器解析的 token 的值。
%option bison-locations: 为 yylex() 增加参数 YYLTYPE *yylloc_param, 用来存储行列信息。
```

如果有以下选项配置:
```
%option reentrant
%option bison-bridge
%option bison-locations
...
%%
...
%%
...
```
则生成的 yylex() 函数原型为：
```
int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner);
```
3.1.4.2 定义
类似于C中的宏定义，主要是将正则规则中重复的部分抽离出来，免得重写。我们看一个例子：
```
group		[^,{}/]*[{][^}]*[}][^,{}/]*
%%
{group}		{
			BEGIN(INITIAL);
			REWIND(0);
		}
%%
...
```
上例中，在第一部分定义了 group ，然后再第二部分规则中引用，使用 {} 括起来。

3.1.4.3 定义特定状态下才会执行的规则
```
%x IFILE

%%

^"#"[ \t]*include[ \t]*[\"<] { BEGIN IFILE; }

<IFILE>[^ \t\n\">]+	{
						{
							int c;
							while ((c = input()) && c != '\n');
						}
						yylineno++;
						if (!newfile(yytext))
							yyterminate(); /* no such file */
						BEGIN INITIAL;
					}

<IFILE>.|\n			{
						fprintf(stderr, "%4d bad include line\n", yylineno);
						yyterminate();
					}

<<EOF>>				{ if (!popfile()) yyterminate(); }

^.					{ fprintf(yyout, "%4d %s", yylineno, yytext); }
^\n					{ fprintf(yyout, "%4d %s", yylineno++, yytext); }
\n					{ ECHO; yylineno++; }
.					{ ECHO; }

%%
...
```

上面我们通过 %x 定义了一个 exclusive 的状态 IFILE，在该状态下，只有以 <IFILE> 开头的规则才会被执行，它用来解析 #include 预处理符号。其中，特殊符号<<EOF>>表示遇到文件结尾；词法分析器用 input() 从输入读取一个字符，yylineno 记录行号，yytext 记录当前匹配的文本，ECHO 回显匹配的文本。
词法分析器的初始状态为INITIAL(即0)，可以通过YY_START或YYSTATE获取当前状态，通过BEGIN来切换当前状态，如上例中的BEGIN IFILE;来切换词法分析器的状态为IFILE，在状态IFILE下，只有以<IFILE>开头的规则才会被执行。
另外还可以通过%s定义可共享状态。假设我们通过%s SS定义了状态SS，和%x定义不同的是，除了将<SS>开头的规则限制在只能在SS状态下执行外，而剩余的其它规则，也可以在SS状态下执行。
通常来讲，%x是更加有用的，因为它将分析限制于特定的上下文，这可以简化我们词法分析器的设计。

## referemce
https://blog.csdn.net/JiMoKuangXiangQu/article/details/128200598