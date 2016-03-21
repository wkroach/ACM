//Îâ¿Â
#include<cstdio>
#include<cstdlib>
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
using namespace std;
#define LL long long int
#define ULL unsigned long long int
#define MOD 1000000007
#define N 205
#define INF 0x3f3f3f3f
#define seed 31
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r

///用set优化的原理是用红黑树找到未被访问过的节点中的最小值
///优化过程，目的，时间复杂度与优先队列类似，只是原理不同

int n,m,vis[N];
int e[N][N];///当边数较多时改用邻接表(vector)
struct node
{
    int u;
    int d;
    friend bool operator < (node a,node b)///重载操作符'<'，表示结构体的大小比较
    {
        if(a.d==b.d) return a.u<b.u;
        else return a.d<b.d;
    }
}dis[N];

vector <int> v[N];
set < node > ss;
void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i)
        dis[i].d=INF,
        dis[i].u=i;
    ss.clear();
}

void dijkstra(int a,int b)
{
    dis[a].d=0;
    ss.insert(dis[a]);
    while(!ss.empty())
    {
        int m=INF,s;
        node x=*ss.begin();
        s=x.u;
        ss.erase(ss.begin());
        if(vis[s])
            continue;
        vis[s]=1;
        for(int j=0;j<v[s].size();++j)
        {
            if(dis[v[s][j]].d>dis[s].d+e[s][v[s][j]])
            {
               dis[v[s][j]].d=dis[s].d+e[s][v[s][j]];
                ss.insert(dis[v[s][j]]);
            }
        }
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
        for(int i=1;i<=N;++i)
            v[i].clear();
        for(int i=1;i<=N;++i)
            for(int j=1;j<=N;++j)
            {
                if(i==j) e[i][j]=0;
                e[i][j]=INF;
            }
        for(int i=1;i<=m;++i)///如果是无向图，则需要对两个节点都存一遍(加上注释中的代码即可)
        {
            scanf("%d%d%d",&a,&b,&c);
            e[a][b]=c;
//            e[b][a]=c;
            v[a].push_back(b);
//            v[b].push_back(a);
        }
        init();///将ss，dis和vis初始化
        dijkstra(1,n);///可根据题目要求改变始末节点
        printf("%d\n",dis[n].d);
    }
    return 0;
}
