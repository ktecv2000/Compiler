%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
int tmp[26];
int yydebug = 0;
%}
%union {
int ival;
int ele[2];
int list[26];
}
%left ARROW
%left  ADD 
%token<ival> NUM
%token<ele> ELEMENT

%type<list> mole
%type<list> expr

%%
line		: expr				{
									for(int i = 0; i < 5; i++)
									{
										if($1[i])
											printf("%c %d\n", i+'A', $1[i]);
									}
								}
	  		;
expr		: NUM mole			{ 
									for(int i = 0; i < 26; i++)
										$$[i] = $2[i]*$1;
							    }
			| mole				{ 
									for(int i = 0; i < 26; i++)
										$$[i] = $1[i];
							    }
	  		| expr ADD expr		{
								/*
									printf("ADD\n");
									for(int i = 0; i < 5; i++)
										printf("%c %d,%d\n", i+'A', $1[i], $3[i]);
									printf("-------------\n");
								*/
									for(int i = 0; i < 26; i++)
										$$[i] = $1[i] + $3[i];
								}
			| expr ARROW expr
	  							{
								/*
									printf("ARROW\n");
									for(int i = 0; i < 5; i++)
										printf("%c %d,%d\n", i+'A', $1[i], $3[i]);
									printf("-------------\n");
								*/
									for(int i = 0; i < 26; i++)
										$$[i] = $1[i] - $3[i];
								}
			;

mole	  	: mole '(' mole ')' NUM 
								{
									for(int i = 0; i < 26; i++)
										$$[i] = $1[i] + $3[i]*$5;
								}
			| mole ELEMENT		{
							/*
									printf("-> ele:%c %d\n", $2[0]+'A', $2[1]);
									for(int i = 0; i < 5; i++)
										printf("%c %d\n", i+'A', $1[i]);
									printf("-------------\n");
							*/
									$1[ $2[0] ] += $2[1];					
									for(int i = 0; i < 26; i++)
										$$[i] = $1[i];
								}
			|					{
									for(int i = 0; i < 26; i++)
										$$[i] = 0;
								}
			;
%%

void yyerror (const char *message)
{
	printf("Invalid format");
}

int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}
