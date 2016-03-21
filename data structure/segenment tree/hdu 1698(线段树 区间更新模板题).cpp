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
#define MOD 1000000007
#define N 105
#define M 100005
#define MAX 1000000000
int sum[M*4];
int lazy[M*4];
int ql,qr,z;

void push_up(int now)
{
    sum[now]=sum[now*2]+sum[now*2+1];
}

void push_down(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(lazy[now]&&l!=r)
    {
        lazy[now*2]=lazy[now];
        lazy[now*2+1]=lazy[now];
        sum[now*2]=lazy[now]*(mid-l+1);
        sum[now*2+1]=lazy[now]*(r-mid);
        lazy[now]=0;
    }
}

void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(ql<=l&&qr>=r)
    {
        lazy[now]=z;
        sum[now]=z*(r-l+1);
        if(l!=r)
            push_down(now,l,r);
    }
    else
    {
        push_down(now,l,r);
        if(ql<=mid) update(now*2,l,mid);
        if(qr>mid) update(now*2+1,mid+1,r);
        push_up(now);
    }
}

void build(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r) sum[now]=1;
    else
    {
        build(now*2,l,mid);
        build(now*2+1,mid+1,r);
        push_up(now);
    }
}


int quire(int now,int l,int r)
{
    int ans=0;
    int mid=l+(r-l)/2;
    push_down(now,l,r);
    push_up(now);
    if(ql<=l&&r<=qr)
    {
        return sum[now];
    }
    if(ql=mid) ans+=quire(now*2,l,mid);
    if(qr>mid) ans+=quire(now*2+1,mid+1,r);
    return ans;
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int n,t;
    scanf("%d",&t);
    int T=t;
    while(t--)
    {
        memset(sum,0,sizeof(sum));
        memset(lazy,0,sizeof(lazy));
        scanf("%d",&n);
        build(1,1,n);
        int q;
        scanf("%d",&q);
        for(int i=0;i<q;++i)
        {
            scanf("%d%d%d",&ql,&qr,&z);
            update(1,1,n);
        }
        ql=1;qr=n;
        //quire(1,1,n);
        printf("Case %d: The total value of the hook is %d.\n",T-t,quire(1,1,n));
        //printf("%d.\n",sum[1]);
//        for(int i=1;i<=2*n+1;++i)
//            printf("%d ",sum[i]);
//        puts("");
//        for(int i=1;i<=2*n+1;++i)
//            printf("%d ",lazy[i]);
    }
    return 0;

}

