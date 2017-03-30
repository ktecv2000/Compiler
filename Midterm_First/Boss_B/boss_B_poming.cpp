#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

class Parser
{
	public:
		void set_error()
		{
			error = true;
		}
		bool is_error()
		{
			//cout << "stack:\n" << stack << "\nindex = " << index << endl; ///
			if(error)
				return error;
			else
			{
			    peek();
				if(in.size() != index)
					return true;
				return false;
			}
		}
		void ini(string tmp)
		{
			index = 0;
			error = false;
			in = tmp;
			out = "";
		}
		void print_out()
		{
		    if(is_error())
                cout << "invalid input" << endl;
            else
                cout << out;
		}
		char peek()
		{

			while((in[index] == ' ') || (in[index] == '\t') || (in[index] == '\r') || (in[index] == '\n'))
			{
				if(index < in.size())
					index ++;
				else
                    set_error();
			}

            return in[index];
		}
		bool match(string token)
		{
		    int i = index;
		    char p;
		    if(token == "ID")
            {
                p = peek();
                if(isalpha(p) || p == '_')
                {
                    int base = index;
                    index++;
                    p = peek();
                    while(isalnum(p) || p == '_')
                    {
                        index++;
                        p = peek();
                    }

                    out += "ID " + in.substr(base, index - base) + "\n";
                    return true;
                }
            }
            else if(token == "STRLIT")
            {
                p = peek();
                if(p == '\"')
                {
                    int base = index;
                    index ++;
                    p = peek();
                    while(p != '\"')
                    {
                        index++;
                        p = peek();
                    }
                    index++;
                    if(index < in.size())
                    {
                        out += "STRLIT " + in.substr(base, index - base) + "\n";
                        return true;
                    }
                }
            }
            else if(token == "LBR")
            {
                p = peek();
                if(p == '[')
                {
                    index++;
                    out += "LBR [\n";
                    return true;
                }
            }
            else if(token == "RBR")
            {
                p = peek();
                if(p == ']')
                {
                    index++;
                    out += "RBR ]\n";
                    return true;
                }
            }
            else if(token == "DOT")
            {
                p = peek();
                if(p == '.')
                {
                    index++;
                    out += "DOT .\n";
                    return true;
                }
            }
            else if(token == "SEMICOLON")
            {
                p = peek();
                if(p == ';')
                {
                    index++;
                    out += "SEMICOLON ;\n";
                    return true;
                }
            }

            index = i;
            return false;
		}

	private:
		string in, out;
		int index;
		bool error;
};

Parser parser;

/*
enum Token{
	leftParen = '(', rightParen = ')', LBR = '[', RBR = ']', LCB = '{', RCB = '}'
};
*/

void program();
void stmts();
void stmt();
void exp();
void primary();
void primary_tail();

int main()
{

	string in, tmp;
	while(cin >> tmp)
		in += tmp + " ";

	parser.ini(in);

    program();
	parser.print_out();

    return 0;
}
void program()
{
	stmts();
}
void stmts()
{
    char p = parser.peek();
    if(p == '\"' || (isalpha(p) || p == '_'))
    {
        stmt();
        stmts();
    }
    else
        return;
}
void stmt()
{
    exp();

    if(parser.match("SEMICOLON"))
    {
        return;
    }
    parser.set_error();
}
void exp()
{

    char p = parser.peek();
    if(isalpha(p) || p == '_')
    {
        primary();
        return;
    }
    else if(parser.match("STRLIT"))
    {
        return;
    }
    parser.set_error();
}
void primary()
{

    if(parser.match("ID"))
    {
        primary_tail();
        return;
    }
    parser.set_error();
}
void primary_tail()
{

    char p = parser.peek();
    if(p == '.')
    {
        if(parser.match("DOT"))
        {
            if(parser.match("ID"))
            {
                primary_tail();
                return;
            }
        }
    }
    else if(p == '[')
    {
        if(parser.match("LBR"))
        {
            exp();
            if(parser.match("RBR"))
            {
                primary_tail();
                return;
            }
        }
    }
    else
        return;
}
