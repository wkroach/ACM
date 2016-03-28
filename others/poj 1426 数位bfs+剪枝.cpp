#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<vector>
#include<algorithm>

//#include<bits/c++std.h>

#define Size 100005
#define inf 2e9
#define INF 2e18
#define LL long long
#define i64 __LL64
#define ULL unsigned long long
#define Mod 1000000007
using namespace std;
int n,m,k;
int vis[300];

struct node
{
    ULL s;
    int mod;
};

node bfs(int n)///状态压缩加（将数存到一个ull的数中），bfs剪枝（对模剪枝，搜过的不搜）
{
    queue<node> q;
    while(!q.empty())
    {
        q.pop();
    }
    node tmp;
    tmp.s = 1;
    tmp.mod = 1%n;
    q.push(tmp);
    while(!q.empty())
    {
        tmp = q.front();
        if(vis[tmp.mod])
        {
           q.pop();
           continue;
        }
        else
            vis[tmp.mod] = 1;
        if(!tmp.mod)
        {
            return tmp;
        }
        node tmp2;
        tmp2.s = tmp.s;
        tmp2.s <<= 1;
        tmp2.s++;
        tmp2.mod = (tmp.mod*10+1)%n;
        q.push(tmp2);
        node tmp3;
        tmp3.s = tmp.s;
        tmp3.s <<= 1;
        tmp3.mod = (tmp.mod*10)%n;
        q.push(tmp3);
        q.pop();
    }
}

int main()
{

    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    LL t;
    int x,y,z;
    LL Case=0;
//    cin>>t;
//    while(t--)
//    cin>>n;
    int tmp=0;
    while(cin>>n)
    {
//        n=tmp;
        memset(vis,0,sizeof(vis));
        if(n==0) break;
        node ans = bfs(n);
        ULL tmp2 = ans.s;
        stack<int> st;
        while(tmp2)
        {
            st.push(tmp2&1);
            tmp2 >>= 1;
        }
        while(!st.empty())///将数还原
        {
            printf("%d",st.top());
            st.pop();
        }
        cout<<endl;
    }
    return 0;
}
