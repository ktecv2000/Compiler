
%%

^([^[:space:]]+[[:blank:]]+){2}"noodles".*$		{	ECHO;puts("");	}
.|\n

%%

int main()
{	
	yylex();
	return 0;
}
