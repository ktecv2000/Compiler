%{
int ind = 0;
char *last;
char *buf;
const int last_size = 10000;
const int buf_size = 100000;
char OK = 1;
%}

%%
\<[a-zA-Z_]+\> {
                    if(strcmp(last,""))
                    {
                        sprintf(buf, "%s\n", buf);
                        if(strcmp(last, yytext))
                            ind += 2;
                    }
                    for(int i = 0; i < ind; i++)
                        sprintf(buf, "%s ", buf);
                    sprintf(buf, "%s%s", buf, yytext);

                    strcpy(last, yytext);
                    last[strlen(yytext)] = 0;

                }
[ \t\n] {}
. {
    if(OK)
	{	
		printf("please don't eat me");
		OK = 0;  
	}
  }
%%
int main()
{
    buf = (char*)malloc(buf_size*sizeof(char));
	last = (char*)malloc(last_size*sizeof(char));
    memset(last, 0, last_size);
    memset(buf, 0, buf_size);
    yylex();
    if(OK)
        printf("%s", buf);
    return 0;
}
