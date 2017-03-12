%{
#define YY_MAIN 1
#define yywrap() 1
%}
H	[a-fA-F0-9]
HP	0[xX]
HEX	^" "*{HP}{H}+" "*$
%%
{HEX} {
	ECHO;printf("\n");
}
.|\n
%%
