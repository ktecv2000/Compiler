#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <regex>
#include <cstdlib>
#include <cstdio>
using namespace std;

enum Terminal
{
	num, fnName, leftParen, rightParen, Dollar
};

void Scanner(void);
void SCANDIGITS(void);
void SCANFUNC(void);
void LEXICALERROR(void);

void Parser(void);
void Stmt(size_t &i);
void Func(size_t &i);
void Args(size_t &i);
void Arg(size_t &i);
void MATCH(size_t & i, Terminal);
void PARSEERROR(void);

class ProgramStream
{
public:
	// constructor
	ProgramStream(unsigned int iter = 0, string str = "")
	{};

	void ADD(string inp)
	{
		if(!inp.empty())
			str += inp + "\n";
	}

	char PEEK()
	{
		if (iter >= str.length())
			return EOF;
		else
		{
			return str.at(iter);
		}
	}

	char ADVANCE()
	{
		if (iter >= str.length())
			return EOF;
		else
		{
			return str.at(iter++);
		}
	}

	bool isEOF()
	{
		return iter >= str.length();
	}

	void Getstr()
	{
		cout << "Program_stream ==> \"" << endl;
		cout << str << endl;
		cout << "\" End" << endl;
	}

	int Getlen()
	{
		return str.length();
	}

private:
	unsigned int iter;
	string str;
};

class Token
{
public:
	Token()
	{};

	Terminal type;
	string val = "";

	string Gettype()
	{
		string t;
		switch (Token::type)
		{
		case num:
			t = "num";
			break;
        case fnName:
			t = "fnName";
			break;
        case leftParen:
			t = "leftParen";
			break;
        case rightParen:
			t = "rightParen";
			break;
		case Dollar:
			t = "$";
			break;
		default:
			t = "ERR!";
			break;
		}
		return t;
	}
};

ProgramStream s;
vector<Token> ts;

int main()
{
	//Program Input
	string inp;

	while (getline(cin, inp))
		s.ADD(inp);

	Scanner();
	Parser();

	for (auto it = ts.begin(); it < ts.end()-1; it++)
		cout << (*it).Gettype() << " " << (*it).val << endl;

	return 0;
}

void Scanner(void)
{
	while ( !s.isEOF() )
	{
		if (isspace(s.PEEK()))
			s.ADVANCE();
		else
		{
			if (isdigit(s.PEEK()))
				SCANDIGITS();
            else if ( isalpha(s.PEEK()) )
                SCANFUNC();
			else
			{
				char ch = s.ADVANCE();
				Token ans;
				switch (ch)
				{
					case '(':
						ans.type = leftParen;
						ans.val = ch;
						break;
					case ')':
						ans.type = rightParen;
						ans.val = ch;
						break;
					default:
						LEXICALERROR();
						break;
				}
				ts.push_back(ans);
			}

		}
	}
	Token ans;
	ans.type = Dollar;
	ans.val = "$";
	ts.push_back(ans);
}

void SCANDIGITS(void)
{
	Token tok;
	while (isdigit(s.PEEK()))
		tok.val += s.ADVANCE();

	tok.type = num;
	ts.push_back(tok);
	return;
}

void SCANFUNC(void)
{
	Token tok;
	while (isalpha(s.PEEK()))
		tok.val += s.ADVANCE();
    if ( isdigit(s.PEEK()) )
        LEXICALERROR();
    else
    {
       tok.type = fnName;
        ts.push_back(tok);
    }
	return;
}

void LEXICALERROR(void)
{
	cout << "Invalid input" << endl;
	exit(EXIT_SUCCESS);
}

void Parser()
{
	size_t i = 0;
	Stmt(i);
	MATCH(i, Dollar);
	return;
}

void Stmt(size_t & i)
{
	Func(i);
	return;
}

void Func(size_t & i)
{
    MATCH(i, leftParen);
    MATCH(i, fnName);
    Args(i);
	MATCH(i, rightParen);
	return;
}

void Args(size_t & i)
{
    if (ts.at(i).type == num || ts.at(i).type == leftParen)
    {
        Arg(i);
        Args(i);
    }
    else
    {
        if (ts.at(i).type == rightParen)
            ;
        else
            PARSEERROR();
    }
	return;
}

void Arg(size_t & i)
{
    if (ts.at(i).type == num)
        MATCH(i, num);
	else if (ts.at(i).type == leftParen)
        Func(i);
    else
        PARSEERROR();
	return;
}

void MATCH(size_t & i, Terminal tm)
{
	if (ts.at(i).type == tm)
		i++;
	else
		PARSEERROR();
	return;
}


void PARSEERROR(void)
{
	cout << "Invalid input" << endl;
	exit(EXIT_SUCCESS);
}

