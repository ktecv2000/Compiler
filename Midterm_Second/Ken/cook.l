%{
	int section = 0;
%}
%%
([0-9]+|[0-9]+\/[0-9]+|[0-9]+[ ][0-9]+\/[0-9]+)[ ](cup|tablespoon|teaspoon)s? {
	if(section == 1) {
		printf("%s\n", yytext);
	}
	else if(section == 2) {
		printf("# %s\n", yytext);
	}
}
^Directions$ {
	if(section == 1) section = 2;
}
^Ingredients$ {
	if(section == 0) section = 1;
}
.|\n
%%

int main() {
	yylex();
	return 0;
}
