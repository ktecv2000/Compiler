%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(const char *message);
int alphaKey(char* text, int flag); 
int yydebug = 0;
#define range 26*27
%}
%union {
int ival;
int list[range];
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
	  								for(int c1 = 'A'; c1 <= 'Z'; c1++)
									{
	  									for(int c2 = '\0'; c2 <= 'z'; c2++)
										{
											char text[3];
											text[0] = c1;
											text[1] = c2;
											text[2] = '\0';
											int index = alphaKey(text, -1);
											//printf("==%s %d\n", text, index);
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
									for(int i = 0; i < range; i++)
										$$[i] = $2[i]*$1;
							    }
			| mole				{ 
									for(int i = 0; i < range; i++)
										$$[i] = $1[i];
							    }
	  		| expr ADD expr		{
									for(int i = 0; i < range; i++)
										$$[i] = $1[i] + $3[i];
								}
			| expr ARROW expr
	  							{
									for(int i = 0; i < range; i++)
										$$[i] = $1[i] - $3[i];
								}
			;

mole	  	: mole '(' mole ')' NUM 
								{
									for(int i = 0; i < range; i++)
										$$[i] = $1[i] + $3[i]*$5;
								}
			| mole ELEMENT		{
									$1[ $2[0] ] += $2[1];					
									for(int i = 0; i < range; i++)
										$$[i] = $1[i];
								}
			|					{
									for(int i = 0; i < range; i++)
										$$[i] = 0;
								}
			;
%%

void yyerror (const char *message)
{
	printf("Invalid format\n");
}

int alphaKey(char* text, int flag)
{
	if(flag < 0)  	// text -> index
	{
		if(strlen(text) == 1)
		{
			return text[0] - 'A';
		}
		else
		{
			return (text[0] - 'A' + 1)*26 + (text[1] - 'a');
		}
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
