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
#define N 100005
#define MAX 1000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val,c;
LL arr[N],sum[N*4],lazy[N*4];
char ch[2];

void push_up(int now)
{
    sum[now]=sum[now*2]+sum[now*2+1];
}

void build(int now,int l,int r)
{
    if(l==r)
    {
        sum[now]=arr[l];
        return ;
    }
    build(lson);
    build(rson);
    push_up(now);
}

void push_down(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r) return;
    if(lazy[now]!=0)
    {
        lazy[now*2]+=lazy[now];
        lazy[now*2+1]+=lazy[now];
        sum[now*2]+=(mid-l+1)*lazy[now];
        sum[now*2+1]+=(r-mid)*lazy[now];
        lazy[now]=0;
    }
}

void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)
    {
        lazy[now]+=c;
        sum[now]+=(r-l+1)*c;
        return ;
    }
    push_down(now,l,r);
    if(ql<=mid) update(lson);
    if(qr>mid) update(rson);
    push_up(now);
}

LL quire(int now,int l,int r)
{
    LL ans=0;
    int mid=l+(r-l)/2;
    push_down(now,l,r);
    if(ql<=l&&r<=qr)
    {
        return sum[now];
    }
    if(ql<=mid) ans+=quire(lson);
    if(qr>mid) ans+=quire(rson);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d",&n,&m)==2)
    {
        memset(lazy,0,sizeof(lazy));
        for(int i=1;i<=n;++i)
            scanf("%I64d",&arr[i]);
        build(1,1,n);
        for(int i=1;i<=m;++i)
        {
            scanf("%s",ch);
            if(ch[0]=='C')
            {
                scanf("%d%d%d",&ql,&qr,&c);
                update(1,1,n);
            }
            else if(ch[0]=='Q')
            {
                scanf("%d%d",&ql,&qr);
                printf("%I64d\n",quire(1,1,n));
            }
        }
    }
    return 0;
}
