#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
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
                //cout<<temp<<endl;
                temp="";
                continue;
            }
        temp+=input[i];
    }
    prod.push_back(temp);
    
    int counter = min(prod[0].size(),prod[1].size());
    string prefix = "";
    int i = 0;
    while(i < counter)
    {
        if(prod[0][i]==prod[1][i])
            prefix+=prod[0][i];
        else
            break;
        i++;
    }
    //cout<<prefix<<endl;
    if(prefix!="")
        {
            string nc0 = "";
            for(int j =i;  j < prod[0].size();j++)
            {
                nc0+=prod[0][j];
            }
            string nc1 = "";
            for(int j =i;  j < prod[1].size();j++)
            {
                nc1+=prod[1][j];
            }
           
            cout<<key[0]<<"->"<<prefix<<key[0]<<"'|";
            if(prod.size()>2)cout<<prod[2]<<endl;
            cout<<key[0]<<"'->";
            if(nc0!="")
                cout<<nc0<<"|";
            if(nc1!="")
                cout<<nc1<<"|";
            cout<<"Ebs";
        }
    else cout<<"No need for left factoring";
}
