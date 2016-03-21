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
#define Max 1000000000
#define seed 31
#define ULL unsigned long long int
#define lson now*2,l,l+(r-l)/2
#define rson now*2+1,l+(r-l)/2+1,r
int n,m,ql,qr,pos,val,arr[N],MAX[N*4],SMAX[N*4];
int arr2[N],p=0;

bool cmp(int a,int b)
{
    return a>b;
}

void push_up(int now,int l,int r)///建立两颗线段树，一颗保存最大值，另一颗保存次大值
{
    MAX[now]=max(MAX[now*2],MAX[now*2+1]);
    int a=MAX[now*2]+MAX[now*2+1]-MAX[now];
    SMAX[now]=max(a,max(SMAX[now*2],SMAX[now*2+1]));///注意保存次大值时需要区间合并
}

void build(int now,int l,int r)
{
    if(l==r)
    {
        MAX[now]=arr[l];
        SMAX[now]=0;///单点次大值初始化为0
        return ;
    }
    build(lson);
    build(rson);
    push_up(now,l,r);
}

int quire1(int now,int l,int r)///第一次插询出最大值，并保存下来
{
    int ans1=0,ans2=0;
    int mid=l+(r-l)/2;
    if(ql<=l&&qr>=r)
    {
        return MAX[now];
    }
    if(ql<=mid) ans1=quire1(lson);
    if(qr>mid) ans2=quire1(rson);
    return max(ans1,ans2);
}

int quire2(int now,int l,int r)///第二次根据最大值插询出次大值
{
    int ans1=0,ans2=0;
    int mid=l+(r-l)/2;
    if(ql<=l&&r<=qr)///重点！！！！！！！
        ///次大值一定是除最大值所在节点之外其余节点的最大值
        ///或这是最大值所在节点的次大值
        ///然后在他们之中选最大的那个就是次大值
    {
        if(MAX[now]==val)
            return SMAX[now];
        else
            return MAX[now];
    }
    if(ql<=mid) ans1=quire2(lson);
    if(qr>mid) ans2=quire2(rson);
    return max(ans1,ans2);
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE
    int n,m;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&arr[i]);
        build(1,1,n);
        for(int i=0;i<m;++i)
        {
            memset(arr2,0,sizeof(arr2));
            p=val=0;
            scanf("%d%d",&ql,&qr);
            if(ql==qr)
                printf("-1\n");
            else
            {
                val=quire1(1,1,n);
                printf("%d\n",quire2(1,1,n));
            }
        }
    }
    return 0;
}
