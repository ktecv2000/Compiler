%{
#define YY_MAIN 1
#define yywrap() 1	
%}
IP_PART 25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9]
%%

^{IP_PART}"."{IP_PART}"."{IP_PART}"."{IP_PART}" " {
	ECHO;printf("\n");
}
.|\n
%%
