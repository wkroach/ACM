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
int n,m,vis[N],dis[N];
int e[N][N];///当边数较多时改为邻接矩阵
vector <int> v[N];///邻接表，用于表示节点间的前后继关系

void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=N;++i)
        dis[i]=INF;
}

void dijkstra(int a,int b)///用于有向图
///算法思想：贪心
///时间复杂度：O(V^2+E)
{
    dis[a]=0;
    for(int i=1;i<=n;++i)///执行n次循环，n为节点个数
    {
        int m=INF,s;///每次循环需要找出一个未被遍历过的dis最小的节点，并标记
        for(int j=1;j<=n;++j)///查询最小dis的节点需要遍历所有节点，即循环n次
            if(!vis[j]&&dis[j]<m) m=dis[j],s=j;
        vis[s]=1;///标记
        for(int j=0;j<v[s].size();++j)///对于当前这个最小节点，对它的每个后继节点作松弛操作
            dis[v[s][j]]=min(dis[v[s][j]],dis[s]+e[s][v[s][j]]);///松弛操作，类似于一个状态转移方程
            ///由于维护每个节点的最小dis

            ///tips:松弛操作实际将dis的上界“收紧”了，但却将节点之间的三角不等式条件“放松”了，因此叫作松弛操作
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
            scanf("%d%d%d",&a,&b,&c);
            e[a][b]=c;
            v[a].push_back(b);
        }
            init();///将vis，dis初始化
            dijkstra(1,n);///可根据题目要求更变始末节点
            printf("%d\n",dis[n]);
    }
    return 0;
}

