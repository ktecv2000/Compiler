
match		"cpy"[[:alnum:]_\$]*|[[:alpha:]_\$][[:alnum:]_\$]*"cpy"[[:alnum:]_\$]*

%%

{match}	{	ECHO;
			    puts(""); }
.|\n

%%

int main()
{
	yylex();
	return 0;
}
