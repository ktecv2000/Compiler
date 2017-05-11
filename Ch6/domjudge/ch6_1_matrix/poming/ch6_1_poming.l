%{
#include "ch6_1_poming.tab.h"
long long int count = 1;
%}
%%

\n  { return(0); /* EOF */ }
[ \t]+  { count += strlen(yytext); }
[0-9]+  {
            yylval.ival= atoi(yytext);
            count += strlen(yytext);
            return INDEX;
        }
"+"|"-" { yylval.ival = count++; return ADD_SUB; }
"*" { yylval.ival = count++; return MUL; }
"\^T" { count += strlen(yytext); return TRANS; }
.   { count += strlen(yytext); return yytext[0]; }

%%
