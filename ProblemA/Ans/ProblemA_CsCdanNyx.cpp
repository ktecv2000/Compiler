//#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <regex>
#include <stdio.h>
using namespace std;

enum Terminal
{
	id, assign, inum, Dollar
};

void Scanner(void);
void SCANDIGITS(void);
void LEXICALERROR(void);

void Parser(void);
void Stmt(size_t & i);
void Val(size_t & i);
void MATCH(size_t & i, Terminal);
void PARSEERROR(void);

class ProgramStream
{
public:
	// constructor
	ProgramStream(unsigned int iter = 0, std::string str = "")
	{};

	void ADD(std::string inp)
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
	std::string str;
};

class Token
{
public:
	Token()
	{};

	Terminal type;
	std::string val = "";

	std::string Gettype()
	{
		std::string t;
		switch (Token::type)
		{
			case id:
				t = "id";
				break;
			case inum:
				t = "inum";
				break;
			case assign:
				t = "assign";
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
	std::string inp;

	cout << "Your Program : \"" << endl;
	while (getline(cin, inp))
		s.ADD(inp);
	cout << endl;
	s.Getstr();
	cout << "Len: " << s.Getlen() << endl;
	cout << endl;

	Scanner();

	cout << "Token stream after Scanner(ts) = \"" << endl;
	for (auto &i : ts)
		cout << i.Gettype() << "\t" << i.val << endl;
	cout << "\"" << endl;
	cout << endl;

	Parser();

	cout << "Final Result: => " << endl;
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
			else
			{
				char ch = s.ADVANCE();
				Token ans;
				switch (ch)
				{
					case '=':
						ans.type = assign;
						ans.val = ch;
						break;
					default:
						if (islower(ch))
						{
							ans.type = id;
							ans.val = ch;
						}
						else
						{
							LEXICALERROR();
						}
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
	{
		tok.val += s.ADVANCE();
	}
	tok.type = inum;
	ts.push_back(tok);
	return;
}

void LEXICALERROR(void)
{
	cout << "LEXICAL ERR!!!" << endl;
	cout << "valid input" << endl;
	cout << endl;
	exit(EXIT_SUCCESS);
}

void Parser(void)
{
	size_t i = 0;
	Stmt(i);
	MATCH(i, Dollar);
}

void Stmt(size_t & i)
{
	if (ts.at(i).type == id)
	{
		MATCH(i, id);
		MATCH(i, assign);
		Val(i);
	}
	else
		PARSEERROR();
	return;
}

void Val(size_t & i)
{
	if (ts.at(i).type == id)
		MATCH(i, id);
	else if (ts.at(i).type == inum)
		MATCH(i, inum);
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
	cout << "PARSE ERR!!!" << endl;
	cout << "valid input" << endl;
	cout << endl;
	exit(EXIT_SUCCESS);
}

