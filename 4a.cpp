#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;
vector<char> key;
vector<string> prod;
int main()
{
    cout<<"Enter the production";
    string input;
    getline(cin,input);
    key.push_back(input[0]);
    string temp = "";
    for(int i = 1 ; i < input.size();i++)
    {
        if(input[i]=='-'||input[i]=='>'||input[i]==' ')
            continue;
        if(input[i]=='|')
            {
                prod.push_back(temp);
                temp="";
                continue;
            }
        temp+=input[i];
    }
    prod.push_back(temp);
    if(key[0]==prod[1][0])
        swap(prod[0],prod[1]);
    if(key[0]==prod[0][0])
    {
        string pre ="";
        for (int i = 1 ; i < prod[0].size();i++)
            pre+=prod[0][i];
        cout<<prod[0][0]<<"->"<<prod[1]<<prod[0][0]<<'\''<<endl;
        cout<<prod[0][0]<<'\''<<"->"<<pre<<prod[0][0]<<'\''<<"|E";
    }
    else
    {
        cout<<"No Left recursion";
    }
    return 0;
}
