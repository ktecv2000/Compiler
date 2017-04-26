%{
char * trim(char *str)
{
    char *str_last,*str_cur;
    if(str==NULL)
        return NULL;
    for(;*str==0x20 || *str=='\n' || *str=='\t'; ++str);
    for(str_last=str_cur=str;*str_cur!='\0';++str_cur)
        if(*str_cur!=0x20&&*str_cur!='\t')
            str_last=str_cur;
    *++str_last=0;
    return str;
}
%}
IP_PART 25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9][0-9]|[0-9]
IP {IP_PART}"."{IP_PART}"."{IP_PART}"."{IP_PART}
%%
{IP} {printf("%s\n", trim(yytext));}
.|\n
%%

int main()
{
	yylex();
	return 0;
}
