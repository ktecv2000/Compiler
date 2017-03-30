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
                cout << "Invalid input" << endl;
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
		    if(token == "leftParen")
            {
                if(peek() == '(')
                {
                    index ++;
                    out += "leftParen (\n";
                    return true;
                }
            }
            else if(token == "rightParen")
            {
                if(peek() == ')')
                {
                    index ++;
                    out += "rightParen )\n";
                    return true;
                }
            }
            else if(token == "fnName")
            {
                if(isalpha(peek()))
                {
                    int base = index;
                    while(isalpha(in[index]))
                        index++;

                    if(in[index] == ' ' || in[index] == '(' || in[index] == ')')
                    {
                        out += "fnName " + in.substr(base, index - base) + "\n";
                        return true;
                    }
                }
            }
            else if(token == "num")
            {
                if(isdigit(peek()))
                {
                    int base = index;
                    while(isdigit(in[index]))
                    {
                        index++;
                    }
                    //if(in[index] == ' ' || in[index] == '(' || in[index] == ')')
                    {
                        out += "num " + in.substr(base, index - base) + "\n";
                        return true;
                    }
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

void Prog();
void Stmts();
void Func();
void Args();
void Arg();

int main()
{
	string in, tmp;
	while(cin >> tmp)
		in += tmp + " ";
	parser.ini(in);
    Prog();
	parser.print_out();
    return 0;
}
void Prog()
{
	Stmts();
}
void Stmts()
{
    Func();
}
void Func()
{
    if(parser.match("leftParen"))
    {
        if(parser.match("fnName"))
        {
            Args();
            if(parser.match("rightParen"))
            {
                return;
            }
        }
    }
    parser.set_error();
}
void Args()
{
    char p = parser.peek();
    if(isdigit(p) || p == '(')
    {
        Arg();
        Args();
        return;
    }
    else
        return; // lambda
}

void Arg()
{
    char p = parser.peek();
    if(isdigit(p))
    {
        parser.match("num");
        return;
    }
    else if(p == '(')
    {
        Func();
        return;
    }
    parser.set_error();
}
