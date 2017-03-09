%{
#include <stdlib.h>
#include <ctype.h>
#define YY_MAIN 1
#define yywrap() 1
%}
%%
.|\n {}
^([0-9]{1,3}"."){3}[0-9]{1,3} {
	char * const pointer = malloc(yyleng);
	char * str = pointer;
	strcpy(pointer, yytext);
	int part = 0;
	while(str < pointer + yyleng)
	{
		if(!isdigit(*str))
		{
			if(part > 255)
			{
				free(pointer);
				YY_BREAK;
			}
			part = 0;
		}
		else
		{
			part = ((*str) - '0') + part * 10;
		}
		str++;
	}
	if(part > 255)
	{
		free(pointer);
		YY_BREAK;
	}
	ECHO; printf("\n");
	free(pointer);
}
%%
