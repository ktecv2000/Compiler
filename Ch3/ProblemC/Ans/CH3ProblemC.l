%{
char * trim(char *str)
{
    char *str_last,*str_cur;
    if(str==NULL)
        return NULL;
    for(;*str==0x20 || *str=='\t'; ++str);
    for(str_last=str_cur=str;*str_cur!='\0';++str_cur)
        if(*str_cur!=0x20&&*str_cur!='\t')
            str_last=str_cur;
    *++str_last=0;
    return str;
}
%}
H	[a-fA-F0-9]
HP	0[xX]
HEX	^" "*{HP}{H}{H}?{H}?{H}?{H}?{H}?{H}?{H}?" "*$
%%
{HEX} {printf("%s\n", trim(yytext));}
.|\n
%%
int main()
{
	yylex();
	return 0;
}