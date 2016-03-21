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

///优先队列的本质是一个二叉（最小/最大）堆
///用优先队列优化dijkstra实际上是在用堆优化

///被优化的过程：在未被遍历的节点中找到dis最短的节点
///时间复杂度提升：
///被优化部分：O(V)->O(log(V))
///整体:O(V^2 +E)->O((V+E)log(V))

///注意：手动实现一个堆的运行效率比用stl的priority_queue高
int n,m,vis[N];
int e[N][N];///当边数较多时改为邻接矩阵
struct node
{
    int u;
    int d;
    friend bool operator < (node a,node b)///重载操作符'<',用于比较连个结构体
    {
        if(a.d==b.d) return a.u>b.u;///重点！！！优先队列中原本以较小为优先级低
        else return a.d>b.d;///这里重载时要将'<'改为'>',a<b实际在结构体之间表示a>b
    }
}dis[N];

vector <int> v[N];
priority_queue < node > q;
void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i)
        dis[i].d=INF,
        dis[i].u=i;
    while(!q.empty())
        q.pop();
}

void dijkstra(int a,int b)
{
    dis[a].d=0;
    q.push(dis[a]);
    while(!q.empty())
    {
        int m=INF,s;
        node x=q.top();
        s=x.u;
        q.pop();
        if(vis[s])
            continue;
        vis[s]=1;
        for(int j=0;j<v[s].size();++j)
        {
            if(dis[v[s][j]].d>dis[s].d+e[s][v[s][j]])
            {
               dis[v[s][j]].d=dis[s].d+e[s][v[s][j]];
                q.push(dis[v[s][j]]);
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
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);///如果是无向图，则需要对两个节点都存一遍(加上注释中的代码即可)
            e[a][b]=c;
//            e[b][a]=c;
            v[a].push_back(b);
//            v[b].push_back(a);
        }
            init();///将vis，dis和优先队列初始化
            dijkstra(1,n);///可根据题目要求更变始末节点
            printf("%d\n",dis[n].d);
    }
    return 0;
}
