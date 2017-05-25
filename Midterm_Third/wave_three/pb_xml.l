%{
#include "pb_xml.tab.h"
int dep = 0;
%}
%%
\<and\>     {
                yylval.d[0] = dep;
                return L_AND;
            }
\<\/and\>   {
                yylval.d[0] = dep;
                return R_AND;
            }
\<or\>      {
                yylval.d[0] = dep;
                return L_OR;
            }
\<\/or\>    {
                yylval.d[0] = dep;
                return R_OR;
            }
\<not\>     {
                yylval.d[0] = dep;
                return L_NOT;
            }
\<\/not\>   {
                yylval.d[0] = dep;
                return R_NOT;
            }
\<true\/>   {
                yylval.d[0] = dep;
                return T;
            }
\<false\/>  {
                yylval.d[0] = dep;
                return F;
            }
\n          {
                dep = 0;
            }
[ \t]+      { dep += strlen(yytext); }
.           { return yytext[0]; }

%%
