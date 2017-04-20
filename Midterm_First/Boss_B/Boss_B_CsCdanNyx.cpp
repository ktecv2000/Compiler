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
	ID, STRLIT, LBR, RBR, DOT, SEMICOLON, Dollar
};

void Scanner(void);
void SCANSTRING(void);
void SCANID(void);
void LEXICALERROR(void);

void Parser(void);
void stmts(size_t &i);
void stmt(size_t &i);
void exp(size_t &i);
void primary(size_t &i);
void primary_tail(size_t &i);
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
			str += inp + " ";
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
		case ID:
			t = "ID";
			break;
        case STRLIT:
			t = "STRLIT";
			break;
        case LBR:
			t = "LBR";
			break;
        case RBR:
			t = "RBR";
			break;
        case DOT:
			t = "DOT";
			break;
        case SEMICOLON:
			t = "SEMICOLON";
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
			if (s.PEEK() == '\"')
				SCANSTRING();
            else if ( isalpha(s.PEEK()) || s.PEEK() == '_' )
                SCANID();
			else
			{
				char ch = s.ADVANCE();
				Token ans;
				switch (ch)
				{
					case '[':
						ans.type = LBR;
						ans.val = ch;
						break;
					case ']':
						ans.type = RBR;
						ans.val = ch;
						break;
                    case '.':
						ans.type = DOT;
						ans.val = ch;
						break;
                    case ';':
						ans.type = SEMICOLON;
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

void SCANSTRING(void)
{
	if(s.PEEK()=='\"')
	{
		Token tok;
		tok.val += s.ADVANCE();
		while ((s.PEEK() != '\"') && (!s.isEOF()))
			tok.val += s.ADVANCE();

		if (s.PEEK() == '\"')
		{
			tok.val += s.ADVANCE();
			tok.type = STRLIT;
			ts.push_back(tok);
		}
	}
	return;
}

void SCANID(void)
{
	if ( isalpha(s.PEEK()) || s.PEEK() == '_' )
	{
		Token tok;
		tok.val += s.ADVANCE();
		while ((isalnum(s.PEEK()) || s.PEEK() == '_') && (!s.isEOF()))
			tok.val += s.ADVANCE();

		tok.type = ID;
		ts.push_back(tok);
    }
	return;
}

void LEXICALERROR(void)
{
	cout << "invalid input" << endl;
	exit(EXIT_SUCCESS);
}

void Parser()
{
	size_t i = 0;
	stmts(i);
	MATCH(i, Dollar);
	return;
}

void stmts(size_t & i)
{
	if (ts.at(i).type == ID || ts.at(i).type == STRLIT )
	{
		stmt(i);
		stmts(i);
	}
	else
	{
		if (ts.at(i).type == Dollar)
			;
		else
			PARSEERROR();
	}
	return;
}

void stmt(size_t & i)
{
	exp(i);
	MATCH(i, SEMICOLON);
	return;
}

void exp(size_t & i)
{
    if (ts.at(i).type == STRLIT)
        MATCH(i, STRLIT);
    else if (ts.at(i).type == ID)
        primary(i);
    else
        PARSEERROR();
	return;
}

void primary(size_t & i)
{
    MATCH(i, ID);
	primary_tail(i);
	return;
}

void primary_tail(size_t & i)
{
	if (ts.at(i).type == DOT )
	{
	    MATCH(i, DOT);
		MATCH(i, ID);
		primary_tail(i);
	}
	else if ( ts.at(i).type == LBR )
	{
	    MATCH(i, LBR);
	    exp(i);
		MATCH(i, RBR);
		primary_tail(i);
	}
	else
	{
		if (ts.at(i).type == SEMICOLON || ts.at(i).type == RBR )
			;
		else
			PARSEERROR();
	}
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
	cout << "invalid input" << endl;
	exit(EXIT_SUCCESS);
}

