%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
int yydebug = 0;
%}
%union {
int d[2];   /*
                d[1] => -1 : all false
                        0 : some false, some true
                        1 : all true
                        2 : empty
            */
}
%token <d> L_AND R_AND L_OR R_OR L_NOT R_NOT T F
%type <d> expr
%%
line    : expr                  {
                                    if($1[1] == 1)
                                        printf("true\n");
                                    else
                                        printf("false\n");
                                }
        ;

expr    : expr L_AND expr R_AND     {
                                    if($3[1] >= 1)
                                        $$[1] = 1;
                                    else
                                        $$[1] = -1;

                                }
        | expr L_OR expr R_OR       {
                                    if($3[1] == 2)
                                        $$[1] = -1;
                                    else if($3[1] >= 0)
                                        $$[1] = 1;
                                    else
                                        $$[1] = -1;
                                }
        | expr L_NOT expr R_NOT     {
                                    $$[1] = -$3[1];
                                }
        | expr T                {
                                    if($1[1] == 1 || $1[1] == 2)
                                        $$[1] = 1;
                                    else
                                        $$[1] = 0;
                                }
        | expr F                {
                                    if($1[1] == -1 || $1[1] == 2)
                                        $$[1] = -1;
                                    else
                                        $$[1] = 0;
                                }
        |                       {
                                    $$[1] = 2;
                                }
        ;

%%
void yyerror (const char *message)
{
    fprintf (stderr, "Syntax Error\n");
    exit(0);
}
int main(int argc, char *argv[]) {
    yyparse();
    return(0);
}

