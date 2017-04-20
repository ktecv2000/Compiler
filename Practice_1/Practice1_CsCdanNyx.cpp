#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstdio>
using namespace std;

enum Terminal
{
	LPH, RPH, LBR, RBR, LCB, RCB, Dollar
};

void Scanner(void);
void LEXICALERROR(void);

void Parser(void);
void exprs(size_t &i);
void expr(size_t &i);
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
		if (!inp.empty())
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
	cout << "valid" << endl;

	return 0;
}

void Scanner(void)
{
	while (!s.isEOF())
	{
		if (isspace(s.PEEK()))
			s.ADVANCE();
		else
		{
			char ch = s.ADVANCE();
			Token ans;
			switch (ch)
			{
				case '(':
					ans.type = LPH;
					ans.val = ch;
					break;
				case ')':
					ans.type = RPH;
					ans.val = ch;
					break;
				case '[':
					ans.type = LBR;
					ans.val = ch;
					break;
				case ']':
					ans.type = RBR;
					ans.val = ch;
					break;
				case '{':
					ans.type = LCB;
					ans.val = ch;
					break;
				case '}':
					ans.type = RCB;
					ans.val = ch;
					break;
				default:
					LEXICALERROR();
					break;
			}
			ts.push_back(ans);
		}
	}
	Token ans;
	ans.type = Dollar;
	ans.val = "$";
	ts.push_back(ans);
}

void LEXICALERROR(void)
{
	cout << "error" << endl;
	exit(EXIT_SUCCESS);;
}

void Parser()
{
	size_t i = 0;
	exprs(i);
	MATCH(i, Dollar);
	return;
}

void exprs(size_t & i)
{
	if (ts.at(i).type == LPH || ts.at(i).type == LBR || ts.at(i).type == LCB)
	{
		expr(i);
		exprs(i);
	}
	else
	{
		if (ts.at(i).type == RPH || ts.at(i).type == RBR || ts.at(i).type == RCB || ts.at(i).type == Dollar)
			;
		else
			PARSEERROR();
	}
	return;
}

void expr(size_t & i)
{
	if (ts.at(i).type == LPH)
	{
		MATCH(i, LPH);
		exprs(i);
		MATCH(i, RPH);
	}
	else if (ts.at(i).type == LBR)
	{
		MATCH(i, LBR);
		exprs(i);
		MATCH(i, RBR);
	}
	else if (ts.at(i).type == LCB)
	{
		MATCH(i, LCB);
		exprs(i);
		MATCH(i, RCB);
	}
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
	cout << "error" << endl;
	exit(EXIT_SUCCESS);
}

