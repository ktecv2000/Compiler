%{  
#include <stdio.h>
#include <string.h>
char tmp[10000]={0};
int indent=-1;
int i=0;
char out[10000]={0};
%}

tagId       [[:alpha:]_]+
lefttag     "<"
righttag    ">"
blank       [ \t\n\r]+

%%

{lefttag}{tagId}{righttag}  {   if ( strcmp(yytext, tmp) )
                                    indent++;
                                for (i=0;i<indent;i++)
                                    strcat(out, "  ");
                                strcat(out, yytext);
                                strcat(out, "\n");
                                strcpy(tmp, yytext);
                            }

{blank}
.                           {   printf("please don't eat me");exit(1);    }

%%

int main()
{   
    yylex();
    printf("%s", out);
    return 0;
}
