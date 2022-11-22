#include <bits/stdc++.h>
using namespace std;


string prntstr(string &input, int in){
    string ans;
    for(; in<input.size(); in++){
        ans.push_back(input[in]);
    }
    return ans;
}

void prntstk(stack<int> sk){
    vector<int> ans;
    while(!sk.empty()) {
        ans.push_back(sk.top());
        sk.pop();
    }
    reverse(ans.begin(), ans.end());
    for(auto i:ans) cout<<i; cout<<"\n";
}

void outstk(string sk, stack<int> StateSk){
    string ans;
    vector<int> intTemp;
    int N = sk.size()+StateSk.size();
    while(!StateSk.empty()){
        intTemp.push_back(StateSk.top());
        StateSk.pop();
    }
    reverse(intTemp.begin(), intTemp.end());

    for(int i=0; i<sk.size(); i++){
        ans+=to_string(intTemp[i])+sk[i+1];
    }
    cout<<setw(25)<<ans;
}

int strInt(string c, int s=0){
    string S; for(int i=s; i<c.size(); i++) S.push_back(c[i]);
    stringstream ss(S);
    int ans; ss>>ans;
    return ans;
}


int main()
{

    map<int, string> Prods;
    Prods[1]="S->ABC";
    Prods[2]="A->abA";
    Prods[3]="A->ab";
    Prods[4]="B->b";
    Prods[5]="B->BC";
    Prods[6]="C->c";
    Prods[7]="C->cC";

    map<char,int> idx; 
    int Col=9, Row=12;
    vector<vector<string>> PTable(Row+1, vector<string>(Col+1));

    fstream inputFile("./ParseTable.txt");
    string sym; int state; 
    for(int r=0; r<Row; r++){
        for(int c=0; c<Col; c++){
            inputFile>>sym;
            if(r==0) idx[sym[0]]=c;
            else{
                if(c==0) state = strInt(sym);
                else PTable[state][c]=sym;
            }
        }
    }


    cout<<" **** Shift Reduce Parser **** \n";
    cout<<"GIVEN GRAMMER :"<<'\n';
    for(auto prodi : Prods) cout<<prodi.second<<'\n';

    cout<<"Enter the Input string with $ at the end: \n";
    string input; 
    input = "aaaa$";
    
    for(int i=1; i<70; i++) cout<<'-'; cout<<'\n';

    cout<<"\n\n\tStack\t|\tInput Buffer\t|\tAction\n";
    cout<<"     -------\t\t--------------\t-------\n";


    string sk;
    stack<int> stkstate;
    stkstate.push(0);
    sk.push_back('$');
    state = 0;
    char ch = input[0];

    for(int cur=0; cur<input.size(); ){

        outstk(sk, stkstate);
        cout<<setw(25)<<left<<prntstr(input, cur); 


        state = stkstate.top();
        string S = PTable[state][idx[ch]];
        
       // reject
        if(S[0]=='-'){
            cout<<"REJECT\n";
            break;
        }
        // accept 
        else if(S[0]=='A'){ 
            cout<<"ACCEPT\n";
            break;
        }
        // reduce
        else if(S[0]=='r'){
            int prod_idx = strInt(S,1);
            string prod = Prods[prod_idx];
            cout<<("Reducing: "+prod)<<'\n';
            for(int i=0; i<prod.size()-3; i++){
                sk.pop_back();
                stkstate.pop();
            }
            
            ch = prod[0];
            sk.push_back(ch);
            string nxt = PTable[stkstate.top()][idx[ch]];

            stkstate.push(strInt(nxt));
            ch = input[cur];

        }

        else{
           cout<<"Shifting: "+to_string(state)<<'\n';
           sk.push_back(ch); 
           ch = input[++cur];
           stkstate.push(strInt(S));
        }
    }

    return 0;
}
