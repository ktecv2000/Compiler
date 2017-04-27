%{
char last[10000] = {0};
int indent = 0;
char buff[100000] = {0};
char in = 0;
char success = 1;
char calledIn = 0;
%}
%%
"<" {
	if(in == 0) in = 1;
	else success = 0;
	calledIn = 0;
}
[a-zA-Z_]+ {
	if(in && calledIn == 0) {
		calledIn = 1;
		int i;
		if(*last != 0 && strcmp(last, yytext) != 0) {
			indent += 2;
		}
		strcpy(last, yytext);
		for(i = 0; i < indent; i++) {
			strcat(buff, " ");
		}
		strcat(buff, "<");
		strcat(buff, yytext);
		strcat(buff, ">\n");
	}
	else {
		success = 0;
	}
}
[^\<\>]+ {
	if(in && calledIn == 0) {
		success = 0;
	}
}
">" {
	if(calledIn == 1 && in == 1) {
		calledIn = in = 0;
	}
	else {
		success = 0;
	}
}

%%

int main() {
	yylex();
	if(success) {
		int len = strlen(buff);
		if(buff[len - 1] == '\n') {
			buff[len - 1] = 0;
		}
		printf("%s", buff);
	}
	else {
		printf("please don't eat me");
	}
	return 0;
}
