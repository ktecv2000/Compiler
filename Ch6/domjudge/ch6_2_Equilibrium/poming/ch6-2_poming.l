%{
#include "ch6-2_poming.tab.h"
#include <ctype.h>
%}


%%
\n			{ 	return(0); /* EOF */ }
[ \t]+		{ 	/* do nothing */ }
[0-9]+		{ 	yylval.ival = atoi(yytext); return NUM; }
[A-Z]([0-9]+)? {
				yylval.ele[0] = yytext[0]-'A';
				if(strlen(yytext) == 1)
					yylval.ele[1] = 1;
				else
					yylval.ele[1] = atoi(yytext+1);
				return ELEMENT;
			}
\+  { 	return ADD;	}
->	{ 	return ARROW; }	
.	{ 	return(yytext[0]); }
%%
