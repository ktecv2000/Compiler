%{
char addHash = 0;
%}
D [0-9]
F {D}\/{D}

%%
({D}|{F}|{D}\ {F})\ (cup|tablespoon|teaspoon)s? {
                if(addHash)
                    printf("# ");
                printf("%s\n", yytext);
                }
Directions { addHash = 1; }
\n {}
. {}
%%
int main()
{
    yylex();
    return 0;
}
