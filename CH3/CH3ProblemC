%{
#include <stdlib.h>
#define YY_MAIN 1
#define yywrap() 1
%}
%%
.|\n 
^[ \t]*0[xX][0-9a-fA-F]{1,8}[ \t]*\/\/.*$ {
	int len = strlen(yytext);
	char * const pointer = (char *)malloc(len);
	char * str = pointer;
	char * tail = pointer + len - 1;
	strcpy(pointer, yytext);
	while((*str == ' ' || *str == '\t') && str < tail)
		str++;
	while(*tail != '/' && tail > str )
		*(tail--) = 0;
	tail -= 2;
	while((*tail == ' ' || *tail == '\t') && tail > str )
		*(tail--) = 0;
	printf("%s\n", str);
	free(pointer);
}
^[ \t]*0[xX][0-9a-fA-F]{1,8}[ \t]*$ {
	int len = strlen(yytext);
	char * const pointer = (char *)malloc(len);
	char * str = pointer;
	char * tail = pointer + len - 1;
	strcpy(pointer, yytext);
	while((*str == ' ' || *str == '\t') && str < tail)
		str++;
	while((*tail == ' ' || *tail == '\t') && tail > str )
		*(tail--) = 0;
	printf("%s\n", str);
	free(pointer);
}
%%
