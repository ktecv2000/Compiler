%{
#include <ctype.h>
int i;
%}

%%

^0(x|X)[[:digit:]a-fA-F]{1,8}/[ \t\n]       {   ECHO;puts("");  }
[ \t\n]0(x|X)[[:digit:]a-fA-F]{1,8}/[ \t\n] {   i=0;
                                            while(isspace(*(yytext+i)))
                                                i++;
                                            for(;i<yyleng;i++)
                                                printf("%c", *(yytext+i));
                                            puts("");   }

.|\n

%%

int main()
{   
    yylex();
    return 0;
}