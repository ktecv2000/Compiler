#include <iostream>
#include <cctype>
#include <string>
#include <unistd.h>

using namespace std;

string out = "";
istream & in = cin;
bool f = true;

bool exp();

bool ID()
{
    //cout << "ID" << endl;
    char c;
    string s = "";
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(isalpha(c) || c == '_')
    {
        in.get();
        s += c;
    }
    else
    {
        return false;
    }
    while(isalnum(c = in.peek()) || c == '_')
    {
        in.get();
        s += c;
    }
    out += "ID " + s + "\n";
    return true;
}

bool STRLIT()
{
    //cout << "STRLIT" << endl;
    char c;
    string s = "";
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(c == '"')
    {
        in.get();
        while((c = in.peek()) != '"')
        {
            in.get();
            s += c;
        }
        if(c == '"')
        {
            in.get();
            out += "STRLIT \"" + s + "\"\n";
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

bool LBR()
{
    //cout << "LBR" << endl;
    char c;
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(c == '[')
    {
        out += "LBR [\n";
        in.get();
        return true;
    }
    return false;
}

bool RBR()
{
    //cout << "RBR" << endl;
    char c;
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(c == ']')
    {
        out += "RBR ]\n";
        in.get();
        return true;
    }
    return false;
}

bool DOT()
{
    //cout << "DOT" << endl;
    char c;
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(c == '.')
    {
        out += "DOT .\n";
        in.get();
        return true;
    }
    return false;
}

bool SEMICOLON()
{
    //cout << "SEMICOLON" << endl;
    char c;
    while((c = in.peek()) == ' ' || c == '\t' || c == '\n')
        in.get();
    if(c == ';')
    {
        out += "SEMICOLON ;\n";
        in.get();
        return true;
    }
    return false;
}

bool primary_tail()
{
    //cout << "primary_tail" << endl;
    if(DOT())
    {
        return ID() && primary_tail();
    }
    else if(LBR())
    {
        return exp() && RBR() && primary_tail();
    }
    return true;
}

bool primary()
{
    //cout << "primary" << endl;
    return ID() && primary_tail();
}

bool exp()
{
    //cout << "exp" << endl;
    return STRLIT() || primary();
}

bool stmt()
{
    //cout << "stmt" << endl;
    return exp() && SEMICOLON();
}

bool stmts()
{
    //cout << "stmts" << endl;
    return (stmt() && stmts()) || true;
}

bool program()
{
    //cout << "program" << endl;
    return stmts();
}

int main()
{
    string s;
        if(program() && cin.eof())
    {
        cout << out;
    }
    else
    {
        cout << "invalid input" << endl;
    }
        return 0;
}
