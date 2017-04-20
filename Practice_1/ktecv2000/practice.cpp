#include <iostream>
#include <string>
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
				if(!stack.empty() || in.size() != index)
					return true;
				return false;
			}
		}
		void ini(string tmp)
		{
			index = 0;
			error = false;
			stack = "";
			in = tmp;
		}
		char peek()
		{
			int i = index;
			while((in[i] == ' ') || (in[i] == '\t') || (in[i] == '\r') || (in[i] == '\n'))
			{
				if(i < in.size())
					i ++;
				else
					is_error(); 
			}
			
			return in[i];
		}
		bool match(char in, char token)
		{
			if(in == token)
			{
				index++;
				return true;
			}
			return false;
		}
		void stack_push(char x)
		{
			stack.push_back(x);
		}
		char stack_top()
		{
			if(!stack.empty())
				return stack[stack.size()-1];
			else
				set_error();
		}
		void stack_pop()
		{
			if(!stack.empty())
				stack.erase(stack.size()-1, 1);
			else
				set_error();
		}
	private:
		string in, stack;	
		int index;
		bool error;
};

Parser parser;

enum Token{
	LPH = '(', RPH = ')', LBR = '[', RBR = ']', LCB = '{', RCB = '}'
};

void program();
void exprs();
void expr();

int main()
{
	string in, tmp;
	while(cin >> tmp)
		in += tmp;
	parser.ini(in);
	program();
	if(parser.is_error())
		cout << "error" << endl;
	else
		cout << "valid" << endl;
    return 0;
}
void program()
{
	exprs();
}
void exprs()
{
	char p = parser.peek();
	if((p == LPH) || (p == LBR) || (p == LCB))
	{
		expr();
		exprs();
	}
	else
		return;	// lambda
}
void expr()
{
	char p = parser.peek();
	if(parser.match(p, LPH))
	{
		parser.stack_push(LPH);
		exprs();
		p = parser.peek();
		if(parser.match(p, RPH)  && parser.stack_top() == LPH)
			parser.stack_pop();
		else
			parser.set_error();
	}
	else if(parser.match(p, LBR))
	{
		parser.stack_push(LBR);
		exprs();
		p = parser.peek();
		if(parser.match(p, RBR)  && parser.stack_top() == LBR)
			parser.stack_pop();
		else
			parser.set_error();
	}
	else if(parser.match(p, LCB))
	{
		parser.stack_push(LCB);
		exprs();
		p = parser.peek();
		if(parser.match(p, RCB)  && parser.stack_top() == LCB)
			parser.stack_pop();
		else
			parser.set_error();
	}
	else
	{
		parser.set_error();
	}
}
