%{
#include "pa_bit.tab.h"
%}

%%

"\n"        { return 0; }
"-"?[0-9]+  {
                if(yytext[0] == '-')
                    yyerror("integer out of range");
                else if(strlen(yytext) > 2)
                    yyerror("integer out of range");
                int val = atoi(yytext);
                if(val > 31)
                    yyerror("integer out of range");
                yylval.ival = val;
                return NUM;
            }
"& "        { return AND;}
"| "        { return OR;}
"^ "        { return XOR;}
"~ "        { return NOT;}
"<< "       { return L_SHIFT;}
">> "       { return R_SHIFT;}
[ \t]+      { }
.           { return yytext[0]; }
%%
