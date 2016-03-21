//Îâ¿Â
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
#define N 110
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val;
int e[N][N],vis[N],dis[N],judge[N];
vector <int> v[N];

bool spfa(int s)
{
    queue <int> q;
    dis[s]=0;
    int a=s;
    q.push(s);
    while(!q.empty())
    {
        a=q.front();
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
                    judge[v[a][i]]++;
                    if(judge[v[a][i]]>n)
                        return false;
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
    int a,b,c;
    while(scanf("%d%d",&n,&m)==2)
    {
        if(!n&&!m) break;
        memset(vis,0,sizeof(vis));
        memset(judge,0,sizeof(judge));
        for(int i=0;i<=n;++i)
            dis[i]=INF;
        for(int i=0;i<=n;++i)
            v[i].clear();
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            {
                if(i==j) e[i][j]=0;
                e[i][j]=INF;
                e[j][i]=INF;
            }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            e[a][b]=c;
            e[b][a]=c;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        if(spfa(1))
            printf("%d\n",dis[n]);
        printf("-1\n");
    }
    return 0;
}
