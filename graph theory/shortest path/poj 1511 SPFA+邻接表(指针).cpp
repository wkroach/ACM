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
#define N 1000005
#define INF 10000000000LL
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val;
int vis[N],judge[N];
LL dis[N];

struct node///邻接链表
{
    int v;
    LL e;
    node *next;
}edge[N];///正向道路
node redge[N];///反向道路
void init()
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;++i)
        dis[i]=INF;
}

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
        for(node *p=edge[a].next;p!=NULL;p=p->next)
        {
            if(dis[p->v]>dis[a]+p->e)
            {
                dis[p->v]=dis[a]+p->e;
                if(!vis[p->v])
                {
                    vis[p->v]=1;
                    q.push(p->v);
                }
            }
        }
    }
    return true;
}

bool spfa2(int s)
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
        for(node *p=redge[a].next;p!=NULL;p=p->next)
        {
            if(dis[p->v]>dis[a]+p->e)
            {
                dis[p->v]=dis[a]+p->e;
                if(!vis[p->v])
                {
                    vis[p->v]=1;
                    q.push(p->v);
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
    LL c;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i)
        {
            edge[i].v=i;
            edge[i].e=INF;
            edge[i].next=NULL;
            redge[i].v=i;
            redge[i].e=INF;
            redge[i].next=NULL;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%lld",&a,&b,&c);
            node *p1=&edge[a];///正向道路即出度
            node *p2=NULL;
            p2=new node;
            p2->v=b;
            p2->e=c;
            p2->next=p1->next;
            p1->next=p2;
            p1=&redge[b];///反向道路及入度
            p2=new node;
            p2->v=a;
            p2->e=c;
            p2->next=p1->next;
            p1->next=p2;
        }
        LL sum=0;
        ///两次SPFA求出正向与反向最短路，两者加和即从起点到某一节点再回起点的最短路
        init();
        spfa(1);
        for(int i=1;i<=n;++i)
            sum+=dis[i];
        init();
        spfa2(1);
        for(int i=1;i<=n;++i)
            sum+=dis[i];
        printf("%lld\n",sum);
    }
    return 0;
}
