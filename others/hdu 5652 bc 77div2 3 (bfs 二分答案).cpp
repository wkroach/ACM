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

#define Size 1000005
#define inf 2e9
#define INF 2e18
#define LL long long int
#define i64 __int64
#define ULL unsigned long long
#define Mod 1000000007
#define pi 4*atan(1)
#define eps 1e-8
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
using namespace std;
int n,m,k;
int ql,qr,pos;
int dir[4][2] = {1,0,0,1,-1,0,0,-1};

struct node
{
    int x,y;
    int val;
    int num;
    node():x(0),y(0),val(0),num(0){}
};

int maze[505][505];
node maze2[505][505];
int vis[505][505];

void maze_input(int r,int c)///重点，对于此题，可以在最上面加一排空点，并搜索第一个点，即可保证原第一排均被搜索过，避免了对原第一排每个位置作起始点搜索
{
    char s[506];
    for(int i=1;i<=r;++i)
    {
        scanf("%s",s);
        for(int j=0;j<c;++j)
        {
            maze[i][j] = s[j]-'0';
        }
    }
}

void maze_output()
{
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<m;++j)
        {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
}


bool good(node tmp, int t)
{
    int x = tmp.x;
    int y = tmp.y;
    if(vis[x][y])
        return false;
    if(x<0||x>n)
        return false;
    if(y<0||y>=m)
        return false;
    if(maze[x][y])
        return false;
    if(maze2[x][y].val == 1 && maze2[x][y].num <= t)
        return false;
    return true;
}

bool bfs(int t)///bfs，注意每次搜索前要初始化vis数组
{
    memset(vis,0,sizeof(vis));///记得初始化！！！！！！！！！！！！！！
    node s;
    queue<node> q;
    while(!q.empty())
        q.pop();
    q.push(s);
    while(!q.empty())
    {
        node tmp = q.front();
//        cout<<tmp.x<<" "<<tmp.y<<endl;
        if(tmp.x == n)
            return true;
        node tmp2;
        for(int i=0;i<4;++i)
        {
            tmp2.x = tmp.x + dir[i][0];
            tmp2.y = tmp.y + dir[i][1];
            if(good(tmp2,t))
            {
                vis[tmp2.x][tmp2.y] = 1;
                q.push(tmp2);
            }
        }
        q.pop();
    }
    return false;
}

int bis(int s, int e)
{
    int l = s, r = e;///二分核心思想，所要找的解必须在[l,r] 中，减小范围直到两者相差1，根据选取的左右边界是否为前一个mid（即是否访问过），选择取整方式
  /*  if(!bfs(s))
        return 0;
    while(l < r)
    {
        int mid = (l + r + 1) / 2;///由于当r = l + 1时可能会无线循环，要向上取整
        bool judge = bfs(mid);

        if(judge)
        {
            l = mid;///每段区间，在初始值已特判的情况下，l作为前一个的mid已经判断过
        }
        else
        {
            r = mid - 1;
        }
    }
    if(l == e) return -1;
    return l + 1;
    */ ///二分写法1，找出可以通行的最后的一年 再加一(相对于可行解进行upper_bound)，要判断都不能通行的情况即起始年份是否能通行

    if(bfs(e))
        return -1;
    while(l<r)
    {
        int mid = (l + r)/2;
        bool judge = bfs(mid);
        if(judge)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;///每段区间，在末尾值已特判的情况下，r作为前一个的mid已经判断过
        }
    }
    return l;///二分写法2，找到不可行的第一年（相对于不可行解进行lower_bound), 要判断都可通行即最后一年的情况
}
int main()
{
    #ifndef ONLINE_JUDGE
//        freopen("input.txt","r",stdin);
//        freopen("output.txt","w",stdout);
    #endif // ONLINE_JUDGE
    int t;
    int x,y,z;
    int Case=0;
    cin>>t;
    while(t--)
//    while(scanf("%d",&t)&&t)
    {
        cin>>n>>m;
        memset(maze,0,sizeof(maze));
        memset(maze2,0,sizeof(maze2));
        maze_input(n,m);
//        maze_output();
        cin>>k;
        for(int i=1;i<=k;++i)
        {
            cin>>x>>y;
            maze2[x+1][y].val = 1;
            maze2[x+1][y].num = i;
        }
        cout<<bis(0,k)<<endl;///由于随着年份增加，山越多，连通的可能性越低，因此是有序的，可以二分答案
    }
    return 0;
}

