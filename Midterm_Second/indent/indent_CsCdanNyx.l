%{  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char tmp[10000]={0};
int indent=-1;
int i=0;
char out[100000]={0};
%}

tagId       [[:alpha:]_]+
lefttag     "<"
righttag    ">"
blank       [ \t]+

%x intag
%%
{lefttag}                   {   BEGIN(intag);   }

<intag>{tagId}              {   if ( strcmp(yytext, tmp) )
                                    indent++;
                                strcpy(tmp, yytext);
                                for (i=0;i<indent;i++)
                                    strcat(out, "  ");
                                strcat(out, "<");
                                strcat(out, yytext);
                                strcat(out, ">\n");
                                strcpy(tmp, yytext);
                            }

<intag>{righttag}           {   BEGIN(INITIAL); }

<intag>[^{tagId}]           {   printf("please don't eat me");exit(1);    }

[^[:space:]]                {   printf("please don't eat me");exit(1);    }
.|\n

%%

int main()
{   
    yylex();
    printf("%s", out);
    return 0;

}
