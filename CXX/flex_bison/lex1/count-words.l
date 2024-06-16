%{
int chars = 0; /* 字符计数 */
int words = 0; /* 单词计数 */
int lines = 0; /* 行计数 */
%}

%%

[a-zA-Z]+	{ words++; chars += strlen(yytext); }
\n		{ chars++; lines++; }
.		{ chars++; }

%%

int main(int argc, char *argv[])
{
	yylex();

	printf("%8d%8d%8d\n", chars, words, lines);

	return 0;
}