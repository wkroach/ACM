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
#define ULL unsigned long long int
#define MOD 1000000007
#define N 205
#define INF 0x3f3f3f3f
#define seed 31
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,dis[N],vis[N];
int e[N][N];
vector <int> v[N];

void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i)
        dis[i]=INF;
}

void dijkstra(int a,int b)
{
    dis[a]=0;
    for(int i=1;i<=N;++i)
    {
        int m=INF,s;
        for(int j=1;j<=N;++j)
            if(!vis[j]&&dis[j]<m) m=dis[j],s=j;
        vis[s]=1;
        for(int j=0;j<v[s].size();++j)
            dis[v[s][j]]=min(dis[v[s][j]],dis[s]+e[s][v[s][j]]);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int a,b,c,k=0;
    while(scanf("%d%d",&n,&m)==2)
    {
//        if(!n&&!m)
//            break;
        for(int i=1;i<=N;++i)
            v[i].clear();
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
            {
                if(i==j) e[i][j]=0;
                e[i][j]=INF;
            }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            a++,b++;
            e[a][b]=min(e[a][b],c);
            e[b][a]=min(e[b][a],c);
            v[a].push_back(b);
            v[b].push_back(a);
        }
//        printf("Test Set #%d\n",++k);
//        for(int i=1;i<=n;++i)
//        {
            scanf("%d%d",&a,&b);
            a++;b++;
            if(a==b)
            {
                printf("0\n");
                continue;
            }
            init();
            dijkstra(a,b);
            if(dis[b]==INF) dis[b]=-1;
            printf("%d\n",dis[b]);
//        }
//        puts("");
//        for(int i=1;i<=N;++i)
//            printf("%d ",dis[i].d);
    }
    return 0;
}
