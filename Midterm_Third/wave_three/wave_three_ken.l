%{
#include "wave_three.tab.h"
%}
%%

"-"?[0-9]+ {
	if(strlen(yytext) > 2)
		yyerror("integer out of range");
	yylval.ival = atoi(yytext);
	return NUM;
}
[ ] {}
"& " {return AND;}
"| " {return OR;}
"^ " {return XOR;}
"~ " {return NOT;}
"<< " {return L_SHIFT;}
">> " {return R_SHIFT;}
\n {return END;}
.

%%

