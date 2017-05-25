%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
%}
%union {
char ival;
char ivals[2];
}
%token <ival> VAL OR_START OR_END AND_START AND_END NOT_START NOT_END
%type <ival> expr
%type <ivals> exprs
%%
all		: expr { printf($1 ? "true\n" : "false\n"); }
        ;

expr    : OR_START exprs OR_END {$$ = $2[1];}
		| AND_START exprs AND_END {$$ = $2[0];}
		| NOT_START expr NOT_END {$$ = !$2;}
		| VAL {$$ = $1;}
		;
exprs	: expr exprs {$$[0] = $1 & $2[0]; $$[1] = $1 | $2[1];}
		| {$$[0] = 1; $$[1] = 0;}
		;
%%

void yyerror (const char *message)
{
	printf("%s", message);
	exit(0);
}


int main(int argc, char *argv[]) {
    yyparse();
    return(0);
}

