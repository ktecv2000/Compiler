%{
#include "ch6-2.tab.h"
#include <ctype.h>
%}


%%
\n			{ 	return(0); /* EOF */ }
[ \t]+		{ 	/* do nothing */ }
[0-9]+		{ 	yylval.ival = atoi(yytext); return NUM; }
[A-Z][a-z]*([0-9]+)? {
				int i = 0;
				while(isalpha(yytext[i]))
					i++;
				if(i != strlen(yytext))   // optional element number
					yylval.ele[1] = atoi(yytext+i);
				else
					yylval.ele[1] = 1;
				yytext[i] = '\0';
				yylval.ele[0] = alphaKey(yytext, -1);
				return ELEMENT;
			}
\+  { 	return ADD;	}
->	{ 	return ARROW; }	
.	{ 	return(yytext[0]); }
%%
