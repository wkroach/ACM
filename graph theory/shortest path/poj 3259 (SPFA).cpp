//吴柯
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define N 505
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,w,ql,qr,pos,val;
int vis[N],vis2[N],judge[N],num[N];
int dis[N],head[N];
int e[N][N];
vector <int> v[N];
void init()
{
    memset(vis,0,sizeof(vis));
    memset(num,0,sizeof(num));
//    memset(vis2,0,sizeof(vis2));
    for(int i=0;i<=n;++i)
        dis[i]=INF;
}

bool spfa(int s)
{
    stack <int> q;///SPFA的栈优化，效率高于队列
//    int cnt=1;
    dis[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int a=q.top();
        q.pop();
        vis[a]=0;
        for(int i=0;i<v[a].size();++i)
        {
            if(dis[v[a][i]]>dis[a]+e[a][v[a][i]])
            {
                dis[v[a][i]]=dis[a]+e[a][v[a][i]];
                if(!vis[v[a][i]])
                {
                    vis[v[a][i]]=1;
                    q.push(v[a][i]);
                    if(++num[v[a][i]]>n)
                    {
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b;
    int c;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
            {
                if(i==j) e[i][j]=0;
                else e[i][j]=INF;
            }
        for(int i=0;i<=n;++i)
            v[i].clear();
        scanf("%d%d%d",&n,&m,&w);
        for(int i=0;i<m+w;++i)///注意审题,不同
        {
            scanf("%d%d%d",&a,&b,&c);
            if(i>=m) c=-1*c;
            if(e[a][b]>c)
            {
                if(i<m)
                {
                    e[a][b]=e[b][a]=c;
                    v[a].push_back(b);
                    v[b].push_back(a);
                }
                else
                {
                    e[a][b]=c;
                    v[a].push_back(b);
                }
            }
        }
        init();
        if(spfa(1))
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}
