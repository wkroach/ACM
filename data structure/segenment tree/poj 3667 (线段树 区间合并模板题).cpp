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
int msum[500005*4],lsum[500005*4],rsum[500005*4];
int lazy[500005*4];
int ql,qr,a,b,c;
void build(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(l==r)
    {
        msum[now]=lsum[now]=rsum[now]=1;
    }
    else
    {
        build(now*2,l,mid);
        build(now*2+1,mid+1,r);
        lsum[now]=rsum[now]=msum[now]=msum[now*2]+msum[now*2+1];
    }
}

void push_up(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(lsum[now*2]==(mid-l+1))
        lsum[now]=lsum[now*2]+lsum[now*2+1];
    else
        lsum[now]=lsum[now*2];
    if(rsum[now*2+1]==r-mid)
        rsum[now]=rsum[now*2+1]+rsum[now*2];
    else
        rsum[now]=rsum[now*2+1];
//    msum[now]=max(msum[now],msum[now*2]);
    msum[now]=max(msum[now*2],msum[now*2+1]);
    msum[now]=max(msum[now],rsum[now*2]+lsum[now*2+1]);
//    msum[now]=max(msum[now],lsum[now]);
//    msum[now]=max(msum[now],rsum[now]);
}

void push_down(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    if(lazy[now]!=-1&&l!=r)
    {
        lazy[now*2]=lazy[now];
        lazy[now*2+1]=lazy[now];
        lsum[now*2]=rsum[now*2]=msum[now*2]=(mid-l+1)*lazy[now];
        lsum[now*2+1]=rsum[now*2+1]=msum[now*2+1]=(r-mid)*lazy[now];
        lazy[now]=-1;
    }
    //push_up(now,l,r);
}

void update(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    //push_down(now,l,r);
    if(ql<=l&&r<=qr)
    {
        lazy[now]=c;
        lsum[now]=msum[now]=rsum[now]=(r-l+1)*lazy[now];
//        if(l==r) lazy[now]=-1;
//        push_down(now,l,r);
        return ;
    }
    push_down(now,l,r);
    if(ql<=mid) update(now*2,l,mid);
    if(qr>mid) update(now*2+1,mid+1,r);
    push_up(now,l,r);
}

int quire(int now,int l,int r)
{
    int mid=l+(r-l)/2;
    push_down(now,l,r);
    //push_up(now,l,r);
    if(msum[now]<b) return 0;
    if(lsum[now]>=b) return l;
    else if(msum[now*2]>=b) quire(now*2,l,mid);
    else if(rsum[now*2]+lsum[now*2+1]>=b) return mid-rsum[now*2]+1;
    else quire(now*2+1,mid+1,r);
    //push_up(now,l,r);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int n,m;
    while(scanf("%d%d",&n,&m)==2)
    {
        memset(msum,0,sizeof(msum));
        memset(lsum,0,sizeof(lsum));
        memset(rsum,0,sizeof(rsum));
        memset(lazy,-1,sizeof(lazy));
        build(1,1,n);
        for(int i=0;i<m;++i)
        {
            scanf("%d",&a);
            if(a==1)
            {
                c=0;
                scanf("%d",&b);
                ql=quire(1,1,n);
                printf("%d\n",ql);
                if(ql)
                {
                    qr=ql+b-1;
                    update(1,1,n);
                }
            }
            else if(a==2)
            {
                scanf("%d%d",&ql,&qr);
                qr=ql+qr-1;
                c=1;
                update(1,1,n);
            }
//        printf("%d %d %d %d %d\n",a,b,c,ql,qr);
//        for(int i=1;i<=n*2+1;++i)
//            printf("%d ",msum[i]);
//        puts("");
//        for(int i=1;i<=n*2+1;++i)
//            printf("%d ",lsum[i]);
//        puts("");
//        for(int i=1;i<=n*2+1;++i)
//            printf("%d ",rsum[i]);
//        puts("");
        }
//        for(int i=1;i<=n*2+1;++i)
//            printf("%d ",msum[i]);
    }
    return 0;
}
