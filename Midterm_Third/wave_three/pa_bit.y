%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
int yydebug = 0;
int ans;
%}
%union {
int ival;
}
%token <ival> AND OR XOR NOT L_SHIFT R_SHIFT NUM
%type <ival> expr
%%
line    : expr                  {
                                    ans = $1;
                                }
        ;
expr    :  AND expr expr        {
                                    $$ = $2 & $3;
                                    
                                }
        |  OR expr expr         {
                                    $$ = $2 | $3;
                                    
                                }
        |  XOR expr expr        {
                                    $$ = $2 ^ $3;
                                    
                                }
        |  NOT expr             {
                                    //$$ = ~$2;
                                    $$ = 31 - $2;
                                   
                                }
        |  L_SHIFT expr expr    {
                                    $$ = $2 << $3;
                                  
                                }
        |  R_SHIFT expr expr    {
                                    $$ = $2 >> $3;
                                    
                                }
        | NUM                   {
                                    $$ = $1;
                                }
        ;

%%
void yyerror (const char *message)
{
    printf("%s", message);
    exit(0);
}
int main(int argc, char *argv[]) {
    yyparse();
    printf("%d", ans);
    return(0);
}
