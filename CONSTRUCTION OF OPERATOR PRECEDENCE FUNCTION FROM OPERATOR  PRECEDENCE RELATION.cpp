#include<iostream>
#include<stack>
#include<string>
#include<unordered_map>
#include<vector>
#include<bits/stdc++.h>

// Input string: "a+b*c*d" 

using namespace std;


char op_table[5][5] =
                    {
                        { '_', 'i', '+', '*', '$' },
                        { 'i', '_', '>', '>', '>' },
                        { '+', '<', '>', '<', '>' },
                        { '*', '<', '>', '>', '>' },
                        { '$', '<', '<', '<', '_' }
                    };

int getLongestPath(int node, int graph[5][5], int vis[5][5], bool isRow)
{
    int ans = 0;
    for(int v  = 1; v < 5; v++)
    {
        int i, j, tar;
        if(isRow)
        {
            i = node;
            j = v;
            tar = 1;
        }
        else
        {
            i = v;
            j = node;
            tar = -1;      }
        if(vis[i][j] or graph[i][j] != tar)     continue;
        vis[i][j] = true;
        ans = max(ans, 1 + getLongestPath(v, graph, vis, !isRow));
        vis[i][j] = false;
    }

    return ans;
}

int main()
{
    int graph[5][5] = {{0}};

    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 5; j++)
        {
            if(op_table[i][j] == '>')
            {
                graph[i][j] = 1;
            }
            else if(op_table[i][j] == '<')
            {
                graph[i][j] = -1;
            }
        }
    }

    cout << "f ";

    for(int i = 1; i < 5; i++)
    {
        int vis[5][5] = {{0}};
        cout << getLongestPath(i, graph, vis, true) << " ";
    }
    
    cout << endl << "g ";
    for(int i = 1; i < 5; i++)
    {
        int vis[5][5] = {{0}};
        cout << getLongestPath(i, graph, vis, false) << " ";
    }

    return 0;
}
