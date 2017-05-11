%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
char err[100];
//int yydebug = 0;
%}
%union {
long long int ival;
long long int mat_val[2];
}
%token <ival> INDEX  ADD_SUB  MUL  TRANS

%type <mat_val> mat  expr
%left ADD_SUB 
%left MUL
%right TRANS

%%
line    : expr      { }
        ;

expr    : '(' expr ')'
                    { $$[0] = $2[0]; $$[1] = $2[1]; }
		| expr MUL expr
                    {
                        if(!($1[1] == $3[0]))
                        {
                            sprintf(err, "Semantic error on col %d\n", $2);
							return 0;
                        }
                        else
                        {
                            $$[0] = $1[0];
                            $$[1] = $3[1];
                        }
                    }
        | expr ADD_SUB expr
                    {
                        if(!($1[0] == $3[0] && $1[1] == $3[1]))
                        {
                            sprintf(err, "Semantic error on col %d\n", $2);
							return 0;
                        }
                    }

        | expr TRANS
                    { $$[0] = $1[1]; $$[1] = $1[0]; }
        | mat
                    { $$[0] = $1[0]; $$[1] = $1[1]; }
        ;

mat     : '[' INDEX ',' INDEX ']'
                    { $$[0] = $2; $$[1] = $4; }
        ;
%%

void yyerror (const char *message)
{
    fprintf (stderr, "Syntax Error");
    exit(0);
}


int main(int argc, char *argv[]) {
    yyparse();
    if(strcmp(err,""))
        printf("%s", err);
    else
        printf("Accepted");
    return(0);
}
