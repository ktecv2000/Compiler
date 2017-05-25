%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
%}
%union {
int ival;
}
%token <ival> NUM AND OR XOR NOT L_SHIFT R_SHIFT END
%type <ival> expr
%%
line    : expr END { printf("%d", $1); return 0; }
        ;

expr    : AND expr expr
		{
			$$ = $2 & $3 & 31;
		}
		| OR expr expr
		{
			$$ = ($2 | $3) & 31;
		}
		| XOR expr expr
		{
			$$ = ($2 ^ $3) & 31;
		}
		| NOT expr
		{
			$$ = (~$2) & 31;
		}
		| L_SHIFT expr expr
		{
			$$ = ($2 << $3) & 31;
		}
		| R_SHIFT expr expr
		{
			$$ = ($2 >> $3) & 31;
		}
		| NUM
		{
			if($1 > 31 || $1 < 0)
				yyerror("integer out of range");
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
    return(0);
}

