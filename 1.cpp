#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> s = {"auto", "break", "case", "char", "const", "continue", "default",
                    "do", "double", "else", "enum", "extern", "float", "for", "goto",
                    "if", "int", "long", "register", "return", "short", "signed",
                    "sizeof", "static", "struct", "switch", "typedef", "union",
                    "unsigned", "void", "volatile", "while"};

unordered_map<string, bool> key;
unordered_map<string, bool> opt;
unordered_map<string, bool> symb;

bool iskeyword(string str)
{
    if (key.find(str) != key.end())
        return true;
    return false;
}
bool isoperator(string str)
{
    if (opt.find(str) != opt.end())
        return true;
    return false;
}
bool issymbol(string str)
{
    if (symb.find(str) != symb.end())
        return true;
    return false;
}
bool isconstant(string str)
{
    for (auto x : str)
    {
        if (x == '.' || isdigit(x))
            continue;
        else
            return false;
    }
    return true;
}
bool isliteral(string str)
{
    if (str[0] == '"' && str[str.size() - 1] == '"')
        return true;
    else
        return false;
}
bool isidentifier(string str)
{
    if (str[0] == '_' || isalpha(str[0]))
    {
        for (int i = 1; i < str.size(); i++)
        {
            if (iswalnum(str[i]))
                continue;
            return false;
        }
        return true;
    }
    return false;
}
int main()
{
    for (auto x : s)
    {
        key[x] = true;
    }

    opt["<="] = true;
    opt[">="] = true;
    opt["!="] = true;
    opt["+"] = true;
    opt["-"] = true;
    opt["*"] = true;
    opt["/"] = true;
    opt["%"] = true;
    opt["="] = true;
    opt["<"] = true;
    opt[">"] = true;
    
    symb[","] = true;
    symb[";"] = true;
    symb[":"] = true;
    symb["("] = true;
    symb[")"] = true;
    symb["{"] = true;
    symb["}"] = true;
    symb["["] = true;
    symb["]"] = true;
    symb["~"] = true;

    vector<string> keywords, constants, operators, identifiers, literal, symbols;
    string input;
    cout <<"Enter input string"<<endl;
    getline(cin, input);
    vector<string> inp;
    string temp = "";
    for (auto a : input)
    {
        if (a == ' ')
        {
            if (temp[0] != '#')
                inp.push_back(temp);
            temp = "";
            continue;
        }
        temp += a;
    }
    for (auto a : inp)
    {
        if (iskeyword(a))
        {
            keywords.push_back(a);
        }
        else if (isconstant(a))
        {
            constants.push_back(a);
        }
        else if (isoperator(a))
        {
            operators.push_back(a);
        }
        else if (isidentifier(a))
        {
            identifiers.push_back(a);
        }
        else if (isliteral(a))
        {
            literal.push_back(a);
        }
        else if (issymbol(a))
        {
            symbols.push_back(a);
        }
    }
    cout<<"Keywords:"<<endl;
    for (auto a : keywords)
        cout<<a<<" ";
    cout<<endl;
    cout<<"Identifiers:"<<endl;
    for (auto a : identifiers)
        cout << a << " ";
    cout<<endl;
    cout<<"Constants:"<<endl;
    for (auto a : constants)
        cout << a << " ";
    cout<<endl;
    cout<<"Operators:"<<endl;
    for (auto a : operators)
        cout << a << " ";
    cout<<endl;
    cout<<"Literals:"<<endl;
    for (auto a : literal)
        cout << a << " ";
    cout<<endl;
    cout<<"Symbols:"<<endl;
    for (auto a : symbols)
        cout<<a<<" ";
    cout<<endl;

    return 0;
}
