#include <bits/stdc++.h>
#include <math.h>
#define lli long long int
#include <limits.h>

using namespace std;

set<int> box[3][3],row[9],col[9];
int grid[9][9];
set<int> pos[9][9];

bool solve(int x,int y)
{
    if(x>8 || y>8)
        return 1;
    if(grid[x][y]!=0)
    {
        if(y==8)
            return solve(x+1,0);
        else
            return solve(x,y+1);
    }
    bool ok=0;
    for(auto num:pos[x][y])
    {
        if(box[x/3][y/3].count(num) && row[x].count(num) && col[y].count(num))
        {
            //cout<<x<<" "<<y<<" "<<num<<"\n";
            grid[x][y]=num;
            box[x/3][y/3].erase(box[x/3][y/3].find(num));
            row[x].erase(row[x].find(num));
            col[y].erase(col[y].find(num));
            if(y==8)
                ok=solve(x+1,0);
            else
                ok=solve(x,y+1);
            if(ok==1)
                return 1;
            else
            {
                box[x/3][y/3].insert(num);
                row[x].insert(num);
                col[y].insert(num);
                grid[x][y]=0;
            }
        }
    }
    return 0;
}

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int i,j;
    int k;
    string s;
    for(i=0;i<9;i++)
    {
        cin>>s;
        for(j=0;j<9;j++)
            grid[i][j]=(s[j]-'0');
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=1;k<10;k++)
                box[i][j].insert(k);
        }
    }
    for(i=0;i<9;i++)
    {
        for(j=1;j<10;j++)
        {
            row[i].insert(j);
            col[i].insert(j);
        }
    }
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(grid[i][j]!=0)
            {
                box[i/3][j/3].erase(box[i/3][j/3].find(grid[i][j]));
                row[i].erase(row[i].find(grid[i][j]));
                col[j].erase(col[j].find(grid[i][j]));
            }
        }
    }
    /*for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            for(auto x:box[i][j])
                cout<<x<<" ";
            cout<<"\n";
        }
    }*/
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            for(k=1;k<10;k++)
            {
                if(grid[i][j]==0)
                    pos[i][j].insert(k);
                else
                    break;
            }
        }
    }
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            for(k=1;k<10;k++)
            {
                if(box[i/3][j/3].count(k)==0)
                {
                    if(pos[i][j].count(k))
                    {
                        pos[i][j].erase(pos[i][j].find(k));
                        continue;
                    }
                }
                if(row[i].count(k)==0)
                {
                    if(pos[i][j].count(k))
                    {
                        pos[i][j].erase(pos[i][j].find(k));
                        continue;
                    }
                }
                if(col[j].count(k)==0)
                {
                    if(pos[i][j].count(k))
                    {
                        pos[i][j].erase(pos[i][j].find(k));
                        continue;
                    }
                }
            }
        }
    }
    /*for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            cout<<i<<" "<<j<<": ";
            for(auto x:pos[i][j])
                cout<<x<<" ";
            cout<<"\n";
        }
    }*/
    bool junk=solve(0,0);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
            cout<<grid[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}

