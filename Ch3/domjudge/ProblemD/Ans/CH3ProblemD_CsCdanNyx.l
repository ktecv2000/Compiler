
dig    0|[1-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]

%%

({dig}\.){3}{dig}  {    ECHO;puts("");  }

.|\n

%%

int main()
{   
    yylex();
    
    return 0;
}