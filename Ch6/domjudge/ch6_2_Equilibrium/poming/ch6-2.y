%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
int alphaKey(char* text, int flag); 
int yydebug = 0;
%}
%union {
int ival;
int list[675];
int ele[2];
}
%left ARROW
%left  ADD 
%token<ival> NUM
%token<ele> ELEMENT

%type<list> mole
%type<list> expr

%%
line		: expr				{
	  								for(char c1 = 'A'; c1 < 'Z'; c1++)
									{
	  									for(char c2 = '\0'; c2 < 'z'; c2++)
										{
											char text[3];
											text[0] = c1;
											text[1] = c2;
											text[2] = '\0';
											int index = alphaKey(text, -1);
											if($1[index])
											{
												printf("%s %d\n", text, $1[index]);
											}
											if(!c2)
												c2 = 'a'-1;
										}
									}
								}
	  		;
expr		: NUM mole			{ 
									for(int i = 0; i < 512; i++)
										$$[i] = $2[i]*$1;
							    }
			| mole				{ 
									for(int i = 0; i < 512; i++)
										$$[i] = $1[i];
							    }
	  		| expr ADD expr		{
								/*
									printf("ADD\n");
									for(int i = 0; i < 5; i++)
										printf("%c %d,%d\n", i+'A', $1[i], $3[i]);
									printf("-------------\n");
								*/
									for(int i = 0; i < 512; i++)
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
									for(int i = 0; i < 512; i++)
										$$[i] = $1[i] - $3[i];
								}
			;

mole	  	: mole '(' mole ')' NUM 
								{
									for(int i = 0; i < 512; i++)
										$$[i] = $1[i] + $3[i]*$5;
								}
			| mole ELEMENT		{
			/*
									char text[4];
									alphaKey(text, $2[0]);
									printf("*ele: %s %d\n", text, $2[1]);
									printf("-------------\n");
			*/				
									$1[ $2[0] ] += $2[1];					
									for(int i = 0; i < 512; i++)
										$$[i] = $1[i];
								}
			|					{
									for(int i = 0; i < 512; i++)
										$$[i] = 0;
								}
			;
%%

void yyerror (const char *message)
{
	printf("Invalid format");
}

int alphaKey(char* text, int flag)
{
	if(flag < 0)  	// text -> index
	{
		if(strlen(text) == 1)
			return text[0] - 'A';
		else
			return (text[0] - 'A' + 1)*26 + (text[1] - 'a');
	}
	else		// index -> text
	{
		if(flag < 26)
		{
			text[0] = 'A' + flag;
		}
		else
		{
			text[1] = 'a' + flag % 26;
			flag /= 26;
			text[0] = 'A' + flag - 1;
		}
		return 0;
	}
}
int main(int argc, char *argv[]) {
        yyparse();
        return(0);
}
