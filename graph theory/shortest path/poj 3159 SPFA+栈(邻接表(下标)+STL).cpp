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
#define N 30005
#define INF 0x3f3f3f3f
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val;
int vis[N],judge[N];
int dis[N],head[N];

struct node///下标法实现邻接链表，效率高于指针
{
    int u;
    int v;
    int w;
    int next;
}edge[N*10];
void init()
{
    memset(vis,0,sizeof(vis));
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
//        cnt--;
        vis[a]=0;
        for(int tmp=head[a];tmp!=-1;tmp=edge[tmp].next)
        {
            int v=edge[tmp].v,w=edge[tmp].w;
            if(dis[v]>dis[a]+w)
            {
                dis[v]=dis[a]+w;
                if(!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
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
    while(scanf("%d%d",&n,&m)==2)
    {
        int cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            edge[cnt].u=a;
            edge[cnt].v=b;
            edge[cnt].w=c;
            edge[cnt].next=head[a];
            head[a]=cnt++;
        }
        init();
        spfa(1);
        printf("%d\n",dis[n]);
    }
    return 0;
}
